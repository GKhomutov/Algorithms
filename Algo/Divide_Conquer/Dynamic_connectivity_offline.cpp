#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
#define fi first
#define se second
using namespace std;
using ll = long long;

struct Change {
    int v; bool ad;
    Change(int vv = -1, bool add = 0) : v(vv), ad(add) {}
};
vector<Change> st;

const int N = 10'005;
int par[N];
int rk[N];
int find_t(int v) {
    if (v == par[v]) return v;
    return find_t(par[v]);
}
void unite(int a, int b) {
    a = find_t(a);
    b = find_t(b);
    if (a == b) {
        st.push_back(Change());
        return;
    }
    if (rk[a] < rk[b]) swap(a, b);
    bool ad = false;
    par[b] = a;
    if (rk[a] == rk[b]) {
        ad = true;
        ++rk[a];
    }
    st.push_back(Change(b, ad));
}
void undo() {
    assert(!st.empty());
    auto ch = st.back(); st.pop_back();
    if (ch.v == -1) return;
    if (ch.ad) --rk[par[ch.v]];
    par[ch.v] = ch.v;
}

const int Q = 10'005;
pair<int, int> que[Q]; // if elem is negative, erase edge, else add edge

// ed -- edges present in the graph (not in DSU!) but removed on [l;r)
void go(int l, int r, vector<pair<int, int>> &ed)
{
    if (r - l == 1) {
        assert(ed.size() <= 1);
        if (ed.empty()) {
            assert(que[l].fi > 0);
            unite(que[l].fi, que[l].se);
            // answer
            undo();
        } else {
            assert(que[l].fi < 0);
            // answer
        }
        return;
    }
    int m = (r + l) >> 1;

    {
        // edges present in the graph (not in DSU!) and not removed in the left half
        set<pair<int, int>> remain(all(ed));
        for (int i = l; i < m; ++i) {
            if (que[i].fi < 0) {
                remain.erase({-que[i].fi, -que[i].se});
            }
        }
        // edges present in the graph (not in DSU!) and removed in the left half
        vector<pair<int, int>> ned;
        int cnt = 0;
        for (const auto &p : ed) {
            if (remain.contains(p)) {
                ++cnt;
                unite(p.fi, p.se);
            } else {
                ned.push_back(p);
            }
        }
        go(l, m, ned);
        while (cnt--) undo();
    }

    // edges present in the graph (not in DSU!) but possibly removed in the right half
    set<pair<int, int>> to_ad(all(ed)); 
    for (int i = l; i < m; ++i) {
        if (que[i].fi > 0) {
            to_ad.insert(que[i]);
        } else {
            to_ad.erase({-que[i].fi, -que[i].se});
        }
    }
    ed = vector<pair<int, int>>(all(to_ad));

    {
        // edges present in the graph (not in DSU!) and not removed in the right half
        set<pair<int, int>> remain(all(ed)); 
        for (int i = m; i < r; ++i) {
            if (que[i].fi < 0) {
                remain.erase({-que[i].fi, -que[i].se});
            }
        }
        // edges present in the graph (not in DSU!) and removed in the right half
        vector<pair<int, int>> ned;
        int cnt = 0;
        for (const auto &p : ed) {
            if (remain.contains(p)) {
                ++cnt;
                unite(p.fi, p.se);
            } else {
                ned.push_back(p);
            }
        } 
        go(m, r, ned);
        while (cnt--) undo();
    }
}
