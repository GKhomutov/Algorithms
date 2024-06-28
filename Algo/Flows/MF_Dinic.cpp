// O(N^2 * M) but in fact is much faster 
// O(min{N^(2/3), sqrt(M)} * M) with 0-1 capacities
// O(N * M * logC) using binary scaling

#include <bits/stdc++.h>
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()
#define mineq(x, y) (x) = min((x), (y))
#define maxeq(x, y) (x) = max((x), (y))
using namespace std;
using ll = long long;


struct Edge{
    int fr, to;
    ll cap, f;
    Edge() {}
    Edge(int u, int v, ll cap, ll f = 0) : fr(u), to(v), cap(cap), f(f) {}
};


struct Dinic {
    int N;
    int S, T;
    vector<Edge> e;
    vector<vector<int>> g;
    vector<ll> dist;
    vector<int> ptr;

    Dinic(int n, int s = -1, int t = -1) : N(n), g(n), dist(n), ptr(n), S(s), T(t) {}

    void add_edge(int u, int v, ll cap) {
        g[u].push_back(sz(e));
        e.emplace_back(u, v, cap);
        g[v].push_back(sz(e));
        e.emplace_back(v, u, 0);
    }

    bool bfs() {
        queue<int> q({S});
        fill(all(dist), N);
        dist[S] = 0;
        while(!q.empty()) {
            int u = q.front(); q.pop();
            if (u == T) break;
            for (int k : g[u]) {
                Edge &ed = e[k];
                if (ed.f < ed.cap && dist[ed.to] > dist[ed.fr] + 1) {
                    dist[ed.to] = dist[ed.fr] + 1;
                    q.push(ed.to);
                }
            }
        }
        return dist[T] != N;
    }

    // blocking flow finding O(N * M)
    ll dfs(int v, ll f = -1) {
        if (v == T) {
            return f;
        }
        ll pushed = 0;
        for (; ptr[v] < sz(g[v]); ++ptr[v]) {
            Edge &ed = e[g[v][ptr[v]]];
            Edge &edr = e[g[v][ptr[v]] ^ 1];
            if (ed.cap == ed.f || dist[ed.to] != dist[v] + 1) {
                continue;
            }
            ll amt = ed.cap - ed.f;
            if (f != -1) mineq(amt, f);
            ll add = dfs(ed.to, amt);
            f -= add;
            ed.f += add;
            edr.f -= add;
            pushed += add;
            if (f == 0) {
                break;
            }
        }
        return pushed;
    }

    // O(N^2 * M)
    ll max_flow(int s = -1, int t = -1) {
        if (s != -1) S = s;
        if (t != -1) T = t;
        ll flow = 0;
        // <= N iterations
        while (bfs()) {
            fill(all(ptr), 0);
            flow += dfs(S);
        }
        return flow;
    }
};

/*----------------------------------------Dinic with scaling---------------------------------------------------*/

struct Dinic {
    int N;
    int S, T;
    vector<Edge> e;
    vector<vector<int>> g;
    vector<ll> dist;
    vector<int> ptr;

    Dinic(int n, int s = -1, int t = -1): N(n), g(n), dist(n), ptr(n), S(s), T(t) {}

    void add_edge(int u, int v, ll cap) {
        g[u].push_back(sz(e));
        e.emplace_back(u, v, cap);
        g[v].push_back(sz(e));
        e.emplace_back(v, u, 0);
    }

    bool bfs(ll lim) {
        queue<int> q({S});
        fill(all(dist), N);
        dist[S] = 0;
        while(!q.empty()) {
            int u = q.front(); q.pop();
            if (u == T) break;
            for (int k : g[u]) {
                Edge &ed = e[k];
                if (ed.cap - ed.f >= lim && dist[ed.to] > dist[ed.fr] + 1) {
                    dist[ed.to] = dist[ed.fr] + 1;
                    q.push(ed.to);
                }
            }
        }
        return dist[T] != N;
    }

    // blocking flow finding O(N + M)
    ll dfs(int v, ll lim, ll f = -1) {
        if (v == T) {
            return f;
        }
        ll pushed = 0;
        for (; ptr[v] < sz(g[v]); ++ptr[v]) {
            Edge &ed = e[g[v][ptr[v]]];
            Edge &edr = e[g[v][ptr[v]] ^ 1];
            if (ed.cap - ed.f < lim || dist[ed.to] != dist[v] + 1) {
                continue;
            }
            ll add = dfs(ed.to, lim, lim);
            f -= add;
            ed.f += add;
            edr.f -= add;
            pushed += add;
            if (f == 0) {
                break;
            }
        }
        return pushed;
    }

    // O(N * M * logC)
    ll max_flow(int s = -1, int t = -1) {
        if (s != -1) S = s;
        if (t != -1) T = t;
        ll flow = 0;
        for (ll lim = (1ll << 62); lim >= 1; lim >>= 1) {
            while (bfs(lim)) {
                fill(all(ptr), 0);
                flow += dfs(S, lim);
            }
        }
        return flow;
    }
};
