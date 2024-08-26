struct point {
	point rot(LD t) const { // 逆时针
		return {x*cos(t) - y*sin(t), x*sin(t) + y*cos(t)};}
	point rot90() const { return {-y, x}; }};
bool two_side(cp a, cp b, cl c) {
	return turn(c.s, c.t, a) * turn(c.s, c.t, b) < 0; }
point line_inter(cl a, cl b) { // 直线交点
	LD s1 = det(a.t - a.s, b.s - a.s);
	LD s2 = det(a.t - a.s, b.t - a.s);
	return (b.s * s2 - b.t * s1) / (s2 - s1); }
vector <point> cut (const vector<point> &c, line l) {
	vector <point> ret; // 线切凸包
	int n = (int) c.size(); if (!n) return ret;
	for (int i = 0; i < n; i++) {
		int j = (i + 1) % n;
		if (turn (l.s, l.t, c[i]) >= 0) ret.push_back(c[i]);
		if (two_side (c[i], c[j], l))
			ret.push_back(line_inter(l, {c[i], c[j]})); }
	return ret; }
bool pos (cp a,cl b){ // point_on_segment 点在线段上
	return turn(b.s, b.t, a) == 0 // 在直线上
	&& sgn(dot(b.s - a, b.t - a)) <= 0;}
bool inter_judge(cl a,cl b) { // 线段判非严格交
	if (pos (b.s, a) || pos (b.t, a)) return true;
	if (pos (a.s, b) || pos (a.t, b)) return true;
	return two_side (a.s, a.t, b)
	    && two_side (b.s, b.t, a); }
point proj_to_line (cp a, cl b) { // 点在直线投影
	point st = b.t - b.s;
	return b.s + st * (dot(a - b.s, st) / dot(st, st));}
LD p2l (cp a, cl b) { // point_to_line
	return abs(det(b.t-b.s, a-b.s)) / dis(b.s, b.t); }
LD p2s (cp a, cl b) { // point_to_segment 注意退化
	if ( sgn(dot(b.s - a, b.t - b.s))
	   * sgn(dot(b.t - a, b.t - b.s)) >= 0)
		return min (dis (a, b.s), dis (a, b.t));
	return p2l (a, b); }
bool point_on_ray (cp a, cl b) { // 点在射线上
	return turn (b.s, b.t, a) == 0
	&& sgn(dot(a - b.s, b.t - b.s)) >= 0; }
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