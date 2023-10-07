#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;


/* Excluded Euclidean algorithm */
template<typename T>
T gcdex(T a, T b, T &x, T &y)
{
	if (a == 0) {
		x = 0, y = 1;
		return b;
	}
	T x1, y1;
	T d = gcdex(b % a, a, x1, y1);
	x = y1 - (b / a) * x1; // potential overflow!!!
	y = x1;
	return d;
}

/* Inversed in ring */
template <typename T>
T Inv(T a, T m)
{
    T x, y;
    assert(gcdex(a, m, x, y) == 1);
    return (x % m + m) % m;
}


/* All inversed elements for prime module */
const int P = 998'244'353;
int inv[P];
void calc_inv()
{
    inv[1] = 1;
    for (int i = 2; i < P; ++i)
        inv[i] = P - int(ull(P / i) * inv[P % i] % P);
}


/* Diophantine equation ax + by = c */
// Common solution is { x0 + k * b/g , y0 - k * a/g } for each k in Z
template<typename T>
bool find_any_solution(T a, T b, T c, T &x0, T &y0, T &g)
{
	assert(a || b);
	g = gcdex(abs(a), abs(b), x0, y0);
	if (c % g)
		return false;
	x0 *= c / g; // potential overflow!!!
	y0 *= c / g;
	if (a < 0) x0 = -x0;
	if (b < 0) y0 = -y0;
	return true;
}
