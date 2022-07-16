/*  given keys K = [k_1 < k_2 < ... < k_n], each searched with different probability p_i (0<i<=n)
    The probability of finding something not in K but in between is q_i (0<=i<=n), for pseudo key in range (k_i, k_i+1)
    Expected search length of tree is averaged number of visiting nodes
    construct BST containing K that has minimum expected search length
    ------------------------------------------------------------
    INPUT:  number of keys n
            probabilities p_i (0<i<=n)
            probabilities q_i (0<=i<=n)
    OUTPUT: table root, entry root[i][j] = root of optimal BST of keys [ k_i < ... < k_j ]
    ------------------------------------------------------------
    Algorithm:
    E[search length of tree] = E[search length of left subtree] + E[search length of right subtree] + w[i][j]
    w[i][j] =   sum {p_l}(i<=l<=j) + sum {q_l}(i-1<=l<=j),      i <= j
    e[i][j] =   {
                    q_j                                                 if i-1 = j
                    min{e[i][r-1] + e[r+1][j] + w[i][j]} (r = i to j)   if i <= j
                }
*/

#include <vector>
#include <cstdint>
#include <limits>
#include <iostream>
using Index_t = std::uint8_t;
using RootTable = std::vector<std::vector<Index_t>>;
using CostTable = std::vector<std::vector<float>>;
using WTable = std::vector<std::vector<float>>;
constexpr Index_t INVALID_ROOT{0};
constexpr Index_t INVALID_PARENT{0};
constexpr float INVALID_W{-1.0};
constexpr float INVALID_E{std::numeric_limits<float>::max()};

void reconstructBST(RootTable &root, Index_t i, Index_t j, int parent = INVALID_PARENT)
{
    if (i > j)
        return;
    int node = root[i][j];
    if (parent)
    {
        auto leftOrRight = (i < parent) ? "left " : "right ";
        std::cout << "node " << node << " is " << leftOrRight << "child of " << parent << std::endl;
    }
    else
    {
        std::cout << "node " << node << " is root" << std::endl;
    }
    reconstructBST(root, i, node - 1, node);
    reconstructBST(root, node + 1, j, node);
}
void findBestBST(std::vector<float> &p, std::vector<float> &q, Index_t n, RootTable &root, CostTable &e, WTable &w)
{
    for (int i = 1; i <= n + 1; i++)
    {
        e.at(i).at(i - 1) = q.at(i - 1);
        w.at(i).at(i - 1) = q.at(i - 1);
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = i; j <= n; j++)
        {
            w.at(i).at(j) = w.at(i).at(j - 1) + p[j] + q[j];
        }
    }

    for (int l = 1; l <= n; l++)
    {
        for (int i = 1; i <= n + 1 - l; i++)
        {
            auto j = i + l - 1;
            for (auto r = i; r <= j; r++)
            {
                auto temp = e[i][r - 1] + e[r + 1][j] + w[i][j];
                if (temp < e[i][j])
                {
                    e[i][j] = temp;
                    root[i][j] = r;
                }
            }
        }
    }
}

int main()
{
    std::vector<float> p{INVALID_W, 0.04, 0.06, 0.08, 0.02, 0.10, 0.12, 0.14}; // INPUT
    std::vector<float> q{0.06, 0.06, 0.06, 0.06, 0.05, 0.05, 0.05, 0.05};      // INPUT
    Index_t n = p.size() - 1;
    RootTable root(n + 1, std::vector<Index_t>(n + 1, INVALID_ROOT));
    CostTable e(n + 2, std::vector<float>(n + 2, INVALID_E));
    WTable w(n + 2, std::vector<float>(n + 1, INVALID_W));
    findBestBST(p, q, n, root, e, w);
    reconstructBST(root, 1, n);
    return e[1][n];
}