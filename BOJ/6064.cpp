#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// returns {gcd, x, y}
tuple<ll, ll, ll> extended_euclidean(ll a, ll b) {
    if (b == 0)
        return {a, 1, 0};
    auto [g, x, y] = extended_euclidean(b, a%b);
    return {g, y, x-(a/b)*y};
}

void solve() {
	ll M, N, X, Y; cin >> M >> N >> X >> Y;
	auto [g, x, y] = extended_euclidean(M, N);
	if ((Y - X) % g != 0) {
		cout << -1 << '\n';
		return;
	}
	x *= (Y - X) / g;
	ll l = M * N / g;
	ll ret = M * x + X; ret %= l;
	while (ret <= 0) ret += l;
	cout << ret << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int T; cin >> T;
	while (T--) solve();
}