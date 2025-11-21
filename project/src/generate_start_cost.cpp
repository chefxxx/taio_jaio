//
// Created by mshamrai on 11/16/25.
//
#include "generate_start_cost.h"
#include <map>


std::vector<std::vector<int>> fillNeighborsStructure(const Matrix &m,
    const std::function<std::vector<int>(Matrix, int)> &f)
{
    auto s = m.rows();
    std::vector<std::vector<int>> res = std::vector<std::vector<int>>();
    res.reserve(s);
    for (int i = 0; i < s; ++i) {
        res[i] = f(m, i);
    }
    return res;
}


void fillStartSources(std::vector<std::vector<int>> &sources, const std::vector<std::vector<int>> &outNeighbors,
    const std::vector<std::vector<int>> &inNeighbors)
{
    auto n = sources.size();
    for (unsigned i = 0; i < n; ++i) {
        sources[i][0] = outNeighbors[i].size();
        sources[i][1] = inNeighbors[i].size();
    }
}

std::vector<int> assignLabels(const std::map<std::vector<int>, int> &labeling,
    const std::vector<std::vector<int>> &sources)
{
    std::vector<int> labels;
    auto n = sources.size();
    for (unsigned i = 0; i < n; ++i) {
        labels[i] = labeling.at(sources[i]);
    }
    return labels;
}

Matrix generateStartCost(const Matrix &m_1, const Matrix &m_2)
{
    constexpr short SIZE_OF_FIRST_SOURCE = 2;
    long s1 = m_1.rows();
    long s2 = m_2.rows();
    std::vector labels_1(s1, -1);
    std::vector labels_2(s2, -1);

    std::vector sources_1(s1, std::vector(SIZE_OF_FIRST_SOURCE, 0));
    std::vector sources_2(s2, std::vector(SIZE_OF_FIRST_SOURCE, 0));

    std::vector<std::vector<int>> outNeighbors_1 = fillNeighborsStructure(m_1, getIndicesOfOutNeighbors);
    std::vector<std::vector<int>> inNeighbors_1 = fillNeighborsStructure(m_1, getIndicesOfInNeighbors);
    std::vector<std::vector<int>> outNeighbors_2 = fillNeighborsStructure(m_2, getIndicesOfOutNeighbors);
    std::vector<std::vector<int>> inNeighbors_2 = fillNeighborsStructure(m_2, getIndicesOfInNeighbors);

    fillStartSources(sources_1, outNeighbors_1, inNeighbors_1);
    fillStartSources(sources_2, outNeighbors_2, inNeighbors_2);

    std::map<std::vector<int>, int> labeling = findLabels(sources_1, sources_2);
    std::map<std::vector<int>, int> oldLabeling = std::map<std::vector<int>, int>();


    labels_1 = assignLabels(labeling, sources_1);
    labels_2 = assignLabels(labeling, sources_2);

    while (oldLabeling.size() != labeling.size()) {
        oldLabeling = labeling;
        auto k = oldLabeling.size();
        // Expand the vectors for sources
        for (unsigned i = 0; i < sources_1.size(); ++i) {
            // The first element is the vertex label from the last iteration
            sources_1[i].resize((k << 1) + 1, 0); // 2k + 1
            sources_1[i][0] = labels_1[i];
            int label = -1;
            for (int outNeighborIndex: outNeighbors_1[i]) {
                // Firstly out
                label = labels_1[outNeighborIndex];
                ++sources_1[i][label + 1];
            }
            for (int inNeighborIndex: inNeighbors_1[i]) {
                // Then inNeighbors
                label = labels_1[inNeighborIndex];
                ++sources_1[i][label + 1 + k];
            }
        }
        for (unsigned i = 0; i < sources_2.size(); ++i) {
            sources_2[i].resize((k << 1) + 1, 0);
            sources_2[i][0] = labels_2[i];
            int label = -1;
            for (int outNeighborIndex: outNeighbors_2[i]) {
                label = labels_2[outNeighborIndex];
                ++sources_2[i][label + 1];
            }
            for (int inNeighborIndex: inNeighbors_2[i]) {
                label = labels_2[inNeighborIndex];
                ++sources_2[i][label + k];
            }
        }
        labeling = findLabels(sources_1, sources_2); // find the next labeling
        labels_1 = assignLabels(labeling, sources_1);
        labels_2 = assignLabels(labeling, sources_2);
    }

    Matrix labelsMappingCost = calculateLabelsMappingCost(labeling);
    Matrix finalCostMatrix = Matrix::Zero(s1, s2);
    for (int i = 0; i < s1; ++i) {
        for (int j = 0; j < s2; ++j) {
            finalCostMatrix(i, j) = labelsMappingCost(labels_1[i], labels_2[j]);
        }
    }

    return finalCostMatrix;
}


std::map<std::vector<int>, int> findLabels(const std::vector<std::vector<int>> &sources1,
    const std::vector<std::vector<int>> &sources2)
{
    std::vector copy1 = sources1;
    std::ranges::sort(copy1, [](const std::vector<int> &a, const std::vector<int> &b) {
        return std::ranges::lexicographical_compare(a, b);
    });

    std::vector copy2 = sources2;
    std::ranges::sort(copy2, [](const std::vector<int> &a, const std::vector<int> &b) {
        return std::ranges::lexicographical_compare(a, b);
    });

    std::vector<std::vector<int>> merged;
    std::ranges::merge(copy1, copy2, std::back_inserter(merged));

    std::map<std::vector<int>, int> labels;

    for (unsigned i = 0, l = 0; i < merged.size(); ++i) {
        labels.try_emplace(merged[i], l).second == true ? l++ : 0;
    }
    return labels;
}

Matrix calculateLabelsMappingCost(const std::map<std::vector<int>, int> &labeling)
{
    int k = labeling.size();
    Matrix result = Matrix::Zero(k, k);
    std::vector<int> values = std::vector<int>();
    values.reserve(k);
    std::transform(labeling.begin(), labeling.end(), std::back_inserter(values),
        [](const auto &entry){return entry.second;});
    for (const auto &labelFrom: labeling) {
        for (const auto &labelTo: labeling) {
            result.coeffRef(labelFrom.second, labelTo.second) =
                calculateCostForTwoLabels(labelFrom.first, labelTo.first);
        }
    }
    return result;
}

int calculateCostForTwoLabels(const std::vector<int> &source_1, const std::vector<int> &source_2)
{
    int res = 0;
    int tmp = 0;
    if (source_1[0] != source_2[0]) {
        for (unsigned i = 1; i < source_1.size(); ++i) {
            tmp = source_1[i] - source_2[i];
            res += tmp >= 0 ? tmp : 0;
        }
    }
    return res;
}