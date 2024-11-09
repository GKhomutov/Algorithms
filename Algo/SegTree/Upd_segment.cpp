#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
using namespace std;

template <class Info, class Tag>
struct SegTree
{
    int n;
    vector<Info> info;
    vector<Tag> tag;    // promise for children
    
    SegTree() : n(0) {}
    SegTree(int sz, Info value = Info()) {
        init(vector<Info>(sz, value));
    }

    void pull(int v) {
        info[v] = info[2 * v] + info[2 * v + 1];
    }
    void apply(int v, const Tag &t) {
        info[v].apply(t);
        tag[v].apply(t);
    }
    void push(int v) {
        apply(2 * v, tag[v]);
        apply(2 * v + 1, tag[v]);
        tag[v] = Tag();
    }

    void init(const vector<Info> &a) {
        n = 1;
        while (n < a.size()) n <<= 1;
        info.assign(2 * n, Info());
        tag.assign(2 * n, Tag());
        copy(all(a), info.begin() + n);
        for (int v = n - 1; v != 0; --v) {
            pull(v);
        }
    }

    void upd(int v, int l, int r, int i, const Info &x) {
        if (r - l == 1) {
            info[v] = x;
            return;
        }
        int m = (l + r) / 2;
        push(v);
        if (i < m) {
            upd(2 * v, l, m, i, x);
        } else {
            upd(2 * v + 1, m, r, i, x);
        }
        pull(v);
    }
    void upd(int i, const Info &x) {
        upd(1, 0, n, i, x);
    }

    Info rangeQuery(int v, int l, int r, int L, int R) {
        if (R <= l || L >= r) {
            return Info();
        }
        if (L <= l && r <= R) {
            return info[v];
        }
        push(v);
        int m = (l + r) / 2;
        return rangeQuery(2 * v, l, m, L, R) +
               rangeQuery(2 * v + 1, m, r, L, R);
    }
    Info rangeQuery(int L, int R) {
        return rangeQuery(1, 0, n, L, R);
    }

    void rangeApply(int v, int l, int r, int L, int R, const Tag &t) {
        if (R <= l || r <= L) {
            return;
        }
        if (L <= l && r <= R) {
            apply(v, t);
            return;
        }
        push(v);
        int m = (l + r) / 2;
        rangeApply(2 * v, l, m, L, R, t);
        rangeApply(2 * v + 1, m, r, L, R, t);
        pull(v);
    }
    void rangeApply(int L, int R, const Tag &t) {
        return rangeApply(1, 0, n, L, R, t);
    }
};

struct Tag {
    int add = 0;
    void apply(const Tag &t) {
        add += t.add;
    }
};

struct Info {
    int max = 0;
    void apply(const Tag &t) {
        max += t.add;
    }
};

Info operator+(const Info &a, const Info &b) {
    return {max(a.max, b.max)};
}
