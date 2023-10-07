#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
using namespace std;
using ll = long long;

/* O(MlogM)*/
const int N = 100'005;
int par[N];
int rk[N];
int find_t(int v) {
    if (v == par[v]) return v;
    return par[v] = find_t(par[v]);
}
bool unite(int a, int b) {
    a = find_t(a), b = find_t(b);
    if (a == b) return false;
    if (rk[a] < rk[b])
        swap(a, b);
    par[b] = a;
    if (rk[a] == rk[b])
        ++rk[a];
    return true;
}
vector<int> mst[N];
ll built_mst(vector<pair<ll, pair<int, int>>>& e) {
    iota(par, par + N, 0);
    fill(rk, rk + N, 0);
    sort(all(e));
    ll weight = 0;
    for (auto [w, verts] : e) {
        auto [a, b] = verts;
        if (unite(a, b)) {
            mst[a].push_back(b);
            mst[b].push_back(a);
            weight += w;
        }
    }
    return weight;
}
