#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;

const int N = 10'000'000;

/* Classic */
vector<bool> isprime(N + 1, true);
void sieve()
{
    isprime[0] = isprime[1] = false;
    for (int j = 4; j <= N; j += 2) {
        isprime[j] = false;
    }
    for (int i = 3; i*i <= N; i += 2) {
        if (isprime[i]) {
            for (int j = i*i; j <= N; j += i) {
                isprime[j] = false;
            }
        }
    }
}


/* Linear + factorization */
int min_d[N + 1];
vector<int> pr; // replace with array for speed
void seive() {
    for (int i=2; i<=N; ++i) {
        if (min_d[i] == 0) {
            min_d[i] = i;
            pr.push_back(i);
        }
        for (int p : pr) {
            ull ip = ull(i) * p;
            if (ip > N || p > min_d[i])
                break;
            min_d[ip] = p;
        }
    }
}


