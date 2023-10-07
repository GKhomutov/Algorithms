#include <bits/stdc++.h>
using namespace std;

struct Query {
    int ind;
    int l, r;
    Query(int i, int ll, int rr) : ind(i), l(ll), r(rr) {}
};
int n;
const int L = 17;
const int N = (1 << L);
T a[N];
int bits[N];
const int K = 1'000'000;
int ans[K];
int id[L + 1][N];
int ptr = 0;
vector<Query> q[2*N];

void go_id(int l, int r, int lvl, int code) {
    id[lvl][code] = ptr++;
    if (r - l == 1) return;
    int m = (l + r) / 2;
    go_id(l, m, lvl + 1, 2 * code);
    go_id(m, r, lvl + 1, 2 * code + 1);
}

void go(int l, int r, int lvl, int code)
{
    const auto &to_process = q[id[lvl][code]];
    if (r - l == 1) {
        for (const auto &que : to_process)
            // ans[que.ind] = ;
        return;
    }
    int m = (l + r) / 2;
    go(l, m, lvl + 1, 2*code);
    go(m, r, lvl + 1, 2*code + 1);

    // vector<T> suf(m - l + 1);
    // vector<T> pref(r - m + 1);
    // pref[0] = suf[0] = ...;
    // for (int i = 1; i <= m - l; ++i) {
    //     suf[i] = a[m-i] OPER suf[i-1];
    // }
    // for (int i = 1; i <= r - m; ++i) {
    //     pref[i] = pref[i-1] OPER a[m+i-1];
    // }
    
    for (auto &que : to_process) {
        // ans[que.ind] = ;
    }
}

void solve()
{
    bits[0] = 0;
    for (int i = 1; i < N; ++i)
        bits[i] = bits[i / 2] + 1;
    cin >> n;
    cin >> a;
    int len = (1 << bits[n]);
    go_id(0, len, 0, 0);
    int k; cin >> k;
    for (int i = 0; i < k; ++i) {
        int l, r; cin >> l >> r; --l; --r;
        int code = (l >> bits[l^r]);
        int lvl = bits[len - 1] - bits[l^r];
        q[id[lvl][code]].pb(Query(i, l, r + 1));
    }
    go(0, len, 0, 0);
}
