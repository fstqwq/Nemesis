/* 给定凸包, $\log n$ 内完成各种询问, 具体操作有 :
   1. 判定一个点是否在凸包内
   2. 询问凸包外的点到凸包的两个切点
   3. 询问一个向量关于凸包的切点
   4. 询问一条直线和凸包的交点
   INF 为坐标范围, 需要定义点类 operator < > 为 pair(x, y)
   改成实数只需修改 sgn 函数, 以及把 LL 改为 double 即可
   传入凸包要求：无重点, 面积非空, 以及 pair(x,y) 的最小点放在第一个 */
const int INF = 1e9;
struct Convex {
 int n;
 vector<point> a, upper, lower;
 Convex(vector<point> _a) : a(_a) {
 	n = a.size();
 	int k = 0;
 	for(int i = 1; i < n; ++ i) if (a[k] < a[i]) k = i;
 	for(int i = 0; i <= k; ++ i) lower.push_back(a[i]);
 	for(int i = k; i < n; ++ i) upper.push_back(a[i]);
 	upper.push_back(a[0]);
 }
 pair <LL, int> get_tan(vector <point> & con, point vec) {
 	int l = 0, r = (int) con.size() - 2;
 	for ( ; l + 1 < r; ) {
 		int mid = (l + r) / 2;
 		if (sgn(det(con[mid + 1] - con[mid], vec)) > 0) r = mid;
 		else l = mid;
 	}
 	return max(make_pair (det(vec, con[r]), r), make_pair(det(vec, con[0]), 0));
 }
 void update_tan(cp p, int id, int &i0, int &i1) {
 	if (det(a[i0] - p, a[id] - p) > 0) i0 = id;
 	if (det(a[i1] - p, a[id] - p) < 0) i1 = id;
 }
 void search(int l, int r, point p, int &i0, int &i1) {
 	if (l == r) return;
 	update_tan(p, l % n, i0, i1);
 	int sl = sgn(det(a[l % n] - p, a[(l + 1) % n] - p));
 	for ( ; l + 1 < r; ) {
 		int mid = (l + r) / 2;
 		int smid = sgn(det(a[mid % n] - p, a[(mid + 1) % n] - p));
 		if (smid == sl) l = mid;
 		else r = mid;
 	}
 	update_tan(p, r % n, i0, i1);
 }
 int search(point u, point v, int l, int r) {
 	int sl = sgn(det(v - u, a[l % n] - u));
 	for ( ; l + 1 < r; ) {
 		int mid = (l + r) / 2;
 		int smid = sgn(det(v - u, a[mid % n] - u));
 		if (smid == sl) l = mid;
 		else r = mid;
 	}
 	return l % n;
 }
 // 判定点是否在凸包内, 在边界返回 true
 bool contain(point p) {
 	if (p.x < lower[0].x || p.x > lower.back().x) return false;
 	int id = lower_bound(lower.begin(), lower.end(), point(p.x, -INF)) - lower.begin();
 	if (lower[id].x == p.x) {
 		if (lower[id].y > p.y) return false;
 	} else if (det(lower[id - 1] - p, lower[id] - p) < 0) return false;
 	id = lower_bound(upper.begin(), upper.end(), point(p.x, INF), greater<point>()) - upper.begin();
 	if (upper[id].x == p.x) {
 		if (upper[id].y < p.y) return false;
 	} else if (det(upper[id - 1] - p, upper[id] - p) < 0) return false;
 	return true;
 }
 // 求点 p 关于凸包的两个切点, 如果在凸包外则有序返回编号, 共线的多个切点返回任意一个, 否则返回 false
 bool get_tan(point p, int &i0, int &i1) {
 	i0 = i1 = 0;
 	int id = int(lower_bound(lower.begin(), lower.end(), p) - lower.begin());
 	search(0, id, p, i0, i1);
 	search(id, (int)lower.size(), p, i0, i1);
 	id = int(lower_bound(upper.begin(), upper.end(), p, greater <point> ()) - upper.begin());
 	search((int)lower.size() - 1, (int) lower.size() - 1 + id, p, i0, i1);
 	search((int)lower.size() - 1 + id, (int) lower.size() - 1 + (int)upper.size(), p, i0, i1);
 	return true;
 }
 // 求凸包上和向量 vec 叉积最大的点, 返回编号, 共线的多个切点返回任意一个
 int get_tan(point vec) {
 	pair<LL, int> ret = get_tan(upper, vec);
 	ret.second = (ret.second + (int)lower.size() - 1) % n;
 	ret = max(ret, get_tan(lower, vec));
 	return ret.second;
 }
 // 求凸包和直线 u,v 的交点, 如果无严格相交返回 false. 如果有则是和 (i,next(i)) 的交点, 两个点无序, 交在点上不确定返回前后两条线段其中之一
 bool get_inter(point u, point v, int &i0, int &i1) {
 	int p0 = get_tan(u - v), p1 = get_tan(v - u);
 	if (sgn(det(v - u, a[p0] - u)) * sgn(det(v - u, a[p1] - u)) < 0) {
 		if (p0 > p1) swap(p0, p1);
 		i0 = search(u, v, p0, p1);
 		i1 = search(u, v, p1, p0 + n);
 		return true;
 	} else {
 		return false;
 	}
 }};
