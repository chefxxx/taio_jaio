//
// Created by mshamrai on 11/16/25.
//
#include "generate_start_cost.h"
#include <map>

Matrix generateStartCost(const Matrix &m_1, const Matrix &m_2)
{
    constexpr short SIZE_OF_FIRST_SOURCE = 2;
    // Define the sizes for matrices
    long s1 = m_1.rows();
    long s2 = m_2.rows();
    std::vector labels_1(s1, -1);
    std::vector labels_2(s2, -1);

    std::vector sources_1(s1, std::vector(SIZE_OF_FIRST_SOURCE, 0));
    std::vector sources_2(s2, std::vector(SIZE_OF_FIRST_SOURCE, 0));

    auto outNeighborsCountForM1 = getNumberOfOutNeighbors(m_1);
    auto inNeighborsCountForM1 = getNumberOfInNeighbors(m_1);
    auto outNeighborsCountForM2 = getNumberOfOutNeighbors(m_2);
    auto inNeighborsCountForM2 = getNumberOfInNeighbors(m_2);

    for (int i = 0; i < s1; ++i) {
        sources_1[i][0] = inNeighborsCountForM1[i];
        sources_1[i][1] = outNeighborsCountForM1[i];
    }

    for (int i = 0; i < s2; ++i) {
        sources_2[i][0] = inNeighborsCountForM2[i];
        sources_2[i][1] = outNeighborsCountForM2[i];
    }

    auto labeling = findLabels(sources_1, sources_2);

    for (int i = 0; i < s1; ++i) {
        labels_1[i] = labeling[sources_1[i]];
    }

    for (int i = 0; i < s2; ++i) {
        labels_2[i] = labeling[sources_2[i]];
    }

    return Matrix::Identity(s1, s1);
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