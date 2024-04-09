#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int MAX_M, MAX_N;
vector<ll> dp_before, dp_cur;

ll C(int i, int j);

// min version
// compute dp_cur[l], ... dp_cur[r] (inclusive)
void compute(int l, int r, int optl, int optr) {
    if (l > r)
        return;

    int mid = (l + r) >> 1;
    pair<ll, int> best = {LLONG_MAX, -1};

    for (int k = optl; k <= min(mid, optr); k++) {
        best = min(best, {(k ? dp_before[k - 1] : 0) + C(k, mid), k});
    }

    dp_cur[mid] = best.first;
    int opt = best.second;

    compute(l, mid - 1, optl, opt);
    compute(mid + 1, r, opt, optr);
}

void solve() {
    dp_before.assign(MAX_N,0);
    dp_cur.assign(MAX_N,0);

    for (int i = 0; i < MAX_N; i++)
        dp_before[i] = C(0, i);

    for (int i = 1; i < MAX_M; i++) {
        compute(0, MAX_N - 1, 0, MAX_N - 1);
        dp_before = dp_cur;
    }

    cout << dp_before[MAX_N - 1];
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}