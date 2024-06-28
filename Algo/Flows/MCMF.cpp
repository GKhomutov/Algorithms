#include <bits/stdc++.h>
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()
#define mineq(x, y) (x) = min((x), (y))
#define maxeq(x, y) (x) = max((x), (y))
using namespace std;
using ll = long long;


struct Edge{
    int fr, to;
    ll cap, f, w;
    Edge() {}
    Edge(int u, int v, ll cap, ll w, ll f = 0) : fr(u), to(v), cap(cap), w(w), f(f) {}
};
ll INF = 1e15;
struct Dinic {
    int N;
    int S, T;
    vector<Edge> e;
    vector<vector<int>> g;
    vector<ll> dist;
    vector<bool> in_q;
    vector<int> par_e;

    Dinic(int n, int s = -1, int t = -1) : N(n), g(n), dist(n), in_q(n), par_e(n), S(s), T(t) {}

    void add_edge(int u, int v, ll cap, ll w) {
        g[u].push_back(sz(e));
        e.emplace_back(u, v, cap, w);
        g[v].push_back(sz(e));
        e.emplace_back(v, u, 0, -w);
    }

    bool calc_dist() {
        fill(all(dist), INF);
        fill(all(in_q), false);
        fill(all(par_e), -1);
        queue<int> q;
        q.push(S);
        dist[S] = 0;
        while (!q.empty())
        {
            int v = q.front(); q.pop();
            in_q[v] = false;
            for (int k : g[v]) {
                const Edge &ed = e[k];
                if (ed.f == ed.cap) continue;
                if (dist[ed.to] > dist[ed.fr] + ed.w) {
                    dist[ed.to] = dist[ed.fr] + ed.w;
                    par_e[ed.to] = k;
                    if (!in_q[ed.to]) {
                        q.push(ed.to);
                        in_q[ed.to] = true;
                    }
                }
            }
        }
        return dist[T] != INF;
    }

    pair<ll, ll> push_t() {
        ll pushed = INF;
        for (int v = T; v != S; ) {
            const Edge &ed = e[par_e[v]];
            mineq(pushed, ed.cap - ed.f);
            v = ed.fr;
        }
        ll cost = 0;
        for (int v = T; v != S; ) {
            Edge &ed = e[par_e[v]];
            Edge &edr = e[par_e[v] ^ 1];
            ed.f += pushed;
            edr.f -= pushed;
            cost += ed.w * pushed;
            v = ed.fr;
        }
        return {pushed, cost};
    }

    pair<ll, ll> min_cost_max_flow(int s = -1, int t = -1) {
        if (s != -1) S = s;
        if (t != -1) T = t;
        ll flow = 0;
        ll cost = 0;
        while (calc_dist()) {
            auto [f, cst] = push_t();
            flow += f;
            cost += cst;
        }
        return {flow, cost};
    }
};
