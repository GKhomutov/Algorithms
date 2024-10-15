#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
using namespace std;
using ll = long long;
mt19937 rd(chrono::system_clock::now().time_since_epoch().count());

struct Node{
    int x, sz;
    uint_fast32_t cmp;
    Node *l, *r;

    Node(int _x) {
        x = _x;
        sz = 1;
        cmp = rd();
        l = r = nullptr;
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
    if (v->x <= x) {
        split(v->r, x, l, r);
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

void insert(Node **root, int x, int i, int ans) {
    Node *t = new Node(x);
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

int order_of_key(Node *v, int x) {
    push(v);
    if (v == nullptr) return 0;
    if (v->x == x) return size(v->l);
    if (v->x > x) {
        return order_of_key(v->l, x);
    } else {
        return size(v->l) + 1 + order_of_key(v->r, x);
    }
}

void dfs_delete(Node *v) {
    if (v == nullptr) return;
    dfs_delete(v->l);
    dfs_delete(v->r);
    delete v;
}

void erase(Node **root, int x) {
    Node *l, *m, *r;
    split(*root, x - 1, &l, &m);
    split(m, x, &m, &r);
    dfs_delete(m);
    *root = merge(l, r);
}
