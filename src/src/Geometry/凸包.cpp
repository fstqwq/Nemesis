#define cp const point &
bool cmp(cp a, cp b) {
	int d = sgn(a - base, b - base);
	if (d) return d > 0;
	else return a.len() < b.len();}
bool onleft(cp a, cp b, cp c) {
	return sgn (det (b - a, c - a)) >= 0; }
vector <point> convex_hull (vector <point> a) {
	int n = (int) a.size (), cnt = 0;
	sort (a.begin (), a.end (), cmp);
	vector <point> ret;
	for (int i = 0; i < n; ++i) {
		while (cnt > 1
		&& onleft (ret[cnt - 2], a[i], ret[cnt - 1])) {
			--cnt; ret.pop_back ();
		} ret.push_back (a[i]); ++cnt; }
	int fixed = cnt;
	for (int i = n - 2; i >= 0; --i) {
		while (cnt > fixed
		&& onleft (ret[cnt - 2], a[i], ret[cnt - 1])) {
			--cnt; ret.pop_back ();
		} ret.push_back (a[i]); ++cnt; }
	ret.pop_back (); return ret; }
