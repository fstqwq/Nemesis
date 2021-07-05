#define cp const point &
const double eps = 1e-7;
point base;
bool cmp(cp a, cp b) {
	int d = sgn(det(a - base, b - base));
	if (d) return d > 0;
	else return (a - base).len() < (b - base).len(); }
bool turn_left(cp a, cp b, cp c) {
	return sgn (det (b - a, c - a)) >= 0; }
vector <point> convex_hull (vector <point> a) {
	int n = (int) a.size (), cnt = 0;
	sort (a.begin (), a.end (), cmp);
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
	ret.pop_back (); return ret; }
