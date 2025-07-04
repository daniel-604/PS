#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct SegmentTree {
	vector<ll> arr;
	vector<ll> tree;
	static constexpr ll dValue = 0; // TODO
	int sz;

	ll merge(ll a, ll b) { return a + b; }
	SegmentTree(int sz) : SegmentTree(vector<ll>(sz, dValue)) {}
	SegmentTree(const vector<ll>& a) {
		sz = a.size();
		arr = a;
		int h = (int)ceil(log2(sz));
		int tree_size = (1 << (h + 1));
		tree = vector<ll>(tree_size);
		init(1, 0, sz - 1);
	}
	void init(int node, int start, int end) {
		if (start == end) tree[node] = arr[start];
		else {
			int mid = (start + end) / 2;
			init(node * 2, start, mid);
			init(node * 2 + 1, mid + 1, end);
			tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
		}
	}
	void update(int node, int start, int end, int index, ll val) {
		if (index < start || index > end) return;
		if (start == end) {
			arr[index] = val;
			tree[node] = val;
			return;
		}
		int mid = (start + end) / 2;
		update(node * 2, start, mid, index, val);
		update(node * 2 + 1, mid + 1, end, index, val);
		tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
	}
	ll query(int node, int start, int end, int left, int right) {
		if (left > end || right < start) return dValue;
		if (left <= start && end <= right) return tree[node];
		int mid = (start + end) / 2;
		ll lsum = query(node * 2, start, mid, left, right);
		ll rsum = query(node * 2 + 1, mid + 1, end, left, right);
		return merge(lsum, rsum);
	}
	void update(int index, ll val) { update(1, 0, sz - 1, index, val); }
	ll query(int left, int right) { return query(1, 0, sz - 1, left, right); }
};

void solve() {
	int N, M, K; cin >> N >> M >> K;
	vector<ll> a(N); for (int i = 0; i < N; ++i) cin >> a[i];
	SegmentTree seg {a};
	M += K;
	while (M--) {
		ll a, b, c; cin >> a >> b >> c;
		if (a == 1) {
			--b;
			seg.update(b, c);
		} else {
			--b; --c;
			cout << seg.query(b, c) << '\n';
		}
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}