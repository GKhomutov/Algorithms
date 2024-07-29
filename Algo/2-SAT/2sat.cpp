#include <bits/stdc++.h>

#define all(x) (x).begin(), (x).end()

using namespace std;

struct TwoSAT {
    int n;
    vector<vector<int>> g, gr;
    vector<int> comp, top_ord, answer;
    vector<bool> used;

    TwoSAT(int _n) : n(_n) {
        g.resize(2 * n);
        gr.resize(2 * n);
        comp.resize(2 * n);
        used.resize(2 * n);
        answer.resize(n);
    }

    void add_edge(int u, int v) {
        g[u].push_back(v);
        gr[v].push_back(u);
    }

    // At least one of them is true
    void add_or(bool fx, int x, bool fy, int y) {
        add_edge(x + fx * n, y + !fy * n);
        add_edge(y + fy * n, x + !fx * n);
    }

    // Only one of them is true
    void add_xor(bool fx, int x, bool fy, int y) {
        add_or(fx, x, fy, y);
        add_or(!fx, x, !fy, y);
    }

    // Both of them have the same value
    void add_eq(bool fx, int x, bool fy, int y) {
        add_xor(!fx, x, fy, y);
    }

    void dfs_top_ord(int v) {
        used[v] = true;
        for (int to : g[v]) {
            if (!used[to]) {
                dfs_top_ord(to);
            }
        }
        top_ord.push_back(v);
    }

    void get_top_ord() {
        fill(all(used), false);
        for (int v = 0; v < 2 * n; ++v) {
            if (!used[v]) {
                dfs_top_ord(v);
            }
        }
        reverse(all(top_ord));
    }

    void dfs_scc(int v, int id) {
        used[v] = true;
        comp[v] = id;
        for (int to : gr[v]) {
            if (!used[to]) {
                dfs_scc(to, id);
            }
        }
    }

    void get_scc() {
        get_top_ord();
        fill(all(used), false);
        int id = 0;
        for (int v : top_ord) {
            if (!used[v]) {
                dfs_scc(v, id++);
            }
        }
    }

    bool satisfiable() {
        get_scc();
        for (int i = 0; i < n; ++i) {
            if (comp[i] == comp[i + n]) {
                return false;
            }
            answer[i] = (comp[i] > comp[i + n]);
        }
        return true;
    }
};
