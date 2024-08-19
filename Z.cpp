#include <bits/stdc++.h>
using namespace std;

// S[i...], S의 lcp
vector<int> getZ(const string& s) {
	const int n = s.size();
	int l = 0, r = 0;
	vector<int> z(n, 0);
	z[0] = n;
	for (int i = 1; i < n; ++i) {
		if (i <= r) z[i] = min(r - i, z[i - l]);
		while (s[i + z[i]] == s[z[i]]) ++z[i];
		if (i > r) l = i;
		r = max(r, i + z[i] - 1);
	}
	return z;
}

void solve() {
	string S;
	vector<int> z = getZ(S);
}