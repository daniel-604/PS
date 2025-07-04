#include <bits/stdc++.h>
using namespace std;

const int MAX_V = 100001;
vector<int> adj[MAX_V];

int ord[MAX_V], low[MAX_V];
int cnt = 0;

void dfs(vector<pair<int, int>>& ret, int v, int p) {
    ord[v] = ++cnt;
    low[v] = ord[v];
	bool flag = false;
    for (auto u: adj[v]) if (u != p) {
        if (ord[u]) low[v] = min(low[v], ord[u]);
        else {
            dfs(ret, u, v);
            if (low[u] > ord[v]) ret.push_back(make_pair(min(v, u), max(v, u)));
			low[v] = min(low[u], low[v]);
        }
    }
}

// V: maximum vertex + 1
// TODO: 1-index
vector<pair<int, int>> getEdge(int V) {
	vector<pair<int, int>> ret;
	for (int i = 1; i < V; ++i) if (!ord[i]) dfs(ret, i, 0);
	return ret;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int V, E; cin >> V >> E;
	while (E--) {
		int a, b; cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	auto ans = getEdge(V + 1);
	cout << ans.size() << '\n';
	sort(ans.begin(), ans.end());
	for (auto i: ans) cout << i.first << ' ' << i.second << '\n';
}