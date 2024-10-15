#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
using namespace std;
using ll = long long;
mt19937 rd(chrono::system_clock::now().time_since_epoch().count());

struct Info{
    
};

struct Node{
    int sz;
    uint_fast32_t cmp;
    Node *l, *r;
    Info item;

    Node(const Info &_item) {
        sz = 1;
        l = r = nullptr;
        cmp = rd();
        item = _item;
    }
};

int size(Node *v) {
    return (v == nullptr) ? 0 : v->sz;
}

void push(Node *v) {
    if (v == nullptr) return;
}

void upd(Node *v) {
    v->sz = 1 + size(v->l) + size(v->r);
}

void split(Node *v, int x, Node **l, Node **r) {
    push(v);
    if (v == nullptr) {
        *l = *r = nullptr;
        return;
    }
    if (size(v->l) + 1 <= x) {
        split(v->r, x - size(v->l) - 1, l, r);
        v->r = *l;
        *l = v;
        upd(v);
    } else {
        split(v->l, x, l, r);
        v->l = *r;
        *r = v;
        upd(v);
    }
}

Node* merge(Node *l, Node *r) {
    push(l), push(r);
    if (l == nullptr) return r;
    if (r == nullptr) return l;
    if (l->cmp <= r->cmp) {
        r->l = merge(l, r->l);
        upd(r);
        return r;
    } else {
        l->r = merge(l->r, r);
        upd(l);
        return l;
    }
}

void insert(Node **root, int x, const Info &item) {
    Node *t = new Node(item);
    Node *l, *r; split(*root, x, &l, &r);
    *root = merge(l, merge(t, r));
}

Node* find_by_order(Node *v, int x) {
    push(v);
    if (v == nullptr) return nullptr;
    if (size(v->l) == x) return v;
    if (size(v->l) > x) {
        return find_by_order(v->l, x);
    } else {
        return find_by_order(v->r, x - size(v->l) - 1);
    }
}


