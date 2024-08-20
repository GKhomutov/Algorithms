#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
using namespace std;
using ll = long long;
 
struct Line
{
    ll k, b;
    Line() {}
    Line(ll k, ll b): k(k), b(b) {}
    ll intersect(Line l) const {
        assert(k != l.k);
        ll db = l.b - b;
        ll dk = k - l.k;
        if (dk < 0) db = -db, dk = -dk;
        if (db > 0) db += dk-1;
        return db / dk;
    }
    ll operator()(ll x) const { return k * x + b; }
};

// k descending, get min
struct CHT
{
    static const ll INF = LLONG_MAX;
    vector<ll> x;
    vector<Line> lines;

    bool empty() const {
        return x.empty();
    }

    void pop_back() {
        x.pop_back();
        lines.pop_back();
    }
    
    void add_line(Line l) {
        if (empty()) {
            x.push_back(-INF); // +INF for max
            lines.push_back(l);
            return;
        }
        if (lines.back().k == l.k) {
            if (lines.back().b <= l.b) { // >= for max
                return;
            } else {
                pop_back();
            }
        }
        while (l.intersect(lines.back()) <= x.back()) { // >= for max
            pop_back();
        }
        x.push_back(l.intersect(lines.back()));
        lines.push_back(l);
    }
    
    ll get(ll qx) const {
        assert(!empty());
        ll pos = upper_bound(all(x), qx) - x.begin() - 1; // lower_bound greater{} for max
        return lines[pos](qx);
    }
};
