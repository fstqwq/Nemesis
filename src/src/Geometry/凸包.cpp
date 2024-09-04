#define cp const point &
int turn (cp a, cp b, cp c) { return sgn(det(b-a, c-a)); }
vector <point> convex_hull (vector <point> a) {
	sort (a.begin(), a.end()); // 小于号 (y, x) 字典序
	a.erase(unique(a.begin(), a.end()), a.end());//必要时去重
	int n = (int) a.size (), cnt = 0;
	vector <point> ret;
	for (int i = 0; i < n; i++) {
		while (cnt > 1
		&& turn (ret[cnt - 2], ret[cnt - 1], a[i]) <= 0)
			--cnt, ret.pop_back (); // 保留边界:    <  0
		++cnt, ret.push_back (a[i]); }
	for (int i = n - 2, fixed = cnt; i >= 0; i--) {
		while (cnt > fixed
		&& turn (ret[cnt - 2], ret[cnt - 1], a[i]) <= 0)
			--cnt, ret.pop_back (); // 所有点共线边界会保留两次
		++cnt, ret.push_back (a[i]); }
	if (n > 1) ret.pop_back (); // n <= 2 吗？
	return ret; } // 小于号为 (y, x) 时边 [0, 2pi) 逆时针