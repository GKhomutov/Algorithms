#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
#define mineq(x, y) (x) = min((x), (y))
using namespace std;
using ll = long long;


struct Line
{
    ll k, b;
    Line() {}
    Line(ll k, ll b): k(k), b(b) {}
    ll operator()(ll x) const { return k * x + b; }
};


struct LiChaoTree
{
    static const ll INF = LLONG_MAX;
    int n;
    vector<Line> t;
    vector<ll> pt;  // for coordinate compression

    LiChaoTree(int sz) {
        n = 1;
        while (n < sz) n <<= 1;
        t.resize(2 * n, {0, INF});
        pt.resize(2 * n);
        iota(all(pt), 0ll);
    }

    LiChaoTree(const vector<ll> &query_points) {
        n = 1;
        while (n < query_points.size()) n <<= 1;
        t.resize(2 * n, {0, INF});
        pt.resize(2 * n);
        auto it = copy(all(query_points), pt.begin());
        iota(it, pt.end(), query_points.back() + 1);
        assert(is_sorted(all(pt)) &&
               unique(all(pt)) == pt.end());
    }

    void add_line(Line line) {
        int v = 1;
        int l = 0, r = n;
        while (v < 2 * n) {
            int m = (l + r) / 2;
            bool lef = line(pt[l]) < t[v](pt[l]);
            bool mid = line(pt[m]) < t[v](pt[m]);
            if (mid) {
                swap(t[v], line);
            }
            if (lef != mid) {
                v = 2 * v;
                r = m;
            } else {
                v = 2 * v + 1;
                l = m;
            }
        }
    }

    ll get(int i) const {
        int v = n + i;
        ll res = t[v](pt[i]);
        for (int v = n + i; v != 0; v >>= 1){
            mineq(res, t[v](pt[i]));
        }
        return res;
    }
};
