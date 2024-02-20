#include <bits/stdc++.h>
using namespace std;

void solve() {
	int n; cin >> n;
	vector<int> a(2 * n); for (int i = 0; i < 2 * n; ++i) cin >> a[i];
	int ans = 0;
	sort(a.begin(), a.end());
	for (int i = 0; i < 2 * n; i += 2) {
		ans += a[i];
	}
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int t; cin >> t;
	while (t--) solve();
}