#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
using namespace std;
using ll = long long;

struct FenwickTree
{
    vector<ll> t;
    int n;

    FenwickTree(int sz, ll val) : n(sz), t(vector<ll>(sz, val)) {}
    FenwickTree(const vector<ll> &a) : n(a.size()), t(a) {
        partial_sum(all(t), t.begin());
        for (int i = n-1; i > 0; --i) {
            int j = (i & (i+1)) - 1;
            if (j >= 0) t[i] -= t[j];
        }
    }
    ll get(int r) const {
        ll ans = 0;
        for (int i = r; i >= 0; i = (i & (i + 1)) - 1) {
            ans += t[i];
        }
        return ans;
    }
    // [l;r]
    ll get(int l, int r) const { 
        return get(r) - get(l-1);
    }
    void inc(int i, ll d) {
        for (int j = i; j < n; j |= j + 1) {
            t[j] += d;
        }
    }
};
