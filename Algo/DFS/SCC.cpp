#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
using namespace std;


/* O(N + M) */
const int N = 100'005;
vector<int> g[N];
vector<int> gr[N]; // reversed graph
vector<bool> used(N, false);
vector<int> order;
void dfs_ord(int v) {
    used[v] = true;
    for (int to : g[v])
        if (!used[to])
            dfs_ord(to);
    order.push_back(v);
}
vector<int> component;
void dfs_comp(int v) {
    used[v] = true;
    component.push_back(v);
    for (int to : gr[v])
        if (!used[to])
            dfs_comp(to);
}

void solve() {
    int n;
    for (int i = 1; i <= n; ++i)
        if (!used[i])
            dfs_ord(i);
    reverse(all(order));
    fill(all(used), false);
    for (int v : order) {
        if (used[v]) continue;
        dfs_comp(v);
        // component received!
        component.clear();
    }
}
