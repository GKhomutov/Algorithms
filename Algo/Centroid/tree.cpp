#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
using namespace std;


const int N = 200'002;
int a[N];
vector<pair<int, int>> g[N];
int sz[N];
bool kil[N];

struct Info {};
vector<pair<int, int>> par[N];
vector<Info> info[N];

void dfs_sz(int v, int p) {
    sz[v] = 1;
    for (auto [to, _] : g[v]) {
        if (to == p || kil[to]) continue;
        dfs_sz(to, v);
        sz[v] += sz[to];
    }
}

int get_centroid(int v, int p, int n) {
    for (auto [to, _] : g[v]) {
        if (to == p || kil[to] || sz[to] <= n / 2) continue;
        return get_centroid(to, v, n);
    }
    return v;
}

void add_parent(int v, int p, int cur, int c) {
    par[v].push_back({c, cur});
    for (auto [to, w] : g[v]) {
        if (to == p || kil[to]) continue;
        add_parent(to, v, cur + w, c);
    }
}

void build_cent_tree(int v) {
    dfs_sz(v, -1);
    int c = get_centroid(v, -1, sz[v]);
    kil[c] = true;
    add_parent(c, -1, 0, c);
    for (auto [to, _] : g[c]) {
        if (!kil[to]) build_cent_tree(to);
    }
}

void query(int v) {
    for (auto [p, w] : par[v]) {
        
    }
}
