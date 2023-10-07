#include "Vec.cpp"

int n;
const int N = 100'005;
Vec a[N];
// Checks if a point lies in the interior of a convex polygon.
// Polygon 'a' is clockwise ordered starting from left down.
bool is_inside(const Vec &q) 
{
    if (q.x <= a[0].x) {
        return false;
    }
    auto AngleCmp = [&](const Vec &u, const Vec &v) {
        return a[0].square(u, v) < 0;
    };
    if (!AngleCmp(a[1], q) || !AngleCmp(q, a[n-1])) {
        return false;
    }
    int r = upper_bound(a+1, a+n, q, AngleCmp) - a;
    if (seg_line_int(a[0], q, a[r - 1], a[r])) {
        return false;
    }
    return true;
}
void solve()
{
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i];
    rotate(a, min_element(a, a+n, LeftDownCmp), a+n);
}
