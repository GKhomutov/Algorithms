#include <bits/stdc++.h>

using namespace std;


const int N = 100'057;
const int L = 17; // (1 << L) > N is needed
vector<int> g[N];
int ht[N];
int la[N][L];

// Call dfs_init(root, root)
void dfs_init(int v, int p, int h = 0)
{ 
	ht[v] = h;
	la[v][0] = p;
	for (int lg = 1; lg < L; ++lg) {
		la[v][lg] = la[la[v][lg - 1]][lg - 1];
	}
	for (auto u : g[v]) {
		if (u != p) {
			dfs_init(u, v, h + 1);
		}
	}
}

// run dfs_init before calling this!
int lca(int u, int v)
{
	if (ht[u] > ht[v]) {
		swap(u, v);
	}
	int dh = ht[v] - ht[u];
	for (int i = 0; i < L; ++i) {
		if ((dh >> i) & 1) {
			v = la[v][i];
		}
	}
	if (u == v) {
		return u;
	}
	for (int i = L - 1; i >= 0; --i) {
		if (la[u][i] != la[v][i]) {
			u = la[u][i];
			v = la[v][i];
		}
	}
	return la[u][0];
}
