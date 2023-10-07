/* Weights are non-negative */
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll INF = LLONG_MAX;
const int N = 100'005;
vector<pair<int, ll>> g[N];
vector<ll> dist(N, INF);
/* O(MlogM)*/
void dijkstra(int st)
{
    dist[st] = 0;
	priority_queue<pair<ll,int>> q;
	q.push({0, st});
	while (!q.empty())
    {
        auto [dist_v, v] = q.top(); q.pop();
		if (-dist_v > dist[v]) continue;
        for (auto [to, len] : g[v]) {
			if (dist[v] + len < dist[to]) {
				dist[to] = dist[v] + len;
				q.push({-dist[to], to});
			}
		}
	}
}
