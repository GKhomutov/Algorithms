/* THEORY */

// f,g are unimodal => max(f, g) is unimodal
// f,g are convex => f + g is convex

// f(x_1,..,x_n) is convex in convex set X => g(x1,..x_(n-1)) := max_y(f(x1,..,x_(n-1), y)) is convex in X'


#include <bits/stdc++.h>

using namespace std;

using ld = double;
const ld PHI = 1. / numbers::phi;


/* 1/3, classic */ 
pair<ld, ld> get_min(ld g(ld), ld l, ld r, int ITER = 70)
{
    while (ITER--) {
        ld m1 = l + (r - l) / 3;
        ld m2 = r - (r - l) / 3;
        if (g(m1) < g(m2)) {
            r = m2;
        } else {
            l = m1;
        }
    }
    ld ans = (l + r) / 2;
    return {ans, g(ans)}; 
}


/* PHI, golden ratio */
pair<ld, ld> get_min(ld g(ld), ld l, ld r, int ITER = 70)
{
    ld m1 = r - PHI * (r - l);
    ld m2 = l + PHI * (r - l);
    ld g1 = g(m1);
    ld g2 = g(m2);
    while (ITER--) {
        if (g1 < g2) {
            r = m2;
            m2 = m1, g2 = g1;
            m1 = r - PHI * (r - l);
            g1 = g(m1);
        } else {
            l = m1;
            m1 = m2, g1 = g2;
            m2 = l + PHI * (r - l);
            g2 = g(m2);
        }
    }
    if (g2 < g1) m1 = m2, g1 = g2;
    return {m1, g1};
}


/* Integer */
template<typename T>
pair<T, T> get_min(T g(T), T l, T r)
{
    while (l - r > 2) {
        T m1 = l + (r - l) / 3;
        T m2 = r - (r - l) / 3;
        if (g(m1) < g(m2)) {
            r = m2;
        } else {
            l = m1;
        }
    }
    pair<T, T> ans = {r, g(r)};
    for (T x = l; x < r; ++x) {
        T gx = g(x);
        if (gx < ans.second)
            ans = {x, gx};
    }
    return ans;
}

