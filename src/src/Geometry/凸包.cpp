#define cp const point &
bool turn_left(cp a, cp b, cp c) {
	return sgn (det (b - a, c - a)) >= 0; }
vector <point> convex_hull (vector <point> a) {
	int n = (int) a.size (), cnt = 0;
	if (n < 2) return a; 
	sort (a.begin(), a.end()); // less<pair>
	vector <point> ret;
	for (int i = 0; i < n; ++i) {
		while (cnt > 1
		&& turn_left (ret[cnt - 2], a[i], ret[cnt - 1]))
			--cnt, ret.pop_back ();
		++cnt, ret.push_back (a[i]); }
	int fixed = cnt;
	for (int i = n - 2; i >= 0; --i) {
		while (cnt > fixed
		&& turn_left (ret[cnt - 2], a[i], ret[cnt - 1]))
			--cnt, ret.pop_back ();
		++cnt, ret.push_back (a[i]); }
	ret.pop_back (); return ret;
} // counter-clockwise, ret[0] = min(pair(x, y))