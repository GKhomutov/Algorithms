#include <bits/stdc++.h>

using namespace std;


template <class Info>
struct SegTree {
    int n;
    vector<Info> info;

    SegTree() : n(0) {}
    SegTree(const vector<Info> &a) {
        n = 1;
        while (n < a.size()) n <<= 1;
        info.assign(2 * n, Info());
        copy(all(a), info.begin() + n);
        for (int v = n - 1; v != 0; --v) {
            pull(v);
        }
    }
    SegTree(int sz, Info value = Info()) : SegTree(vector<Info>(sz, value)) {}

    void pull(int v) {
        info[v] = info[2 * v] + info[2 * v + 1];
    }

    void upd(int i, const Info &x) {
        i += n;
        info[i] = x;
        for (i >>= 1; i != 0; i >>= 1) {
            info[i] = info[i << 1] + info[i << 1 | 1];
        }
    }
    
    Info get(int l, int r) const {
        Info resL = Info(), resR = Info();
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) {
                resL = resL + info[l++];
            }
            if (r & 1) {
                resR = info[--r] + resR;
            }
        }
        return resL + resR;
    }
};

struct Info {
    int max = 0;
};

Info operator+(const Info &a, const Info &b) {
    return {max(a.max, b.max)};
}
