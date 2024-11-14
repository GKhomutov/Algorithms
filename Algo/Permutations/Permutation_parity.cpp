#include <bits/stdc++.h>

using namespace std;

// checks if permutation is odd
bool parity(vector<int> p) {
    int n = p.size();
    if (n == 1) return false;
    vector<int> pos(n);
    for (int i = 0; i < n; ++i)
        pos[p[i]] = i;
    int swaps = 0;
    for (int i = 0; i < n; ++i) {
        if (p[i] != i) {
            ++swaps;
            int loc = pos[i];
            swap(p[i], p[loc]);
            swap(pos[p[i]], pos[p[loc]]);
        }
    }
    return swaps % 2;
}


