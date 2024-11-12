#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Line {
    ll k, b;
    mutable const Line *nx;
    ll operator()(ll x) const {
        return k * x + b;
    }
    bool operator<(ll x) const {
        if (!nx) return false;
        return (*this)(x) < (*nx)(x);
    }
    bool operator<(const Line& rhs) const {
        return k < rhs.k;
    }
};
// will maintain upper hull for maximum
struct DynamicCHT : multiset<Line, less<>> {
    bool bad(iterator y) {
        auto z = next(y);
        if (y == begin()) {
            if (z == end()) return false;
            return y->k == z->k && y->b <= z->b;
        }
        auto x = prev(y);
        if (z == end()) return y->k == x->k && y->b <= x->b;
        return __int128_t(x->b - y->b)*(z->k - y->k) >= __int128_t(y->b - z->b)*(y->k - x->k);
    }
    void insert_line(ll k, ll b) {
        auto y = insert({k, b, nullptr});
        if (bad(y)) {
            erase(y);
            return;
        }
        auto z = next(y);
        while (z != end() && bad(z)) z = erase(z);
        if (z != end()) y->nx = &*z;
        while (y != begin() && bad(z = prev(y))) erase(z);
        if (y != begin()) z->nx = &*y;
    }
    ll eval(ll x) {
        auto line = *lower_bound(x);
        return line(x);
    }
};
