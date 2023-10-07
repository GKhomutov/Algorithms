#include <bits/stdc++.h>

#define all(v) (v).begin(), (v).end()

using namespace std;
using ull = unsigned long long;

template <class RandomIt>
void Merge(RandomIt l1, RandomIt r1, RandomIt l2, RandomIt r2, RandomIt res, ull &inv)
{
    for (; l2 != r2; ++l2, ++res) {
        while (l1 != r1 && *l1 <= *l2) {
            *res = *l1;
            ++res;
            ++l1;
        }
        *res = *l2;
        inv += r1 - l1;
    }
    for (; l1 != r1; ++l1, ++res) {
        *res = *l1;
    }
}

template <class RandomIt>
void MergeSort(RandomIt l, RandomIt r, ull &inv)
{
    typedef typename iterator_traits<RandomIt>::value_type T;
    if (r - l <= 1) {
        return;
    }
    auto mid = l + (r - l) / 2;
    MergeSort(l, mid, inv);
    MergeSort(mid, r, inv);
    vector<T> buf(r - l);
    Merge(l, mid, mid, r, buf.begin(), inv);
    copy(all(buf), l);
}


