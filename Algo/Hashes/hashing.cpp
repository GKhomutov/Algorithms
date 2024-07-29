#include <bits/stdc++.h>

#define all(x) (x).begin(), (x).end()

using namespace std;
using ll = long long;

mt19937 rd(chrono::system_clock::now().time_since_epoch().count());


const int NP = 5;
int pr[NP];
bool is_prime(int n) {
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    for (int d = 3; ll(d) * d <= n; d += 2) if (n % d == 0) return false;
    return true;
}
void gen_primes() {
    const int L = 10'000;
    const int R = 10'000'000;
    for (int i = 0; i < NP; ++i) {
        pr[i] = L + rd() % (R - L);
        while (!is_prime(pr[i])) ++pr[i];
    }
}


using Hash = array<int, NP>;

Hash operator+(const Hash &a, const Hash &b) {
    Hash res;
    for (int i = 0; i < NP; ++i) res[i] = (a[i] + b[i]) % pr[i];
    return res;
}
Hash operator+(const Hash &a, int b) {
    Hash res;
    for (int i = 0; i < NP; ++i) res[i] = (a[i] + b) % pr[i];
    return res;
}
Hash operator-(const Hash &a, const Hash &b) {
    Hash res;
    for (int i = 0; i < NP; ++i) res[i] = (a[i] - b[i] + pr[i]) % pr[i];
    return res;
}
Hash operator*(const Hash &a, const Hash &b) {
    Hash res;
    for (int i = 0; i < NP; ++i) res[i] = (ll(a[i]) * b[i]) % pr[i];
    return res;
}
Hash operator*(const Hash &a, int b) {
    Hash res;
    for (int i = 0; i < NP; ++i) res[i] = (ll(a[i]) * b) % pr[i];
    return res;
}


const int N = 300'005;
const int X = 257;
Hash xpow[N], h[N];

Hash get_h(int pos, int len) {
    return h[pos + len] - h[pos] * xpow[len];
}


void solve()
{
    // DON'T FORGET
    gen_primes();
    int n;
    vector<int> a(n);
    
    fill(all(xpow[0]), 1);
    for (int i = 0; i < n; i++) {
        h[i + 1] = h[i] * X + a[i];
        xpow[i + 1] = xpow[i] * X;
    }
}



