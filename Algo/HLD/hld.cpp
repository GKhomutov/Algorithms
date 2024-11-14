#include <bits/stdc++.h>
using namespace std;


const int N = 100'005;
SegTree<Info, Tag> hld(N);
vector<int> g[N];
int sz[N], par[N], head[N], tin[N], tout[N];

void dfs_sz(int v, int p = -1) {
    par[v] = p;
    sz[v] = 1;
    for (int &to : g[v]) {
        if (to == par[v]) continue;
        dfs_sz(to, v);
        sz[v] += sz[to];
        if (g[v][0] == par[v] || sz[to] > sz[g[v][0]]) {
            swap(to, g[v][0]);
        }
    }
}

int ti = 0;
void dfs_hld(int v) {
    if (par[v] == -1) head[v] = v;
    tin[v] = ti++;
    for (int to : g[v]) {
        if (to == par[v]) continue;
        head[to] = (to == g[v][0] ? head[v] : to);
        dfs_hld(to);
    }
    tout[v] = ti;
}

bool is_ancestor(int a, int b) {
    return tin[a] <= tin[b] && tin[b] < tout[a];
}

void upd(int v, const Info &x) {
    hld.upd(tin[v], x);
}

void up(int &a, int b, Info &ans) {
    while (!is_ancestor(head[a], b)) {
        ans = ans + hld.rangeQuery(tin[head[a]], tin[a] + 1);
        a = par[head[a]];
    }
}

Info get(int a, int b) {
    Info ans;
    up(a, b, ans);
    up(b, a, ans);
    if (!is_ancestor(a, b)) {
        swap(a, b);
    }
    ans = ans + hld.rangeQuery(tin[a], tin[b] + 1);
    return ans;
}

void apply_subtree(int v, const Tag &t) {
    hld.rangeApply(tin[v], tout[v], t);
}
