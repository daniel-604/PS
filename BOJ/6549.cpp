#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n;

ll solution(vector<ll>& h, ll left, ll right) {
    if (left == right) return h[left];
    ll mid = (left + right) / 2;
    ll ret = max(solution(h, left, mid), solution(h, mid + 1, right));
    ll lo = mid, hi = mid + 1;
    ll height = min(h[lo], h[hi]);
    ret = max(ret, height * 2);
    while (left < lo || hi < right) {
        if (hi < right && (lo == left || h[lo - 1] < h[hi + 1])) {
            ++hi;
            height = min(height, h[hi]);
        } else {
            --lo;
            height = min(height, h[lo]);
        }
        ret = max(ret, height * (hi - lo + 1));
    }
    return ret;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    while (true) {
        cin >> n;
        if (n == 0) break;
        vector<ll> h(n);
        for (ll i = 0; i < n; ++i) cin >> h[i];
        cout << solution(h, 0, n - 1) << "\n";
    }
    return 0;
}