#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;


/* Classic */
int Phi(int n) {
	int result = n;
	for (int i=2; ull(i)*i<=n; ++i) {
		if (n % i == 0) {
			while (n % i == 0)
				n /= i;
			result -= result / i;
		}
    }
	if (n > 1)
		result -= result / n;
	return result;
}


/* Linear + factorization */
const int N = 1'000'000;
int phi[N + 1];
vector<int> min_d(N + 1, 0);
vector<int> pr; // replace with array for speed
void calc_phi() {
    phi[1] = 1;
    for (int i=2; i<=N; ++i) {
    	if (min_d[i] == 0) {
    		min_d[i] = i;
            phi[i] = i - 1;
    		pr.push_back(i);
    	} else {
            if (min_d[i] == min_d[i / min_d[i]])
                phi[i] = phi[i / min_d[i]] * min_d[i];
            else
                phi[i] = phi[i / min_d[i]] * (min_d[i] - 1);
        }
        for (int p : pr) {
            ull ip = ull(i) * p;
            if (ip > N || p > min_d[i])
                break;
            min_d[ip] = p;
        }
    }
}
