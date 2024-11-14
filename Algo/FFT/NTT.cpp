#include <bits/stdc++.h>
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()
using namespace std;
using ll = long long;

int pwm(ll a, ll pow, int MD) {
	if (pow < 0) {
		pow = pow % (MD - 1) + MD - 1;
	}
	ll res = 1;
	while (pow) {
		if (pow & 1) {
			res = res * a % MD;
		}
		a = a * a % MD;
		pow >>= 1;
	}
	return res;
}
int inv(ll r, int P) { 
	return pwm(r % P, P - 2, P);
}

const int P = 998'244'353;

namespace NTT {
    const int CL = 20;
    const int SZ = (1 << CL);
	const int G = 3; // For P = 119 * 2^23 + 1
	int L;
	int N, IN;
	int W0, WI;

	int a[SZ], b[SZ];
	int rev[SZ];

	void ntt(int *a, bool inv) {
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
			int w = pwm((inv ? WI : W0), 1 << (L - lg - 1), P);
			assert(pwm(w, bl, P) != 1);
			assert(pwm(w, 2 * bl, P) == 1);
			for (int pos = 0; pos < N; pos += bl) {
				int ww = 1;
				for (int _ = 0; _ < bl; ++_, ++pos) {
					int tmp = (a[pos] + ll(ww) * a[pos + bl] % P) % P;
					a[pos + bl] = (a[pos] + P - ll(ww) * a[pos + bl] % P) % P;
					a[pos] = tmp;
					ww = ll(ww) * w % P;
				}
			}
		}
		if (inv) {
			for (int i = 0; i < N; ++i) {
				a[i] = ll(a[i]) * IN % P;
			}
		}
	}

	vector<int> mult(const vector<int> &aa, const vector<int> &bb) {
		L = 0, N = 1;
		while (N < 2 * max(sz(aa), sz(bb))) N <<= 1, ++L;
		W0 = pwm(G, 119 * (1 << (23 - L)), P); // For P = 119 * 2^23 + 1
		WI = inv(W0, P);
		IN = inv(N, P);
		memset(a, 0, sizeof(a[0]) * N);
		memset(b, 0, sizeof(b[0]) * N);
		copy(all(aa), a);
		copy(all(bb), b);
		ntt(a, false);
		ntt(b, false);
		for (int i = 0; i < N; ++i) {
			a[i] = ll(a[i]) * b[i] % P;
		}
		ntt(a, true);
		int n = sz(aa) + sz(bb) - 1;
		vector<int> ans(a, a + n);
		return ans;
	}
};
