#include <bits/stdc++.h>
#define sz(x) (int)(x).size()
using namespace std;
using ld = long double;

// do not forget precalc()

namespace FFT
{
    struct cm {
        ld re, im;
        cm(ld x = 0, ld y = 0) : re(x), im(y) {}
        cm operator*(const cm &oth) const {return cm(re * oth.re - im * oth.im, re * oth.im + oth.re * im);}
        cm operator+(const cm &oth) const {return cm(re + oth.re, im + oth.im);}
        cm operator-(const cm &oth) const {return cm(re - oth.re, im - oth.im);}
    };

    const int CL = 20;
    const int SZ = (1 << CL);
    int L;
    int N;
    const ld PI = acosl(-1);

    cm a[SZ], b[SZ];
    cm w[SZ], wi[SZ];
    int rev[SZ];

    void precalc() {
        int ptr = 0;
        for (int lg = 0; lg < CL; ++lg) {
            int bl = (1 << lg);
            for (int i = 0; i < bl; ++i) {
                w[ptr] = cm(cos(i * PI / bl), sin(i * PI / bl));
                wi[ptr] = cm(w[ptr].re, -w[ptr].im);
                ++ptr;
            }
        }
    }

    void fft(cm *a, bool inv) {
        for (int i = 1; i < N; ++i) {
            rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (L - 1));
        }
        for (int i = 0; i < N; ++i) {
            if (i < rev[i]) {
                swap(a[i], a[rev[i]]);
            }
        }
        for (int lg = 0; lg < L; ++lg) {
            int bl = (1 << lg);
            for (int pos = 0; pos < N; pos += bl) {
                cm *ww = (inv ? wi : w) + bl - 1;
                for (int _ = 0; _ < bl; ++_, ++pos) {
                    cm tmp = a[pos] + *ww * a[pos + bl];
                    a[pos + bl] = a[pos] - *ww * a[pos + bl];
                    a[pos] = tmp;
                    ++ww;
                }
            }
        }
        if (inv) {
            for (int i = 0; i < N; ++i) {
                a[i].re /= N;
            }
        }
    }

    vector<ld> mult(const vector<int>& aa, const vector<int>& bb) {
        L = 0, N = 1;
        while (N < 2 * max(sz(aa), sz(bb))) N <<= 1, ++L;
        memset(a, 0, sizeof(a[0]) * N);
        for (int i = 0; i < sz(aa); ++i) {
            a[i].re = aa[i];
        }
        for (int i = 0; i < sz(bb); ++i) {
            a[i].im = bb[i];
        }
        fft(a, false);
        b[0] = {a[0].im, 0};
        for (int i = 1; i < N; ++i) {
            b[i] = { (a[i].im + a[N - i].im) / 2, (a[N - i].re - a[i].re) / 2 };
        }
        a[0] = {a[0].re, 0};
        for (int i = 1; i <= N / 2; ++i) {
            cm tmp = a[i];
            a[i] = { (a[i].re + a[N - i].re) / 2, (a[i].im - a[N - i].im) / 2 };
            a[N - i] = { (tmp.re + a[N - i].re) / 2, (a[N - i].im - tmp.im) / 2 };
        }
        for (int i = 0; i < N; ++i) {
            a[i] = a[i] * b[i];
        }

        fft(a, true);
        int n = sz(aa) + sz(bb) - 1;
        vector<ld> ans(n);
        for (int i = 0; i < n; ++i) {
            ans[i] = a[i].re;
        }
        return ans;
    }
};
