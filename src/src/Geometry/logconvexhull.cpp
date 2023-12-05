/* INF 开到值域, point operator < > 为 pair(x, y)
除距离可改为整数: LD to LL
传入逆时针凸包要求无重点, 面积非空 */
struct Convex {
 int n, lz, uz;
 vector<point> a, upper, lower;
 Convex(vector<point> _a) {
 	n = (int) _a.size(); int k = 0;
 	a = _a; // if a[0] is lowest, otherwise:
 /*for(int i = 1; i < n; i++) if (_a[i] < _a[k]) k = i;
 for(int i = 0; i < n; i++) a.push_back(_a[(i + k) % n]);*/
 	for(int i = 1; i < n; ++ i) if (a[k] < a[i]) k = i;
 	for(int i = 0; i <= k; ++ i) lower.push_back(a[i]);
 	for(int i = k; i < n; ++ i) upper.push_back(a[i]);
 	upper.push_back(a[0]);
 	lz = (int) lower.size(); uz = (int) upper.size(); }
 const point & at (int x) { return a[x % n]; }
 pair <LD, int> get_tan(vector <point> & con, cp vec) {
 	int l = 0, r = (int) con.size() - 2;
 	for ( ; l + 1 < r; ) {
 		int m = (l + r) / 2;
 		if (sgn(det(con[m + 1] - con[m], vec)) > 0) r = m;
 		else l = m;
 	}
 	return max(make_pair(det(vec, con[r]), r), make_pair(det(vec, con[0]), 0)); }
 void upd_tan(cp p, int id, int &i0, int &i1) {
 	if (det(a[i0] - p, a[id] - p) > 0) i0 = id;
 	if (det(a[i1] - p, a[id] - p) < 0) i1 = id; }
 // 判定点是否在凸包内, 在边界返回 true
 bool contain(cp p) {
 	if (p.x < lower[0].x || p.x > lower.back().x) return 0;
 	int id = int(lower_bound(lower.begin(), lower.end(), point(p.x, -INF)) - lower.begin());
 	if (lower[id].x == p.x) {
 		if (lower[id].y > p.y) return 0;
 	} else if (det(lower[id - 1] - p, lower[id] - p) < 0)
 		return 0;
 	id = int(lower_bound(upper.begin(), upper.end(), point(p.x, INF), greater<point>()) - upper.begin());
 	if (upper[id].x == p.x) {
 		if (upper[id].y < p.y) return 0;
 	} else if (det(upper[id - 1] - p, upper[id] - p) < 0)
 		return 0;
 	return 1; }
 // 点关于凸包的切点, 在凸包外有序返回编号, 共线返回任意
 void search(int l, int r, cp p, int &i0, int &i1) {
 	if (l == r) return;
 	upd_tan(p, l % n, i0, i1);
 	int sl = sgn(det(at(l) - p, at(l + 1) - p));
 	for ( ; l + 1 < r; ) {
 		int m = (l + r) / 2;
 		int sm = sgn(det(at(m) - p, at(m + 1) - p));
 		if (sm == sl) l = m;
 		else r = m;
 	}
 	upd_tan(p, r % n, i0, i1); }
 bool get_tan(cp p, int &i0, int &i1) {
 	if (contain(p)) return 0; // 严格在凸包内无解
 	i0 = i1 = 0;
 	int id = int(lower_bound(lower.begin(), lower.end(), p) - lower.begin());
 	if (id < lz && lower[id] == p) //顶点上返回相邻边
		i0 = (id + n - 1) % n, i1 = (id + 1) % n;
 	search(0, id, p, i0, i1);
 	search(id, lz, p, i0, i1);
 	id = int(lower_bound(upper.begin(), upper.end(), p, greater<point>()) - upper.begin());
 	if (id < uz && upper[id] == p) //顶点上返回相邻边
		i0 = (lz - 2 + id) % n, i1 = (lz + id) % n;
	search(lz - 1, lz - 1 + id, p, i0, i1);
	search(lz - 1 + id, lz - 1 + uz, p, i0, i1);
 	return 1; }
 // 求凸包外一点到凸包的最短距离, 如凸包内返回 0; 结果产生浮点
 LD search(int l, int r, cp p) {
 	if (l == r) return dis (p, at(l));
 	int sl = sgn(dot(a[l%n]-p, at(l + 1)-at(l)));
 	for ( ; l + 1 < r; ) {
		int m = (l + r) / 2;
		int sm = sgn(dot(at(m)-p,at(m+1)-at(m)));
		if (sm == sl) l = m; else r = m;
	} return point_to_segment(p, {at(l), at(l+1)}); }
 LD get_dis(cp p) {
 	if (contain(p)) return 0;
 	int i0, i1;
 	get_tan(p, i0, i1);
 	return search(i0, i1 + (i0 > i1 ? n : 0), p); }
 // 求凸包上和向量 vec 叉积最大的点编号, 共线返回任意
 int get_tan(cp vec) {
 	pair<LD, int> ret = get_tan(upper, vec);
 	ret.second = (ret.second + lz - 1) % n;
 	ret = max(ret, get_tan(lower, vec));
 	return ret.second; }
 // 求凸包和直线 u,v 的交点, 如果无严格相交返回 0. 如果有则是和 (i,next(i)) 的交点, 两个点无序, 交在点上不确定返回前后两条线段其中之一
 int search(cp u, cp v, int l, int r) {
 	int sl = sgn(det(v - u, at(l) - u));
 	for ( ; l + 1 < r; ) {
 		int m = (l + r) / 2;
 		int sm = sgn(det(v - u, at(m) - u));
 		if (sm == sl) l = m;
 		else r = m; }
 	return l % n; }
 bool get_inter(cp u, cp v, int &i0, int &i1) {
 	int p0 = get_tan(u - v), p1 = get_tan(v - u);
 	if (sgn(det(v-u, a[p0]-u))*sgn(det(v-u, a[p1]-u))<0) {
 		if (p0 > p1) swap(p0, p1);
 		i0 = search(u, v, p0, p1);
 		i1 = search(u, v, p1, p0 + n);
 		return true;
 	} else return 0; }
};
