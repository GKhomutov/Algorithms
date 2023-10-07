/* Weights of edges may be negative! */
#include <bits/stdc++.h>
using namespace std;
using ll = long long;


/* O(N^2) */
const ll INF = LLONG_MAX;
const int N = 10'005;
int n;
ll g[N][N]; // INF if no such edge
vector<int> mst[N];
// vertex numeration: 1..n
ll built_mst()
{
	vector<bool> used(n+1, false);
	vector<ll> min_e(n+1, INF);
	vector<int> sel_e(n+1, -1);
	min_e[1] = 0;
	ll weight = 0;
	for (int i = 1; i <= n; ++i) {
		int v = -1;
		for (int j = 1; j <= n; ++j)
			if (!used[j] && (v == -1 || min_e[j] < min_e[v]))
				v = j;
        assert(min_e[v] != INF); // disconnected graph
		used[v] = true;
		if (sel_e[v] != -1) {
			mst[v].push_back(sel_e[v]);
			mst[sel_e[v]].push_back(v);
			weight += min_e[v];
		}
		for (int to = 1; to <= n; ++to) {
			if (g[v][to] < min_e[to]) {
				min_e[to] = g[v][to];
				sel_e[to] = v;
			}
		}
	}
	return weight;
}



/* O(MlogN) */
const ll INF = LLONG_MAX;
const int N = 100'005;
int n;
vector<pair<int, ll>> g[N]; // {to, weight}
vector<int> mst[N];
// vertex numeration: 1..n
ll built_mst()
{
    vector<ll> min_e(n+1, INF);
    vector<int> sel_e(n+1, -1);
    min_e[1] = 0;
    set<pair<ll, int>> q;
    q.insert({0, 1});
    ll weight = 0;
    for (int _ = 0; _ < n; ++_) {
        assert(!q.empty()); // disconnected graph
        int v = q.begin()->second;
        q.erase(q.begin());
        if (sel_e[v] != -1) {
            mst[v].push_back(sel_e[v]);
            mst[sel_e[v]].push_back(v);
            weight += min_e[v];
        }
        for (auto [to, w] : g[v]) {
            if (w < min_e[to]) {
                q.erase({min_e[to], to});
                min_e[to] = w;
                sel_e[to] = v;
                q.insert({min_e[to], to});
            }
        }
    }
}
