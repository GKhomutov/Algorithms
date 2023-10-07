/* Bipartite graph */
// size of MVC = size of maximal matching
// size of MVC + size of MIS = N
#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
using namespace std;

/* O(N_1 * (N + M)), but in fact it's much faster */
const int N_1 = 5'005;
const int N_2 = 10'005;
vector<int> g[N_1];
int lr[N_1];
int rl[N_2];
vector<bool> used(N_1);
bool try_kuhn(int v)
{
    if (used[v]) return false;
    used[v] = true;
    for (int to : g[v]) {
        if (rl[to] == -1 || try_kuhn(rl[to])) {
            lr[v] = to;
            rl[to] = v;
            return true;
        }
    }
    return false;
}
int build_matching()
{
    fill(lr, lr + N_1, -1);
    fill(rl, rl + N_2, -1);
    int ans = 0;
    bool ok = true;
    while (ok) {
        ok = false;
        fill(all(used), false);
        for (int v = 1; v < N_1; ++v) {
            if (lr[v] == -1 && try_kuhn(v)) {
                ok = true;
                ++ans;
            }
        }
    }
    return ans;
}
vector<bool> used_1(N_1, false);
vector<bool> used_2(N_2, false);
void dfs_mvc(int v)
{
    used_1[v] = true;
    for (int to : g[v]) {
        if (to == lr[v]) continue;
        if (used_2[to]) continue;
        used_2[to] = true;
        if (rl[to] != -1 && !used_1[rl[to]])
            dfs_mvc(rl[to]);
    }
}
/* !used_1 + used_2 will be MVC
   used_1 + !used_2 will be MIS */
int build_mvc()
{
    int ans = build_matching();
    for (int v = 1; v < N_1; ++v) {
        if (lr[v] == -1 && !used_1[v])
            dfs_mvc(v);
    }
    return ans;
}





/* O(N * (N + M)), but in fact it's much faster */
const int N = 10'005;
vector<int> g[N];
int mt[N];
vector<bool> used(N);
bool try_kuhn(int v)
{
    if (used[v]) return false;
    used[v] = true;
    for (int to : g[v]) {
        if (mt[to] == -1 || try_kuhn(mt[to])) {
            mt[v] = to;
            mt[to] = v;
            return true;
        }
    }
    return false;
}
int build_matching()
{
    fill(mt, mt + N, -1);
    int ans = 0;
    bool ok = true;
    while (ok) {
        ok = false;
        fill(all(used), false);
        for (int v = 1; v < N; ++v) {
            if (mt[v] == -1 && try_kuhn(v)) {
                ok = true;
                ++ans;
            }
        }
    }
    return ans;
}
void dfs_mvc(int v)
{
    used[v] = true;
    for (int to : g[v]) {
        if (to == mt[v]) continue;
        if (used[to]) continue;
        used[to] = true;
        if (mt[to] != -1 && !used[mt[to]])
            dfs_mvc(mt[to]);
    }
}
bool is_left(int v) {
    //!
}
/* !used left + used right will be MVC
   used left + !used right will be MIS */
int build_mvc()
{
    int ans = build_matching();
    fill(all(used), false);
    for (int v = 1; v < N; ++v) {
        if (is_left(v) && mt[v] == -1 && !used[v])
            dfs_mvc(v);
    }
    return ans;
}






