#include "Vec.cpp"

vector<Vec> convex_hull(vector<Vec> a)
{
    sort(all(a), LeftDownCmp);
    a.erase(unique(all(a)), a.end());
    int n = a.size();
    if (n < 2) return a;
    Vec p1 = a[0], p2 = a.back();
    vector<Vec> up, down;
    up = down = {p1};
    for (int i = 1; i < n; ++i)
    {
        if (i == n-1 || p1.square(p2, a[i]) > 0) {
            while (up.size() >= 2 && up[up.size()-2].square(up.back(), a[i]) >= 0)
                up.pop_back();
            up.push_back(a[i]);
        }
        if (i == n-1 || p1.square(p2, a[i]) < 0) {
            while (down.size() >= 2 && down[down.size()-2].square(down.back(), a[i]) <= 0)
                down.pop_back();
            down.push_back(a[i]);
        }
    }
    a.resize(up.size() + down.size() - 2);
    auto it = copy(all(up), a.begin());
    copy(down.rbegin() + 1, down.rend() - 1, it);
    return a;
}

