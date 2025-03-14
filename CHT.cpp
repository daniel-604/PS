#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// y = kx + m
struct Line {
	mutable ll k, m;
    mutable double p;
	bool operator < (const Line& o) const { return k < o.k; }
	bool operator < (ll x) const { return p < x; }
};

// maximum
struct LineContainer : multiset<Line, less<>> {
	double div(ll a, ll b) {
		return (double) a / b;
    }
	bool bad(iterator x, iterator y) {
		if (y == end()) return x->p = LLONG_MAX, 0;
		if (x->k == y->k) x->p = x->m > y->m ? LLONG_MAX : LLONG_MIN;
		else x->p = div(y->m - x->m, x->k - y->k);
		return x->p >= y->p;
	}
	void add(ll k, ll m) {
		auto z = insert({k, m, 0}), y = z++, x = y;
		while (bad(y, z)) z = erase(z);
		if (x != begin() && bad(--x, y)) bad(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p) bad(x, erase(y));
	}
	ll query(ll x) {
		assert(!empty());
		auto l = *lower_bound(x);
		return l.k * x + l.m;
	}
} cht;