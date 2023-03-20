/*
### 9.3-6
The k-th quantiles of an n-element set are the k - 1 order statistics that divide the
sorted set into k equal-sized sets (to within 1). Give an O(nlg k)-time algorithm to
list the k-th quantiles of a set.

Proposed Algorithm:
    Step 1. Precalculate indices of k-th quantiles --> A.
            Set p = 1, r = n.
    Step 2. find the order statistic A[(p+r)/2] in set S --> x.
            At this point S is partitioned on x into LS, RS.
    Step 3. Continue finding quantiles in LS, RS, respectively.
            Specifically, find orders A[p, (p+r)/2 - 1] in LS,
            and find orders A[(p+r)/2 + 1, r] in RS.

Complexity:
    T(k) = O(n) + T(⎣k/2⎦-1) + T(⎡k/2⎤)
*/

#include <vector>
#include <array>
#include <cstdio>
#include <algorithm>

using namespace std;

constexpr int n = 12;
constexpr uint8_t k = 3;
array<int, n> S{2, 6, 1, 4, 2, 7, 13, 0, 34, 47, 11, 0};
using Indices = array<int, k - 1>;

Indices precalculateIndices(const array<int, n> &S, int k);

int findKthSmallest(array<int, n> &S, int p, int r, int index);

void kthQuantiles(array<int, n> &S, int p, int r, Indices &indices, int s, int t);

int randomized_partition(array<int, n> &S, int p, int r);

int main()
{
    Indices indices = precalculateIndices(S, k);
    kthQuantiles(S, 0, n - 1, indices, 0, k - 2);
}

int randomized_partition(array<int, n> &S, int p, int r)
{
    auto pivot{S.at(r)};
    auto i{p - 1};
    for (auto j = p; j < r; j++)
    {
        if (S.at(j) <= pivot)
        {
            auto t = S.at(++i);
            S.at(i) = S.at(j);
            S.at(j) = t;
        }
    }
    S.at(r) = S.at(i + 1);
    S.at(i + 1) = pivot;
    return i + 1;
}

int findKthSmallest(array<int, n> &S, int p, int r, int index)
{
    if (p > r)
    {
        printf("warning, not finding %u-th samllest\n", index);
        return 0;
    }
    auto q = randomized_partition(S, p, r);
    if (q == index)
    {
        return S.at(q);
    }
    if (q < index)
    {
        return findKthSmallest(S, q + 1, r, index);
    }
    return findKthSmallest(S, p, q - 1, index);
}

void kthQuantiles(array<int, n> &S, int p, int r, Indices &indices, int s, int t)
{
    if (p > r or s > t)
    {
        return;
    }
    auto index = indices.at((s + t) / 2);
    int quantile = findKthSmallest(S, p, r, index);
    printf("quantile at %u : %u \n", index, quantile);
    kthQuantiles(S, p, index - 1, indices, s, (s + t) / 2 - 1);
    kthQuantiles(S, index + 1, r, indices, (s + t) / 2 + 1, t);
}

Indices precalculateIndices(const array<int, n> &S, int k)
{
    Indices indices{};
    vector<int> numOfElements(k, n / k);
    fill(numOfElements.begin() + k - n % k, numOfElements.end(), n / k + 1);
    for (int i = 1; i < k; i++)
    {
        numOfElements.at(i) = numOfElements.at(i) + numOfElements.at(i - 1);
    }
    numOfElements.pop_back();
    for_each(numOfElements.begin(), numOfElements.end(), [](auto &x)
             { x -= 1; });

    printf("precalculateIndices --> {");
    for (int i = 0; i < k - 1; i++)
    {
        printf("%u ", numOfElements.at(i));
    }
    printf("}\n");

    copy(numOfElements.begin(), numOfElements.end(), indices.begin());
    return indices;
}
