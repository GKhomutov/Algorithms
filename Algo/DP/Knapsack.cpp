#include <bits/stdc++.h>

using namespace std;


const int W = 1'000'000;
const int INF = INT_MAX;
int dp[W + 1];
int knapsack(const vector<pair<int,int>> &a, int task_weight) {
    fill(dp, dp + W + 1, -INF);
    dp[0] = 0;
    for (auto [w, c] : a) {
        for (int i = W; i >= w; --i) {
            dp[i] = max(dp[i], dp[i - w] + c);
        }
    }
    return *max_element(dp, dp + task_weight + 1);
}
