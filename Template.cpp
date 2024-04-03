#include <bits/stdc++.h>

#define sz(x) (int)(x).size()
#define pb push_back
#define pob pop_back
#define all(x) (x).begin(), (x).end()
#define ub upper_bound
#define lb lower_bound
#define fi first
#define se second
#define mineq(x, y) (x) = min((x), (y))
#define maxeq(x, y) (x) = max((x), (y))
#define yes cout << "YES\n"
#define no cout << "NO\n"

using namespace std;
using ull = unsigned long long;
using ll = long long;
using ld =long double;

mt19937 rd(chrono::system_clock::now().time_since_epoch().count());

/*--------------------------------------------------IO_FILES-----------------------------------------------*/
const char *infile = "";
const char *outfile = "";
/*---------------------------------------------------DEBUG-------------------------------------------------*/
#define deb(...) logger(#__VA_ARGS__, __VA_ARGS__)
template <typename... Args>
void logger(string vars, Args &&...values) {
	cout << vars << " = ";
	string delim = "";
	(..., (cout << delim << values, delim = ", "));
	cout << endl;
}
template <typename... T> void printer(T &&...args) { ((cout << args << " "), ...); }
template<typename F>
auto debfunc(const F& func) {
    return [func](auto &&...args) { // forward reference
        cout << "input = ";
        printer(args...);
        auto res = func(std::forward<decltype(args)>(args)...);
        cout << "res = " << res << endl;
        return res;
    };
}
/*--------------------------------------------------FAST_INP-----------------------------------------------*/
//#define FAST_INP
#ifdef FAST_INP
constexpr int _INPBUF = 16 * 1024;
char _inpbuf[_INPBUF];
int _inppos = 0, _inplen = 0;
inline char getChar(FILE *fin = stdin){if (_inppos==_inplen) {_inppos=0;_inplen = fread(_inpbuf, 1, _INPBUF, fin);}if (_inppos == _inplen) {return EOF;}return _inpbuf[_inppos++];}
inline int readChar(FILE *fin = stdin){char c;do {c = getChar(fin);} while (c < ' ');return c;}
template<typename T> inline T readNum(FILE *fin = stdin){bool s=false;char c = readChar(fin); if (c == '-') {s=true;c=getChar(fin);}T x = 0;while (isdigit(c)) {x = x * 10 + c - '0';c = getChar(fin);}return s ? -x : x;}
#endif // FAST_INP
/*--------------------------------------------------FAST_OUT-----------------------------------------------*/
//#define FAST_OUT
#ifdef FAST_OUT
static const int _OUTBUF = 16 * 1024;
static char _outbuf[_OUTBUF];
static int _outpos = 0;
inline void writeChar(int x) { if (_outpos == _OUTBUF) {fwrite(_outbuf, 1, _OUTBUF, stdout); _outpos = 0;}_outbuf[_outpos++] = x;}
static const int _NUMBUF = 16;
static char _numbuf[_NUMBUF];
template<typename T> inline void writeNum(T x, char end = 0) {if (x < 0) {writeChar('-'); x = -x;}int n = 0;do _numbuf[n++] = x % 10 + '0'; while(x /= 10);while (n--) writeChar(_numbuf[n]);if (end) writeChar(end);}
struct Flusher{~Flusher(){if(_outpos){fwrite(_outbuf, 1, _outpos, stdout);_outpos=0;}}}_flusher;
#endif // FAST_OUT
/*------------------------------------------------IO_OPERATORS---------------------------------------------*/
template<typename T, typename U> inline ostream &operator << (ostream &_out, const pair<T, U> &_p) { _out << _p.first << " " << _p.second; return _out; }
template<typename T, typename U> inline istream &operator >> (istream &_in, pair<T, U> &_p) { _in >> _p.first >> _p.second; return _in; }
template<typename T> inline ostream &operator << (ostream &_out, const vector<T> &_v) { if (_v.empty()) return _out; _out << _v.front(); for (auto _it = ++_v.begin(); _it != _v.end(); ++_it) _out << ' ' << *_it; return _out; }
template<typename T> inline istream &operator >> (istream &_in, vector<T> &_v) { for (auto &_i : _v) _in >> _i; return _in; }
template<typename T> inline ostream &operator << (ostream &_out, const set<T> &_s) { if (_s.empty()) return _out; _out << *_s.begin(); for (auto _it = ++_s.begin(); _it != _s.end(); ++_it) _out << ' ' << *_it; return _out; }
template<typename T> inline ostream &operator << (ostream &_out, const multiset<T> &_s) { if (_s.empty()) return _out; _out << *_s.begin(); for (auto _it = ++_s.begin(); _it != _s.end(); ++_it) _out << ' ' << *_it; return _out; }
template<typename T> inline ostream &operator << (ostream &_out, const unordered_set<T> &_s) { if (_s.empty()) return _out; _out << *_s.begin(); for (auto _it = ++_s.begin(); _it != _s.end(); ++_it) _out << ' ' << *_it; return _out; }
template<typename T> inline ostream &operator << (ostream &_out, const unordered_multiset<T> &_s) { if (_s.empty()) return _out; _out << *_s.begin(); for (auto _it = ++_s.begin(); _it != _s.end(); ++_it) _out << ' ' << *_it; return _out; }
template<typename T, typename U> inline ostream &operator << (ostream &_out, const map<T, U> &_m) { if (_m.empty()) return _out; _out << '(' << _m.begin()->first << ": " << _m.begin()->second << ')'; for (auto _it = ++_m.begin(); _it != _m.end(); ++_it) _out << ", (" << _it->first << ": " << _it->second << ')'; return _out; }
template<typename T, typename U> inline ostream &operator << (ostream &_out, const unordered_map<T, U> &_m) { if (_m.empty()) return _out; _out << '(' << _m.begin()->first << ": " << _m.begin()->second << ')'; for (auto _it = ++_m.begin(); _it != _m.end(); ++_it) _out << ", (" << _it->first << ": " << _it->second << ')'; return _out; }
/*-------------------------------------------------ALLOCATOR----------------------------------------------*/
//#define ALLOCATOR
#ifdef ALLOCATOR
const int _ML = 250 * 1024 * 1024;
char _mem[_ML];
size_t _ptr = 0;
void * operator new(size_t cnt) { _ptr += cnt; assert(_ptr <= _ML); return  _mem + _ptr - cnt; }
void operator delete(void *) noexcept {}
#endif // ALLOCATOR
/*-----------------------------------------------------HASH------------------------------------------------*/
struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {x += 0x9e3779b97f4a7c15;x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;x = (x ^ (x >> 27)) * 0x94d049bb133111eb;return x ^ (x >> 31);}
    size_t operator()(uint64_t x) const {static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();return splitmix64(x + FIXED_RANDOM);}
};
/*-----------------------------------------------------CODE------------------------------------------------*/


void solve()
{
	
}


signed main()
{
	if (*infile != '\0') (void)freopen(infile, "r", stdin);
	if (*outfile != '\0') (void)freopen(outfile, "w", stdout);
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios_base::sync_with_stdio(false);
	cout << setprecision(20);
	cout << fixed;

	int t = 1;
	//cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
