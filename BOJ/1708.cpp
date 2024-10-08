#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n;

ll cross(const pair<ll, ll>& a, const pair<ll, ll>& b) { return a.first * b.second - a.second * b.first; }
ll ccw(const pair<ll, ll>& a, const pair<ll, ll>& b, const pair<ll, ll>& c) {
	pair<ll, ll> a_b = {b.first - a.first, b.second - a.second};
	pair<ll, ll> b_c = {c.first - b.first, c.second - b.second};
	return cross(a_b, b_c);
}

void solve() {
	cin >> n;
	vector<pair<ll, ll>> cities;
	for (int i = 0; i < n; ++i) {
		ll x, y; cin >> x >> y;
		cities.push_back({x, y});
	}
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
	convex.push_back(cities[0]); convex.push_back(cities[1]);
	for (int i = 2; i < cities.size(); ++i) {
		while (convex.size() >= 2) {
			pair<ll, ll> b = convex.back(); convex.pop_back();
			pair<ll, ll> a = convex.back();
			if (ccw(a, b, cities[i]) > 0) {
				convex.push_back(b);
				break;
			}
		}
		convex.push_back(cities[i]);
	}
	// for (auto i: convex) cout << i.first + unit.first << ' ' << i.second + unit.second << '\n';
	cout << convex.size();
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}