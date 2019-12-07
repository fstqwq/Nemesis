bool turn_left (const point &a, const point &b, const point &c) {
	return sgn (det (b - a, c - a)) >= 0; }
std::vector <point> convex_hull (std::vector <point> a) {
	int n = (int) a.size (), cnt = 0;
	std::sort (a.begin (), a.end ());
	std::vector <point> ret;
	for (int i = 0; i < n; ++i) {
		while (cnt > 1 && turn_left (ret[cnt - 2], a[i], ret[cnt - 1])) {
			--cnt; ret.pop_back (); }
		ret.push_back (a[i]); ++cnt; }
	int fixed = cnt;
	for (int i = n - 2; i >= 0; --i) {
		while (cnt > fixed && turn_left (ret[cnt - 2], a[i], ret[cnt - 1])) {
			--cnt; ret.pop_back (); }
		ret.push_back (a[i]); ++cnt; }
	ret.pop_back (); return ret; }