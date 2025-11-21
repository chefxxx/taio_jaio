#include "hungarian_method.h"

// Rows - n + 1, columns - m + 1
// u - potentials for vertices from the V1
// v - potentials for vertices from the V2
// p - the vector where each element corresponds to the mapping vertex from the V1 to V2 p[j] - vertex from V1 that is
// mapped to the vertex j from V2
Matrix hungarianMethod(const Matrix &arg)
{
    int n = arg.rows() - 1;
    int m = arg.cols() - 1;
    std::vector u(n + 1, 0);
    std::vector v(m + 1, 0);

    std::vector p(m + 1, 0);
    std::vector way(m + 1, 0);
    for (int i = 1; i <= n; ++i) {
        p[0] = i;
        int j_0 = 0;
        std::vector minv(m + 1, INT_MAX);
        std::vector used(m + 1, false);
        do {
            used[j_0] = true;
            int i_0 = p[j_0];
            int delta = INT_MAX;
            int j_1 = -1;
            for (int j = 1; j <= m; ++j) {
                if (!used[j]) {
                    int cur = arg(i_0, j) - u[i_0] - v[j];
                    if (cur < minv[j]) {
                        minv[j] = cur;
                        way[j] = j_0;
                    }
                    if (minv[j] < delta) {
                        delta = minv[j];
                        j_1 = j;
                    }
                }
            }
            for (int j = 0; j <= m; ++j) {
                if (used[j]) {
                    u[p[j]] += delta;
                    v[j] -= delta;
                } else {
                    minv[j] -= delta;
                }
            }
            j_0 = j_1;
        } while (p[j_0] != 0);
        do {
            int j_1 = way[j_0];
            p[j_0] = p[j_1];
            j_0 = j_1;
        } while (j_0);
    }

    Matrix result = Matrix::Zero(n, m);
    for (int j = 1; j <= m; ++j) {
        p[j] > 0 ? result(p[j] - 1, j - 1) = 1 : 0;
    }
    return result;
}