#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;


/* Classic */
const int P = 998'244'353;
const int N = 1'000'000;
int fact[N + 1];
int inv_fact[N + 1];

int binpow(int a, int n)
{
    int res = 1;
    while (n) {
        if (n & 1)
            res = ull(a) * res % P;
        a = ull(a) * a % P;
        n >>= 1;
    }
    return res;
}

void calc_fact()
{
    fact[0] = 1;
    for (ull i = 1; i <= N; i++)
        fact[i] = i * fact[i - 1] % P;
    inv_fact[N] = binpow(fact[N], P - 2);
    for (ull i = N; i > 0; i--)
        inv_fact[i - 1] = i * inv_fact[i] % P;
    // Do you want iversed numbers?
    // for (int i = 1; i <= N; ++i)
    //     inv[i] = ull(fact[i]) * inv_fact[i - 1] % P;
}

int C(int n, int k)
{
    return ull(fact[N]) * inv_fact[n - k] % P * inv_fact[k] % P;
}




/* Pascal's triangle */
const int N = 1'000;
const int MOD = 1'000'000;
int C[N + 1][N + 1];
void calc_bin_coeff() {
    for (int n = 0; n <= N; ++n) {
        C[n][0] = C[n][n] = 1;
        for (int k = 1; k < n; ++k)
            C[n][k] = (C[n - 1][k - 1] + C[n - 1][k]) % MOD;
    }
}

