#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll cross(const pair<ll, ll>& a, const pair<ll, ll>& b) { return a.first * b.second - a.second * b.first; }
ll ccw(const pair<ll, ll>& a, const pair<ll, ll>& b, const pair<ll, ll>& c) {
	pair<ll, ll> a_b = {b.first - a.first, b.second - a.second};
	pair<ll, ll> b_c = {c.first - b.first, c.second - b.second};
	return cross(a_b, b_c);
}

vector<pair<ll, ll>> getConvexHull(vector<pair<ll, ll>>& cities) {
	sort(cities.begin(), cities.end());
	pair<ll, ll> unit = cities.front();
	for (auto& i: cities) {
		i.first -= unit.first;
		i.second -= unit.second;
	}
	sort(next(cities.begin()), cities.end(), [](const pair<ll, ll>& a, const pair<ll, ll>& b) {
		if (cross(a, b) == 0) {
			if (a.first == b.first) return a.second < b.second;
			return a.first < b.first;
		}
		return cross(a, b) > 0;
	});
	vector<pair<ll, ll>> convex;
	for (auto i = cities.rbegin(); i != cities.rend(); ++i) {
		if (cross(*cities.rbegin(), *i) == 0) {
			convex.push_back(*i);
		} else break;
	}
	convex.push_back(cities[0]);
	for (int i = 1; i < cities.size(); ++i) {
		if (cross(*cities.rbegin(), cities[i]) == 0) break;
		convex.push_back(cities[i]);
	}
	for (auto& i: convex) {
		i.first += unit.first;
		i.second += unit.second;
	}
	return convex;
}

void solve() {
	int n; cin >> n;
	vector<pair<ll, ll>> cities;
	map<pair<ll, ll>, int> M;
	for (int i = 0; i < n; ++i) {
		ll x, y; cin >> x >> y;
		cities.push_back({x, y});
		M[{x, y}] = i;
	}
	vector<pair<ll, ll>> ans = getConvexHull(cities);
	for (auto i: ans) {
		cout << M[i] << ' ';
	}
	cout << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}