#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
using namespace std;


const int N = 200'002;
vector<int> g[N];
int sz[N];
bool kil[N];

void dfs_sz(int v, int p) {
    sz[v] = 1;
    for (int to : g[v]) {
        if (to == p || kil[to]) continue;
        dfs_sz(to, v);
        sz[v] += sz[to];
    }
}

int get_centroid(int v, int p, int n) {
    for (int to : g[v]) {
        if (to == p || kil[to] || sz[to] <= n / 2) continue;
        return get_centroid(to, v, n);
    }
    return v;
}

void calc(int v) {
    
}
 
void decompose(int v) {
    dfs_sz(v, -1);
    int c = get_centroid(v, -1, sz[v]);
    kil[c] = true;
    calc(c);
    for (auto to : g[c]) {
        if (!kil[to]) decompose(to);
    }
}

void solve() {
    decompose(1);
}
