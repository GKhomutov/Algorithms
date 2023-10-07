#include <bits/stdc++.h>

#define all(x) (x).begin(), (x).end()

using namespace std;


const int N = 100'005;
const int INF = INT_MAX;
int dp[N];      // the smallest number that ends the LIS of length i
int ending[N];  // index of last element in LIS of length i
int re[N];      // index of element before a[i]
/* Returns array of indices */
vector<int> lis(const vector<int> &a)
{
    int n = a.size();
    fill(dp, dp + N, INF);
    dp[0] = -INF;
    ending[0] = -1;
    int length = 0;
    for (int i = 0; i < n; ++i) {
        auto it = lower_bound(dp, dp + N, a[i]);
        *it = a[i];
        int k = it - dp;
        length = max(length, k);
        ending[k] = i;
        re[i] = ending[k - 1];
    }

    vector<int> ans;
    for(int p = ending[length]; p != -1; p = re[p])
        ans.push_back(p);
    reverse(all(ans));
    return ans;
}

