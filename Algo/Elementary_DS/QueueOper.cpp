#include <vector>
#include <utility>
#include <cassert>

#define pb push_back
#define pob pop_back
#define fi first
#define se second

using namespace std;

template<typename T, class V>
struct Operation
{
    V operator()(const T &x) const {

    }

    V operator()(const T& x, const V& v) const {

    }

    V operator()(const V &x, const V &y) const {

    }
};


template <typename T, class V, class Oper>
struct StackOper
{
    vector<pair<T, V>> _st;

    void push(const T& x) {
        if (_st.empty()) {
            _st.pb({x, Oper{}(x)});
        } else {
            _st.pb({x, Oper{}(x, _st.back().se)});
        }
    }

    pair<T, V> pop() {
        pair<T, V> to_ret = _st.back();
        assert(!empty());
        _st.pob();
        return to_ret;
    }

    const pair<T, V>& back() const {
        assert(!empty());
        return _st.back();
    }

    pair<T, V>& back() {
        assert(!empty());
        return _st.back();
    }

    size_t size() const {
        return _st.size();
    }

    bool empty() const {
        return _st.empty();
    }
};


template <class T, class V, class Oper>
struct QueueOper
{
    StackOper<T, V, Oper> _in;
    StackOper<T, V, Oper> _out;

    void rebalance() {
        if (_out.empty()) {
            while (!_in.empty()) {
                _out.push(_in.back().fi);
               _in.pop();
             }
        }
    }

    void push(const T& x) {
        _in.push(x);
    }

    pair<T, V> pop() {
        assert(!empty());
        rebalance();
        return _out.pop();
    }

    const pair<T, V> &front() const {
        assert(!empty());
        rebalance();
        return _out.back();
    }

    pair<T, V> &front() {
        assert(!empty());
        rebalance();
        return _out.back();
    }

    V get_state() const {
        assert(!empty());
        if (!_in.empty() && !_out.empty())
            return Oper(_in.back().se, _out.back().se);
        return _out.empty() ? _in.back().se : _out.back().se; 
    }

    size_t size() const {
        return _in.size() + _out.size();
    }

    bool empty() const {
        return _in.empty() && _out.empty();
    }
};
