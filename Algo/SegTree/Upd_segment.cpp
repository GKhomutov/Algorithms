#include <bits/stdc++.h>

using namespace std;
using ll = long long;


// sum_t(1, 0, n, l, r)    --- calculate a[l] + ... + a[r - 1]
// add_t(1, 0, n, l, r, x) --- do a[i] += x for i in [l, r)
 
const int N = 100'057;
ll t[4 * N];
ll p[4 * N];
 
void push_t(int v, int l, int r) {
    t[v] += p[v] * (r - l);
    if (r - l != 1) {
        p[v << 1] += p[v];
        p[v << 1 | 1] += p[v];
    }
    p[v] = 0;
}
 
void build_t(int v, int l, int r, const vector<ll>& a) {
    if (r - l == 1) {
        t[v] = a[l];
        return;
    }
    build_t(   v << 1,        l,     (l + r) >> 1, a);
    build_t(v << 1 | 1, (l + r) >> 1,       r,     a);
    t[v] = t[v << 1] + t[v << 1 | 1];
}
 
ll sum_t(int v, int l, int r, int L, int R) {
    push_t(v, l, r);
    if (L >= r || l >= R) {
        return 0LL;
    }
    if (L <= l && r <= R) {
        return t[v];
    }
    return sum_t(   v << 1,        l,    (l + r) >> 1, L, R) +
           sum_t(v << 1 | 1, (l + r) >> 1,      r,     L, R);
}
 
void add_t(int v, int l, int r, int L, int R, int VL) {
    push_t(v, l, r);
    if (L >= r || l >= R) {
        return;
    }
    if (L <= l && r <= R) {
        p[v] += VL;
        push_t(v, l, r);
        return;
    }
    add_t(  v << 1,         l,    (l + r) >> 1, L, R, VL);
    add_t(v << 1 | 1, (l + r) >> 1,      r,     L, R, VL);
    t[v] = t[v << 1] + t[v << 1 | 1];
}
