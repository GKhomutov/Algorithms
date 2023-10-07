#include <bits/stdc++.h>

using namespace std;


const int N = 100'005;
vector<int> g[N];
vector<int> ht(N, -1);
int fup[N];

/* Simple undirected connected graph */
void dfs(int v, int h = 0, int p = -1)
{
    ht[v] = fup[v] = h;
    // int children = 0;
    for (int to : g[v]) {
        if (to == p) continue;
        if (ht[to] == -1) {
            dfs(to, h + 1, v);
            // if (ht[to] <= fup[to])
            //     (v, to) is a bridge
            // if (ht[v] <= fup[to] && p != -1)
            //     v is a cut point
            // ++children;
            fup[v] = min(fup[v], fup[to]);
        } else {
            fup[v] = min(fup[v], ht[to]);
        }
    }
    // if (p == -1 && children > 1)
    //     v is a cut point
}
