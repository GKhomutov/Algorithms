/* PROBLEM STATEMENT */

// Given n <= 20. For every pair 0 <= i, j < n we know the penalty for placing these numbers
// side by side in a permutation. Find the permutation with minimum penalty.

#include <bits/stdc++.h>

using namespace std;

const int INF = INT_MAX;
const int N = 20;
const int S = 1 << N;
int pen[N][N];
int dp[S][N];   // dp[subset, last] - minimum penalty when subset and last number are fixed
int solve(const int n)
{
    fill(dp, dp + S * N, INF);
    for (int i = 0; i < n; ++i)
        dp[1 << i][i] = 0;
    for (int mask = 0; mask < (1 << n); ++mask) {
        for (int i = 0; i < n; ++i) {
            if ((mask >> i) & 1) {
                int mask_no_i = mask ^ (1 << i);
                for (int j = 0; j < n; ++j) {
                    if ((mask_no_i >> j) & 1) {
                        dp[mask][i] = min(dp[mask][i], dp[mask_no_i][j] + pen[j][i]);
                    }
                }
            }
        }
    }
    int ans = INF;
    int mask_all = (1 << n) - 1;
    for (int i = 0; i < n; ++i) {
        ans = min(ans, dp[mask_all][i]);
    }
    return ans;
}
