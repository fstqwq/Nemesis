#define cp const point &
bool turn_left(cp a, cp b, cp c) {
	return sgn (det (b - a, c - a)) >= 0; }
vector <point> convex_hull (vector <point> a) {
	int n = (int) a.size (), cnt = 0;
	if (n < 3) return a; 
	point base = a[0];
	for (auto i : a) if (make_pair (i.x, i.y)
		< make_pair (base.x, base.y)) base = i;
	sort (a.begin (), a.end (), [] (cp &a, cp &b) {
		int d = sgn(det(a - base, b - base));
		if (d) return d > 0;
		else return (a - base).len() < (b - base).len();});
	vector <point> ret;
	for (int i = 0; i < n; ++i) {
		while (cnt > 1
		&& turn_left (ret[cnt - 2], a[i], ret[cnt - 1])) {
			--cnt; ret.pop_back ();
		}
		ret.push_back (a[i]); ++cnt;
	}
	int fixed = cnt;
	for (int i = n - 2; i >= 0; --i) {
		while (cnt > fixed
		&& turn_left (ret[cnt - 2], a[i], ret[cnt - 1])) {
			--cnt; ret.pop_back ();
		}
		ret.push_back (a[i]); ++cnt; 
	}
	ret.pop_back (); return ret;
}
