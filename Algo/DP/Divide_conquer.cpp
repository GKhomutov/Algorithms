#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
using ll = long long;

/*
    opt(i, k) <= opt(i + 1, k)
*/

vector<ll> dp_prev, dp;

// [l; r), [optl; optr]
void go(int l, int r, int optl, int optr) {
    if (l >= r) return;
    int mid = (l + r) / 2;
    pair<ll, int> best = {LLONG_MAX, -1};
    for (int i = optl; i <= optr && i < mid; ++i) {
        // best = min(best, {dp_prev[i] + C(i, mid), i});
    }
    dp[mid] = best.fi;
    int opt = best.se;
    go(l, mid, optl, opt);
    go(mid + 1, r, opt, optr);
}

ll calc_dp(int n, int k) {
    dp.assign(n + 1, 0);
    for (int i = 0; i <= n; ++i) {
        // dp[i] = C(0, i);
    }
    for (int i = 1; i <= k; ++i) {
        dp_prev = dp;
        go(1, n + 1, 0, n);
    }
    ll res = dp[n];
    return res;
}
