#include <bits/stdc++.h>
using namespace std;

vector<int> aMatch, bMatch;

bool dfs(int a, vector<bool>& visited, vector<vector<int>>& adj) {
	if (visited[a]) return false;
	visited[a] = true;
	for (auto b: adj[a]) {
		if (bMatch[b] == -1 || dfs(bMatch[b], visited, adj)) {
			aMatch[a] = b;
			bMatch[b] = a;
			return true;
		}
	}
	return false;
}

int bipartiteMatch(int MAX_N, int MAX_M, vector<vector<int>>& adj) {
	aMatch = vector<int>(MAX_N, -1);
	bMatch = vector<int>(MAX_M, -1);
	int size = 0;
	vector<bool> visited(MAX_N, false);
	for (int start = 0; start < MAX_N; ++start) {
		if (dfs(start, visited, adj)) {
			++size;
			for (int i = 0; i < MAX_N; ++i) visited[i] = false;
		}
	}
	return size;
}

int grid[100][100];
int r[100][100], c[100][100];
int N, M;

// time complexity: V*E
void solve() {
	cin >> N >> M;
	for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) cin >> grid[i][j];
	memset(r, -1, sizeof(r));
    memset(c, -1, sizeof(c));
    int rcnt = 0, ccnt = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (grid[i][j] != 2) {
                if (j == 0 || c[i][j - 1] == -1) c[i][j] = ccnt++;
                else c[i][j] = c[i][j - 1]; 
            }
        }
    }
    for (int j = 0; j < M; ++j) {
        for (int i = 0; i < N; ++i) {
            if (grid[i][j] != 2) {
                if (i == 0 || r[i - 1][j] == -1) r[i][j] = rcnt++;
                else r[i][j] = r[i - 1][j]; 
            }
        }
    }
	int MAX_N = rcnt, MAX_M = ccnt;
	vector<vector<int>> adj(MAX_N);
	for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) if (grid[i][j] == 0) {
		adj[r[i][j]].push_back(c[i][j]);
	}
	int ans = bipartiteMatch(MAX_N, MAX_M, adj);
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}