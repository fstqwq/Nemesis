#define cp const point &
int turn (cp a, cp b, cp c) { return sgn(det(b-a, c-a)); }
vector <point> convex_hull (vector <point> a) {
	int n = (int) a.size (), cnt = 0;
	sort (a.begin(), a.end()); // less<pair>
	vector <point> ret;
	for (int i = 0; i < n; ++i) {
		while (cnt > 1
		&& turn (ret[cnt - 2], ret[cnt - 1], a[i]) <= 0)
			--cnt, ret.pop_back (); // 保留凸包边界上的点：< 0
		++cnt, ret.push_back (a[i]); }
	int fixed = cnt;
	for (int i = n - 2; i >= 0; --i) {
		while (cnt > fixed
		&& turn (ret[cnt - 2], ret[cnt - 1], a[i]) <= 0)
			--cnt, ret.pop_back (); // 保留凸包边界上的点：< 0
		++cnt, ret.push_back (a[i]); }
	ret.pop_back (); return ret; // 注意凸包退化时返回值
} // 逆时针, ret[0] = min<pair>