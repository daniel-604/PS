#include <bits/stdc++.h>
using namespace std;

void solve() {
	int n; cin >> n;
	int a[n]; for (int i = 0; i < n; ++i) cin >> a[i];
	int x = 0;
	for (int i = 0; i < n; ++i) {
		++x;
		if (x == a[i]) ++x;
	}
	cout << x << '\n';
	return;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}