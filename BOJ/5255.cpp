#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;

const long double EPS = 1e-9;

template<class T>
struct Point {
	T x, y;
	explicit Point(T x = 0, T y = 0) : x(x), y(y) {}
	bool operator< (Point p) const { return tie(x, y) < tie(p.x, p.y); }
	bool operator== (Point p) const { return tie(x, y) == tie(p.x, p.y); }
	Point operator+ (Point p) const { return Point(x + p.x, y + p.y); }
	Point operator- (Point p) const { return Point(x - p.x, y - p.y); }
	Point operator* (T d) const { return Point(x * d, y * d); }
	Point operator/(T d) const { return Point(x / d, y / d); }
	T dot(Point p) const { return x * p.x + y * p.y; }
	T cross(Point p) const { return x * p.y - y * p.x; }
	T cross(Point a, Point b) const { return (a - *this).cross(b - *this); }
	T dist2() const { return x * x + y * y; }
	double dist() const { return sqrt((double)dist2()); }
	double angle() const { return atan2(y, x); } // angle to x−axis in interval [−pi, pi]
	Point unit() const { return *this / dist(); } // makes dist() = 1
	Point perp() const { return Point(-y, x); } // rotates +90 degrees
	Point normal() const { return perp().unit(); }
	// returns point rotated ’a’ radians ccw around the origin
	Point rotate(double a) const { return Point(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a)); }
};

template<class T>
struct Line {
	Point<T> s, e;
	bool sinPos() const { return s.y == e.y ? s.x <= e.x : s.y <= e.y; } // angle in [0, pi)
	bool operator< (Line l) const { return sinPos() != l.sinPos() ? sinPos() > l.sinPos() : (e - s).cross(l.e - l.s) >= 0; }
	Line operator+ (Point<T> p) const { return {s + p, e + p}; }
	Line operator- (Point<T> p) const { return {s - p, e - p}; }
	bool onSegment(Point<T> p) const { return abs(p.cross(s, e)) < EPS && (s - p).dot(e - p) < EPS; }
	Line normTrans(T x) const { return *this + (e - s).normal() * x; }
	double lineDist(Point<T> p) const { return (double)(e - s).cross(p - s) / (e - s).dist(); }
	double segDist(Point<T> p) const {
		if (s == e) return (p - s).dist();
		double d = (e - s).dist2(), t = min(d, max(0.0, (double) (p - s).dot(e - s)));
		return ((p - s) * d - (e - s) * t).dist() / d;
	}
	pair<int, Point<T>> lineInter(Line l) const {
		auto d = (e - s).cross(l.e - l.s);
		if (d == 0) return {-(s.cross(e, l.s) == 0), Point<T>(0, 0)};
		auto p = l.s.cross(e, l.e), q = l.s.cross(l.e, s);
		return {1, (s * p + e * q) / d};
	}
	pair<int, Point<T>> segInter(Line l) const {
		auto sgn = [&](T x) { return (x > 0) - (x < 0); };
		auto oa = l.s.cross(l.e, s), ob = l.s.cross(l.e, e),
		oc = s.cross(e, l.s), od = s.cross(e, l.e);
		// Checks if intersection is single non−endpoint point.
		if (sgn(oa) * sgn(ob) < 0 && sgn(oc) * sgn(od) < 0)
			return {1, (s * ob - e * oa) / (ob - oa)};
		set<Point<T>> spts;
		if (l.onSegment(s)) spts.insert(s);
		if (l.onSegment(e)) spts.insert(e);
		if (onSegment(l.s)) spts.insert(l.s);
		if (onSegment(l.e)) spts.insert(l.e);
		if (spts.size() == 1) return {1, *spts.begin()};
		if (spts.size() == 0) return {0, Point<T>(0, 0)};
		return {-1, Point<T>(0, 0)};
	}
};

template<class P>
vector<P> convexHull(vector<P> pts) {
	if (pts.size() <= 1) return pts;
	sort(pts.begin(), pts.end());
	P unit = pts[0];
	for (auto& i: pts) i = i - unit;
	sort(next(pts.begin()), pts.end(), [](const P& a, P& b) {
		if (a.cross(b) == 0) {
			if (a.x == b.x) return a.y < b.y;
			return a.x < b.x;
		}
		return a.cross(b) > 0;
	});
	vector<P> h;
	h.push_back(pts[0]); h.push_back(pts[1]);
	for (int i = 2; i < pts.size(); ++i) {
		while (h.size() >= 2) {
			P b = h.back(); h.pop_back();
			P a = h.back();
			if (a.cross(b, pts[i]) > 0) {
				h.push_back(b);
				break;
			}
		}
		h.push_back(pts[i]);
	}
	for (auto& i: h) i = i + unit;
	return h;
}

// rotating calipers(convex)
template<class T>
pair<Point<T>, Point<T>> hullDiameter(vector<Point<T>>& pts) {
	int n = pts.size();
	if (n == 0) return {Point<T>(0, 0), Point<T>(0, 0)};
	if (n == 1) return {pts[0], pts[0]};
	pair<T, pair<Point<T>, Point<T>>> res({0, {pts[0], pts[0]}});
	int j = 1;
	for (int i = 0; i < j; ++i) {
		while (true) {
			res = max(res, {(pts[i] - pts[j]).dist2(), {pts[i], pts[j]}});
			if ((pts[(j + 1) % n] - pts[j]).cross(pts[i + 1] - pts[i]) >= 0) break;
			j = (j + 1) % n;
		}
	}
	return res.second;
}

// half plane intersection(convex)
template<class T>
vector<Point<T>> hpi(vector<Line<T>> lines) {
	// intersection of a, b is not part of c's half plane
	auto bad = [&](Line<T>& a, Line<T>& b, Line<T>& c) {
		auto v = a.lineInter(b);
		if (v.first != 1) return false;
		return c.s.cross(c.e, v.second) < EPS;
	};
	sort(lines.begin(), lines.end());
	deque<Line<T>> dq;
	for (int i = 0; i < lines.size(); ++i) {
		while(dq.size() >= 2 && bad(dq[(int) dq.size() - 2], dq.back(), lines[i])) dq.pop_back();
		while(dq.size() >= 2 && bad(dq[0], dq[1], lines[i])) dq.pop_front();
		if (dq.size() < 2 || !bad(dq.back(), lines[i], dq[0])) dq.push_back(lines[i]);
	}
	vector<Point<T>> ret;
	if (dq.size() >= 3) for (int i=0; i < dq.size(); ++i) {
		int j = (i + 1) % dq.size();
		auto v = dq[i].lineInter(dq[j]);
		if (v.first == 1) ret.push_back(v.second);
	}
	return ret;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int n;
	cin >> n;
	vector<Point<ld>> pts(n);
	for (int i = 0; i < n; ++i) cin >> pts[i].x >> pts[i].y;
	vector<Line<ld>> lines;
	for (int i = 0; i < n; ++i) {
		int j = (i + 1) % n;
		lines.push_back({pts[i], pts[j]});
	}
	ld l = 0, r = 4e7, mid;
	for (int t = 0; t < 50; ++t) {
		mid = (l + r) / 2;
		vector<Line<ld>> nlines = lines;
		for (auto& i: nlines) i = i.normTrans(mid);
		auto npts = hpi(nlines);
		if (npts.empty()) {
			r = mid;
			continue;
		}
		auto mx = hullDiameter(npts);
		if ((mx.second - mx.first).dist() > 2 * mid + EPS) l = mid;
		else r = mid;
	}
	cout.precision(4);
	cout << fixed;
	cout << l << "\n";
}