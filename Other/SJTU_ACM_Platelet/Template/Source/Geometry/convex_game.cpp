const int INF = 1000000000;
struct Convex
{
	int n;
	vector<Point> a, upper, lower;
	Convex(vector<Point> _a) : a(_a) {
		n = a.size();
		int ptr = 0;
		for(int i = 1; i < n; ++ i) if (a[ptr] < a[i]) ptr = i;
		for(int i = 0; i <= ptr; ++ i) lower.push_back(a[i]);
		for(int i = ptr; i < n; ++ i) upper.push_back(a[i]);
		upper.push_back(a[0]);
	}
	int sign(long long x) { return x < 0 ? -1 : x > 0; }
	pair<long long, int> get_tangent(vector<Point> &convex, Point vec) {
		int l = 0, r = (int)convex.size() - 2;
		for( ; l + 1 < r; ) {
			int mid = (l + r) / 2;
			if (sign((convex[mid + 1] - convex[mid]).det(vec)) > 0) r = mid;
			else l = mid;
		}
		return max(make_pair(vec.det(convex[r]), r)
			, make_pair(vec.det(convex[0]), 0));
	}
	void update_tangent(const Point &p, int id, int &i0, int &i1) {
		if ((a[i0] - p).det(a[id] - p) > 0) i0 = id;
		if ((a[i1] - p).det(a[id] - p) < 0) i1 = id;
	}
	void binary_search(int l, int r, Point p, int &i0, int &i1) {
		if (l == r) return;
		update_tangent(p, l % n, i0, i1);
		int sl = sign((a[l % n] - p).det(a[(l + 1) % n] - p));
		for( ; l + 1 < r; ) {
			int mid = (l + r) / 2;
			int smid = sign((a[mid % n] - p).det(a[(mid + 1) % n] - p));
			if (smid == sl) l = mid;
			else r = mid;
		}
		update_tangent(p, r % n, i0, i1);
	}
	int binary_search(Point u, Point v, int l, int r) {
		int sl = sign((v - u).det(a[l % n] - u));
		for( ; l + 1 < r; ) {
			int mid = (l + r) / 2;
			int smid = sign((v - u).det(a[mid % n] - u));
			if (smid == sl) l = mid;
			else r = mid;
		}
		return l % n;
	}
	// 判定点是否在凸包内，在边界返回 true
	bool contain(Point p) { 
		if (p.x < lower[0].x || p.x > lower.back().x) return false;
		int id = lower_bound(lower.begin(), lower.end()
			, Point(p.x, -INF)) - lower.begin();
		if (lower[id].x == p.x) { 
			if (lower[id].y > p.y) return false;
		} else if ((lower[id - 1] - p).det(lower[id] - p) < 0) return false;
		id = lower_bound(upper.begin(), upper.end(), Point(p.x, INF)
			, greater<Point>()) - upper.begin();
		if (upper[id].x == p.x) {
			if (upper[id].y < p.y) return false;
		} else if ((upper[id - 1] - p).det(upper[id] - p) < 0) return false;
		return true;
	}
	// 求点 p 关于凸包的两个切点，如果在凸包外则有序返回编号
	// 共线的多个切点返回任意一个，否则返回 false
	bool get_tangent(Point p, int &i0, int &i1) { 
		if (contain(p)) return false;
		i0 = i1 = 0;
		int id = lower_bound(lower.begin(), lower.end(), p) - lower.begin();
		binary_search(0, id, p, i0, i1);
		binary_search(id, (int)lower.size(), p, i0, i1);
		id = lower_bound(upper.begin(), upper.end(), p
			, greater<Point>()) - upper.begin();
		binary_search((int)lower.size() - 1, (int)lower.size() - 1 + id, p, i0, i1);
		binary_search((int)lower.size() - 1 + id
			, (int)lower.size() - 1 + (int)upper.size(), p, i0, i1);
		return true;
	}
	// 求凸包上和向量 vec 叉积最大的点，返回编号，共线的多个切点返回任意一个
	int get_tangent(Point vec) { 
		pair<long long, int> ret = get_tangent(upper, vec);
		ret.second = (ret.second + (int)lower.size() - 1) % n;
		ret = max(ret, get_tangent(lower, vec));
		return ret.second;
	}
	// 求凸包和直线 u,v 的交点, 如果无严格相交返回 false. 
	//如果有则是和 (i,next(i)) 的交点, 两个点无序, 交在点上不确定返回前后两条线段其中之一
	bool get_intersection(Point u, Point v, int &i0, int &i1) { 
		int p0 = get_tangent(u - v), p1 = get_tangent(v - u);
		if (sign((v - u).det(a[p0] - u)) * sign((v - u).det(a[p1] - u)) < 0) {
			if (p0 > p1) swap(p0, p1);
			i0 = binary_search(u, v, p0, p1);
			i1 = binary_search(u, v, p1, p0 + n);
			return true;
		} else {
			return false;
		}
	}
};
