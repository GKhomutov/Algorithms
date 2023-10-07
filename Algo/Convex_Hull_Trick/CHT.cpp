#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
using namespace std;
using ll = long long;


const ll INF = LLONG_MAX;
 
struct CHT
{
    struct Line {
        ll k, b;
        Line() {}
        Line(ll k, ll b): k(k), b(b) {}
        ll intersect(Line l) const {
            assert(k != l.k);
            assert(k != l.k);
            ll db = l.b - b;
            ll dk = k - l.k;
            if (dk < 0) db = -db, dk = -dk;
            if (db > 0) db += dk-1;
            return db / dk;
        }
        ll operator()(ll x) const { return k * x + b; }
    };
    
    vector<ll> x;
    vector<Line> lines;
    
    void addLine(Line l) {
        if (lines.empty()) {
            x.push_back(-INF);
            lines.push_back(l);
            return;
        }
        while (l.intersect(lines.back()) <= x.back()) {
            x.pop_back();
            lines.pop_back();
        }
        x.push_back(l.intersect(lines.back()));
        lines.push_back(l);
    }
    
    ll query(ll qx) const {
        assert(!x.empty());
        ll pos = upper_bound(all(x), qx) - x.begin() - 1;
        return lines[pos](qx);
    }
};
