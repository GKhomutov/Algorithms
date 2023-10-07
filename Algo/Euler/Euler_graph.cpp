#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
using namespace std;


/* Directed graph */
const int N = 100'005;
vector<int> g[N];
/* O(N + M) */
vector<int> eul(int start)
{
    vector<int> ans;
    vector<int> ptr(N, 0);
    vector<int> st = {start};
    while (!st.empty())
    {
        int v = st.back();
        if (ptr[v] == g[v].size()) {
            ans.push_back(v);
            st.pop_back();
        } else {
            st.push_back(g[v][ptr[v]++]);
        }
    }
    reverse(all(ans));
    return ans;
}


vector<int> out(N, 0);
vector<int> in(N, 0);
vector<bool> used(N, false);
void dfs_is_eul(int v) {
	used[v] = true;
	for (int to : g[v]) if (!used[to]) dfs_is_eul(to);
}
// pass any valid vertex
bool is_eul(int& start) {
    int extr = 0;
    for (int i = 0; i < N; ++i) {
        if (in[i] == out[i])
            continue;
        if (abs(in[i]-out[i]) > 1 || ++extr > 2)
            return false;
        if (out[i] > in[i])
            start = i;
    }
	dfs_is_eul(start);
	for (int i = 0; i < N; ++i)
        if (in[i] && !used[i])
            return false;
    return true;
}





/* Undirected graph */
const int N = 100'005;
const int M = 100'005;
vector<pair<int, int>> e;
vector<int> g[N]; // g[v] - indices of edges incident to vertex v
/* O(N + M) */
vector<int> eul(int start)
{
    vector<int> ans;
    vector<bool> kil(M, false);
    vector<int> ptr(N, 0);
    vector<int> st = {start};
    while (!st.empty())
    {
        int v = st.back();
        while (ptr[v] < g[v].size() && kil[g[v][ptr[v]]])
            ++ptr[v];
        if (ptr[v] == g[v].size()) {
            ans.push_back(v);
            st.pop_back();
        } else {
            auto [a, b] = e[g[v][ptr[v]]];
            st.push_back(a ^ b ^ v);
            kil[g[v][ptr[v]]] = true;
        }
    }
    // reverse(all(ans));
    return ans;
}


vector<bool> used(N, false);
void dfs_is_eul(int v) {
	used[v] = true;
	for (int k : g[v]) {
        int to = e[k].first ^ e[k].second ^ v;
        if (!used[to])
            dfs_is_eul(to); 
    }
}
// pass any valid vertex
bool is_eul(int& start) {
    int extr = 0;
    for (int i = 0; i < N; ++i) {
        if (g[i].size() & 1) {
            if (++extr > 2)
                return false;
            start = i;
        }
    }
    dfs_is_eul(start);
    for (int i = 0; i < N; ++i)
        if (!g[i].empty() && !used[i])
            return false;
    return true;
}
