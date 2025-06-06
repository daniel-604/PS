#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// https://tistory.joonhyung.xyz
template<class T>
class Matrix {
public:
    int m, n;
	vector<int> cidx;
    vector<vector<T>> entry;
    Matrix(int m_, int n_) : m(m_), n(n_), cidx(n_), entry(m_, vector<T>(n_)) { iota(cidx.begin(), cidx.end(), 0); }
    Matrix(int m_) : Matrix(m_, m_) {}
    T& operator[](const pair<int, int>& p) { return entry[p.first][cidx[p.second]]; }
    const T& operator[](const pair<int, int>& p) const { return entry[p.first][cidx[p.second]]; }

    void rswap(int i, int j) { swap(entry[i], entry[j]); }
    void rmul(int i, T x) {
        for (int j = 0; j < n; ++j) {
            entry[i][j] *= x;
        }
    }
    void radd(int i1, int i2, T x) {
        for (int j = 0; j < n; ++j) {
            entry[i1][j] += entry[i2][j] * x;
        }
    }
	void cswap(int i, int j) { swap(cidx[i], cidx[j]); };
	void cmul(int j, T x) {
		for (int i = 0; i < n; ++i) {
			entry[i][cidx[j]] *= x;
		}
	}
	void cadd(int j1, int j2, T x) {
		for (int i = 0; i < n; ++i) {
			entry[i][cidx[j1]] += entry[i][cidx[j2]] * x;
		}
	}
};

template<class T>
vector<T> char_poly(Matrix<T>& A) {
	int n = A.n;
	assert(n == A.n);
	for (int j = 0; j < n - 2; ++j) {
		for (int i = j + 1; i < n; ++i) {
			if (A[{i, j}] != 0) {
				A.rswap(i, j + 1);
				A.cswap(i, j + 1);
				break;
			}
		}
		if (A[{j + 1, j}] != 0) {
			for (int i = j + 2; i < n; ++i) {
				T x = -A[{i, j}] / A[{j + 1, j}];
				A.radd(i, j + 1, x);
				A.cadd(j + 1, i, -x);
			}
		}
	}
	vector<vector<T>> cache(n + 1);
	cache[0] = {1};
	for (int k = 1; k <= n; ++k) {
		cache[k].resize(k + 1);
		for (int i = 1; i <= k; ++i) {
			cache[k][i] = cache[k - 1][i - 1];
		}
		for (int i = 0; i < k; ++i) {
			cache[k][i] -= A[{k - 1, k - 1}] * cache[k - 1][i];
		}
		T prod = 1;
		for (int i = k - 2; i >= 0; --i) {
			prod *= A[{i + 1, i}];
			for (int j = 0; j <= i; ++j) {
				cache[k][j] -= A[{i, k - 1}] * prod * cache[i][j];
			}
		}
	}
	return cache[n];
}

template<class T>
void gauss_elim(Matrix<T>& A) {
    for (int j = 0, r = 0; j < A.n && r < A.m; ++j) {
        for (int i = r; i < A.m; ++i) {
            if (A[{i, j}] != 0) {
                A.rswap(r, i);
                break;
            }
        }
        if (A[{r, j}] != 0) {
            A.rmul(r, 1 / A[{r, j}]);
            for (int i = r + 1; i < A.m; ++i) {
                A.radd(i, r, -A[{i, j}]);
            }
            ++r;
        }
    }
}

template<class T>
int matRank(Matrix<T>& A) {
    int r = 0;
    for (int j = 0; j < A.m && r < A.n; j++) {
        for (int i = r; i < A.n; i++) {
            if (A[{i, j}] != 0) {
                A.rswap(r, i);
                break;
            }
        }
        if (A[{r, j}] != 0) {
            A.rmul(r, 1 / A[{r, j}]);
            for (int i = r + 1; i < A.n; i++) {
                A.radd(i, r, -A[{i, j}]);
            }
            r++;
        }
    }
    return r;
};

template<class T>
void rref(Matrix<T>& A) {
    for (int j = 0, r = 0; j < A.n && r < A.m; ++j) {
        for (int i = r; i < A.m; i++) {
            if (A[{i, j}] != 0) {
                A.rswap(r, i);
                break;
            }
        }
        if (A[{r, j}] != 0) {
            A.rmul(r, 1 / A[{r, j}]);
            for (int i = 0; i < A.m; ++i) {
                if (i != r) {
                    A.radd(i, r, -A[{i, j}]);
                }
            }
            ++r;
        }
    }
}

template<class T>
T det(Matrix<T>& A) {
	int n = A.n;
    assert(A.n == A.m);
    T ret = 1;
    for (int j = 0; j < n; ++j) {
        for (int i = j; i < n; ++i) {
            if (A[{i, j}] != 0) {
                if (i > j) {
                    A.rswap(j, i);
                    ret = -ret;
                }
                break;
            }
        }
        if (A[{j, j}] == 0) {
            return 0;
        }
        ret *= A[{j, j}];
        A.rmul(j, 1 / A[{j, j}]);
        for (int i = j + 1; i < n; ++i) {
            A.radd(i, j, -A[{i, j}]);
        }
    }
    return ret;
}


template<class T>
Matrix<T> operator * (const Matrix<T>& A, const Matrix<T>& B) {
    assert(A.n == B.m);
    Matrix<T> C(A.m, B.n);
    for (int i = 0; i < C.m; ++i) {
        for (int k = 0; k < A.n; ++k) {
            for (int j = 0; j < C.n; ++j) {
                C[{i, j}] += A[{i, k}] * B[{k, j}];
            }
        }
    }
    return C;
}

template<class T>
vector<T> sol_lin_equ(const Matrix<T>& A, const vector<T>& b) {
    int n = A.n;
    assert(n == A.m);
    assert(n == (int)b.size());
    matrix<T> B(n, n + 1);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            B[{i, j}] = A[{i, j}];
        }
        B[{i, n}] = b[i];
    }
    rref(B);
    vector<T> x(n);
    for (int i = 0; i < n; ++i) {
        assert((B[{i, i}] == 1));
        x[i] = B[{i, n}];
    }
    return x;
}

template<class T>
Matrix<T> inv(const Matrix<T>& A) {
    int n = A.n;
    assert(n == A.m);
    matrix<T> B(n, n + n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            B[{i, j}] = A[{i, j}];
            B[{i, n + i}] = 1;
        }
    }
    rref(B);
    matrix<T> X(n);
    for (int i = 0; i < n; i++) {
        assert((B[{i, i}] == 1));
        for (int j = 0; j < n; j++) {
            X[{i, j}] = B[{i, n + j}];
        }
    }
    return X;
}

void rref(vector<ll>& A) {
	if (A.empty()) return;
    int m = A.size();
    int sz = 60;
    for (int j = sz - 1, r = 0; j >= 0 && r < m; --j) {
        for (int i = r; i < m; i++) {
            if ((A[i] >> j) & 1) {
                swap(A[r], A[i]);
                break;
            }
        }
        if ((A[r] >> j) & 1) {
            for (int i = 0; i < m; i++) if (i != r) {
                if ((A[i] >> j) & 1) {
                    A[i] ^= A[r];
                }
            }
            ++r;
        }
    }
	while (A.back() == 0ll) A.pop_back();
}