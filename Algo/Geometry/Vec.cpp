#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
using namespace std;
using ll = long long;
using ld = double;

/* THEORY */
// Line throught p and q is (p.y - q.y) * x - (p.x - q.x) * y + p % q = 0
// Pick's formula: S = В + Г/2 - 1


const ld PI = M_PI; // numbers::pi_v<ld>;

struct Vec
{
    ll x, y;
    Vec() {}
    Vec(ll x, ll y) : x(x), y(y) {}
    Vec& operator+=(const Vec &v) { x += v.x; y += v.y; return *this; }
    Vec operator+(const Vec &v) const { Vec sum = *this; sum += v; return sum; }
    Vec& operator-=(const Vec &v) { x -= v.x; y -= v.y; return *this; }
    Vec operator-(const Vec &v) const { Vec diff = *this; diff -= v; return diff; }
    Vec operator-() const { Vec v(-x, -y); return v; }
    ll operator*(const Vec &v) const { return x * v.x + y * v.y; }
    ll operator%(const Vec &v) const { return x * v.y - y * v.x; }
    bool operator==(const Vec &v) const { return x == v.x && y == v.y; }
    bool on_line(const Vec &a, const Vec &b) const { return this->square(a, b) == 0; }
    bool on_seg(const Vec &a, const Vec &b) const {
        const Vec &v = *this;
        return v.on_line(a, b) && ((v - a) * (v - b) <= 0);
    }
    ld angle(const Vec &v) const {
        ld alpha = atan2(*this % v, *this * v);
        return alpha < 0 ? alpha+2*PI : alpha;
    }
    ll square(const Vec &a, const Vec &b) const { return (a - (*this)) % (b - (*this)); }
};
bool LeftDownCmp(const Vec &u, const Vec &v) { return u.x < v.x || (u.x == v.x && u.y < v.y); }
Vec operator*(ll k, const Vec &v) { Vec u(k * v.x, k * v.y); return u; }
istream& operator>>(istream &s, Vec &v) { s >> v.x >> v.y; return s; }
ostream& operator<<(ostream &s, const Vec &v) { s << v.x << " " << v.y; return s; }
ll norm(const Vec &v) { return v.x * v.x + v.y * v.y; }
ld dist(const Vec &a, const Vec &b) { return sqrt(norm(b - a)); }
bool seg_line_int(const Vec &a, const Vec &b, const Vec &c, const Vec &d) {
    if (c.square(a, d) > 0 && c.square(b, d) > 0 ||
        c.square(a, d) < 0 && c.square(b, d) < 0)
        return false;
    return true;
}
bool seg_seg_int(const Vec &a, const Vec &b, const Vec &c, const Vec &d) {
    return seg_line_int(a, b, c, d) && seg_line_int(c, d, a, b);  
}

