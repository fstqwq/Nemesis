#define cp const point &
bool turn_left(cp a, cp b, cp c) {
	return sgn(det (b - a, c - a)) >= 0;} // strict: ... > 0
// 要求非退化凸包，或半平面交面积 0 时返回空集：用 strict
vector <point> convex_hull (vector <point> a) {
	int n = (int) a.size (), cnt = 0;
	sort (a.begin(), a.end()); // less<pair>
	if (n <= 2) return a; //未处理重点,非退化凸包: return {}
	vector <point> ret;
	for (int i = 0; i < n; ++i) {
		while (cnt > 1
		&& !turn_left (ret[cnt - 2], ret[cnt - 1], a[i]))
			--cnt, ret.pop_back ();
		++cnt, ret.push_back (a[i]); }
	int fixed = cnt;
	for (int i = n - 2; i >= 0; --i) {
		while (cnt > fixed
		&& !turn_left (ret[cnt - 2], ret[cnt - 1], a[i]))
			--cnt, ret.pop_back ();
		++cnt, ret.push_back (a[i]); }
	ret.pop_back (); return ret;
} // counter-clockwise, ret[0] = min(pair(x, y))