struct point {
	point rot(LD t) const { // 逆时针
		return {x*cos(t) - y*sin(t), x*sin(t) + y*cos(t)};}
	point rot90() const { return {-y, x}; }};
bool two_side(cp a, cp b, cl c) {
	return sgn (det(a - c.s, c.t - c.s))
		* sgn (det(b - c.s, c.t - c.s)) < 0; }
point line_inter(cl a, cl b) { // 直线交点
	LD s1 = det(a.t - a.s, b.s - a.s);
	LD s2 = det(a.t - a.s, b.t - a.s);
	return (b.s * s2 - b.t * s1) / (s2 - s1); }
vector <point> cut (const vector<point> &c, line l) {
	vector <point> ret; // 线切凸包，turn left 必须 <=
	int n = (int) c.size();
	if (!n) return ret;
	for (int i = 0; i < n; ++i) {
		int j = (i + 1) % n;
		if (turn_left (l.s, l.t, c[i])) ret.push_back(c[i]);
		if (two_side (c[i], c[j], l))
			ret.push_back(line_inter(l, {c[i], c[j]})); }
	return ret; }
bool point_on_segment(cp a,cl b){ // 点在线段上
	return sgn (det(a - b.s, b.t - b.s)) == 0 // 在直线上
	&& sgn (dot (b.s - a, b.t - a)) <= 0;}
bool inter_judge(cl a,cl b) { // 线段判非严格交
	if (point_on_segment (b.s, a)
	 || point_on_segment (b.t, a)) return true;
	if (point_on_segment (a.s, b)
	 || point_on_segment (a.t, b)) return true;
	return two_side (a.s, a.t, b)
	    && two_side (b.s, b.t, a); }
point proj_to_line (cp a, cl b) { // 点在直线投影
	point st = b.t - b.s;
	return b.s + st * (dot(a - b.s, st) / dot(st, st));}
LD point_to_line (cp a, cl b) { // 点到直线距离
	return abs(det(b.t-b.s, a-b.s)) / dis(b.s, b.t); }
LD point_to_segment (cp a, cl b) { // 点到线段距离
	if (sgn (dot (b.s - a, b.t - b.s))
	* sgn (dot (b.t - a, b.t - b.s)) >= 0)
		return min (dis (a, b.s), dis (a, b.t));
	return point_to_line(a, b); }
bool in_polygon (cp p, const vector <point> & po) {
	int n = (int) po.size (); int cnt = 0;
	for (int i = 0; i < n; ++i) {
		point a = po[i], b = po[(i + 1) % n];
		if (point_on_segment (p, {a, b})) return true;
		int x = sgn (det(p - a, b - a));
		int y = sgn (a.y - p.y);
		int z = sgn (b.y - p.y);
		if (x > 0 && y <= 0 && z > 0) ++cnt;
		if (x < 0 && z <= 0 && y > 0) --cnt; }
	return cnt != 0; }
bool point_on_ray (cp a, cl b) { // 点在射线上
	return sgn (det(a - b.s, b.t - b.s)) == 0
	&& sgn (dot (a - b.s, b.t - b.s)) >= 0; }
bool ray_inter_judge(line a, line b) { // 射线判交
	LD s1, s2; // can be LL
	s1 = det(a.t - a.s, b.s - a.s);
	s2 = det(a.t - a.s, b.t - a.s);
	if (sgn(s1) == 0 && sgn(s2) == 0) {
		return sgn(dot(a.t - a.s, b.s - a.s)) >= 0
		    || sgn(dot(b.t - b.s, a.s - b.s)) >= 0; }
	if (!sgn(s1 - s2) || sgn(s1) == sgn(s2 - s1)) return 0;
	swap(a, b);
	s1 = det(a.t - a.s, b.s - a.s);
	s2 = det(a.t - a.s, b.t - a.s);
	return sgn(s1) != sgn(s2 - s1); }