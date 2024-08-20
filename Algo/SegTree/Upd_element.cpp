#include <bits/stdc++.h>

using namespace std;


template <class T, class Fun = function<T(const T &, const T &)>>
struct SegTree
{
    Fun f;
    vector<T> t;
    int n;

    SegTree(int sz, const Fun &g, T default_value = T()) : f(g)
    {
        n = 1;
        while (n < sz) n <<= 1;
        t.resize(2 * n, default_value);
    }

    SegTree(vector<T> &a, const Fun &g, T default_value = T()) : SegTree(a.size(), g, default_value)
    {
        copy(all(a), t.begin() + n);
        for (int i = n - 1; i != 0; --i) {
            t[i] = f(t[i << 1], t[i << 1 | 1]);
        }
    }

    void upd(int i, const T &x)
    {
        i += n;
        t[i] = f(t[i], x);
        for (i >>= 1; i != 0; i >>= 1) {
            t[i] = f(t[i << 1], t[i << 1 | 1]);
        }
    }
    
    // [l, r)
    T get(int l, int r) const
    {
        T resL = t[0], resR = t[0];
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) {
                resL = f(resL, t[l++]);
            }
            if (r & 1) {
                resR = f(t[--r], resR);
            }
        }
        return f(resL, resR);
    }
};
