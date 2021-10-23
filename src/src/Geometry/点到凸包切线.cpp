typedef vector<vector<P>> Convex;
#define sz(x) ((int) x.size())
int lb(P x, const vector<P> & v, int le, int ri, int sg) {
	if (le > ri) le = ri;
	int s(le), t(ri);
	while (le != ri) {
		int mid((le + ri) / 2);
		if (sign(det(v[mid] - x, v[mid + 1] - v[mid])) == sg)
			le = mid + 1; else ri = mid; }
	return le; } // le 即为下标, 按需返回
// v[0] 为顺时针上凸壳, v[1] 为顺时针下凸壳, 均允许起始两个点横坐标相同
// 返回值为真代表严格在凸包外, 顺时针旋转在 d1 方向先碰到凸包
bool getTan(P x, const Convex & v, int & d1, int & d2) {
	if (x.x < v[0][0].x) {
		d1 = lb(x, v[0], 0, sz(v[0]) - 1, 1);
		d2 = lb(x, v[1], 0, sz(v[1]) - 1, -1) + (int) v[0].size() - 1;
		return true;
	} else if(x.x > v[0].back().x) {
		d1 = lb(x, v[1], 0, sz(v[1]) - 1, 1) + (int) v[0].size() - 1;
		d2 = lb(x, v[0], 0, sz(v[0]) - 1, -1);
		return true;
	} else {
		for(int d(0); d < 2; d++) {
			int id(lower_bound(v[d].begin(), v[d].end(), x, [&](const P & a, const P & b) { return d == 0 ? a < b : b < a; }) - v[d].begin());
			if (id && (id == sz(v[d]) || det(v[d][id - 1] - x, v[d][id] - x) > 0)) {
				d1 = lb(x, v[d], id, sz(v[d]) - 1, 1);
				d2 = lb(x, v[d], 0, id, -1);
				if (d) {
					d1 += (int) v[0].size() - 1;
					d2 += (int) v[0].size() - 1; }
				return true; } } }
	return false; }
