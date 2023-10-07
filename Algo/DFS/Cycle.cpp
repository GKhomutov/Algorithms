#include <bits/stdc++.h>

using namespace std;

const int N = 100'005;
vector<int> g[N];

/* Simple undirected connected graph */
vector<bool> used(N, false);
vector<int> cycle;
int dfs(int v, int p)
{
    used[v] = true;
    for (int i : g[v]) {
        if (i == p) continue;
        if (used[i]) {
            cycle.push_back(i);
            cycle.push_back(v);
            return i;
        }
        int res = dfs(i, v);
        if (res == -1) continue;
        if (res == -2) return -2;
        if (res == v) {
            cycle.push_back(v);
            return -2;
        }
        cycle.push_back(v);
        return res;
    }
    return -1;
}


/* Simple directed connected graph */
vector<char> used(N, 0);
vector<int> cycle;
int dfs(int v)
{
    used[v] = 1;
    for (int i : g[v]) {
        if (used[i] == 2) continue;
        if (used[i] == 1) {
            cycle.push_back(i);
            cycle.push_back(v);
            return i;
        }
        int res = dfs(i);
        if (res == -1) continue;
        if (res == -2) return -2;
        if (res == v) {
            cycle.push_back(v);
            return -2;
        }
        cycle.push_back(v);
        return res;
    }
    used[v] = 2;
    return -1;
}

