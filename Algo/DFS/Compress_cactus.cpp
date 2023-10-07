#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
using namespace std;


const int N = 100'005;
vector<int> g[N];
vector<bool> vis(N, false);
int p[N];
int idCnt = 1;
int id[N];
vector<int> gg[N]; // compressed graph
vector<bool> compressed(N, false);

void mark(int finish, int start) {
    for (int v = finish; v != start; v = p[v])
        id[v] = idCnt;
    id[start] = idCnt;
	compressed[idCnt++] = true;
}
 
void dfs_compress(int v, int par = -1) {
	vis[v] = true;
	p[v] = par;
    for (int to : g[v]) {
        if (to == par) continue;
        if (vis[to]) {
            if (id[to] == -1)
                mark(v, to);
        } else {
            dfs_compress(to, v);
        }
    }
}

// old graph is g, new graph is gg
void compress_cactus()
{
    fill(id, id + N, -1);
    dfs_compress(1);
    for (int v = 1; v < N; ++v) {
        if (id[v] == -1)
            id[v] = idCnt++;
    }
    for (int v = 1; v < N; ++v) {
        for (int to : g[v]) {
            if (id[v] != id[to]) {
                gg[id[v]].push_back(id[to]);
            }
        }
    }
}
