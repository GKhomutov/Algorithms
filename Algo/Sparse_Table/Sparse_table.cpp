#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
using namespace std;
using ll = long long;

struct Func {
    vector<T> operator()(const vector<U> &x) const {

    }
    T operator()(const T &x, const T &y) const {

    }
};

template <typename T, typename U, class Func>
struct SparseTable
{
    Func F;
    int n, l;
    vector<vector<T>> t;
    vector<int> logs;

    SparseTable(const vector<U> &a) : n(a.size()), logs(vector<int>(n + 1))
    {
        logs[0] = -1; for (int i = 1; i <= n; ++i) logs[i] = logs[i>>1] + 1;
        l = logs[n] + 1;
        t.assign(l, vector<T>(n));
        t[0] = F(a);
        for (int i = 1; i < l; ++i)
            for (int j = 0; j + (1<<i) <= n; ++j)
                t[i][j] = F(t[i - 1][j], t[i - 1][j + (1<<(i-1))]);
    }
    // [l;r)
    T get(int l, int r) const {
        int lg = logs[r - l];
        return F(t[lg][l], t[lg][r - (1<<lg)]);
    }
};
