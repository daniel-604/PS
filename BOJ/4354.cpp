#include <bits/stdc++.h>
using namespace std;

// N[...i] 접두사와 접미사가 같은 최대 길이(본인 제외)
vector<int> getPartialMatch(const string& N) {
	int m = N.size(); 
	vector<int> pi(m, 0);
	int begin = 1, matched = 0;
	while (begin + matched < m) {
		if (N[begin + matched] == N[matched]) {
			++matched;
			pi[begin + matched - 1] = matched;
		} else {
			if (matched == 0) ++begin;
			else {
				begin += matched - pi[matched - 1];
				matched = pi[matched - 1];
			}
		}
	}
	return pi;
}

// 짚더미 H의 부분 문자열이 바늘 N인 index
vector<int> kmpSearch(const string& H, const string& N) {
	int n = H.size(), m = N.size();
	vector<int> ret;
	vector<int> pi = getPartialMatch(N);
	int begin = 0, matched = 0;
	while (begin <= n - m) {
		if (matched < m && H[begin + matched] == N[matched]) {
			++matched;
			if (matched == m) ret.push_back(begin);
		} else {
			if (matched == 0) ++begin;
			else {
				begin += matched - pi[matched - 1];
				matched = pi[matched - 1];
			}
		}
	}
	return ret;
}
string s;

void solve() {
	vector<int> tmp = kmpSearch(s + s, s);
	if (tmp.size() <= 1) {
		cout << 1 << '\n';
	} else {
		cout << s.size() / tmp[1] << '\n';
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	while (true) {
		cin >> s;
		if (s == ".") break;
		solve();
	}
}