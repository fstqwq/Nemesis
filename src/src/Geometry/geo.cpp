struct point {
	point rot(LD t) const { // 逆时针
		return {x*cos(t) - y*sin(t), x*sin(t) + y*cos(t)};}
	point rot90() const { return {-y, x}; }};
bool two_side(cp a,cp b,cl c) {
	return sgn (det(a - c.s, c.t - c.s))
		* sgn (det(b - c.s, c.t - c.s)) < 0; }
point line_inter(cl a, cl b) { // 直线交点
	LD s1 = det(a.t - a.s, b.s - a.s);
	LD s2 = det(a.t - a.s, b.t - a.s);
	return (b.s * s2 - b.t * s1) / (s2 - s1); }
// 线切凸包，可直接实现半平面交
vector <point> cut (const vector<point> &c, line p) {
	vector <point> ret;
	int n = (int) c.size();
	if (!n) return ret;
	for (int i = 0; i < n; ++i) {
		int j = (i + 1) % n;
		if (turn_left (p.s, p.t, c[i])) ret.push_back (c[i]);
		if (two_side (c[i], c[j], p))
			ret.push_back (line_inter (p, {c[i], c[j]})); }
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
LD point_to_line (cp a, cl b) { // 点到直线距离
	return abs (det(b.t-b.s, a-b.s)) / dis (b.s, b.t); }
point proj_to_line (cp a, cl b) { // 点在直线投影
	return b.s + (b.t - b.s)
	* (dot (a - b.s, b.t - b.s) / dis2(b.t, b.s)); }
LD point_to_segment (cp a, cl b) { // 点到线段距离
	if (sgn (dot (b.s - a, b.t - b.s))
	* sgn (dot (b.t - a, b.t - b.s)) <= 0)
		return abs(det(b.t - b.s, a - b.s)) / dis(b.s, b.t);
	return min (dis (a, b.s), dis (a, b.t)); }
bool in_polygon (cp p, const vector <point> & po) {
	int n = (int) po.size (); int cnt = 0;
	for (int i = 0; i < n; ++i) {
		point a = po[i], b = po[(i + 1) % n];
		if (point_on_segment (p, {a, b})) return true;
		int x = sgn (det(p - a, b - a)),
			y = sgn (a.y - p.y), z = sgn (b.y - p.y);
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
vector <point> line_circle_inter (cl a, cc b) {
	LD d = point_to_line (b.c, a);
	if (sgn (d - b.r) > 0)
		return {};
	LD x = sqrt(sqr(b.r)-sqr(d)));
	return {
		proj_to_line (b.c, a) + (a.s - a.t).unit() * x,
		proj_to_line (b.c, a) - (a.s - a.t).unit() * x};}
LD circle_inter_area (cc a, cc b) {
	LD d = dis (a.c, b.c);
	if (sgn (d - (a.r + b.r)) >= 0) return 0;
	if (sgn (d - abs(a.r - b.r)) <= 0) {
		LD r = min (a.r, b.r);
		return r * r * PI; }
	LD x = (d * d + a.r * a.r - b.r * b.r) / (2 * d),
		   t1 = acos (min (1., max (-1., x / a.r))),
		   t2 = acos (min (1., max (-1., (d - x) / b.r)));
	return sqr(a.r)*t1 + sqr(b.r)*t2 - d*a.r*sin(t1);}
vector <point> circle_inter (cc a, cc b) {
	if (a.c == b.c
		|| sgn (dis (a.c, b.c) - a.r - b.r) > 0
		|| sgn (dis (a.c, b.c) - abs (a.r - b.r)) < 0)
		return {};
	point r = (b.c - a.c).unit();
	LD d = dis (a.c, b.c);
	LD x = ((sqr (a.r) - sqr (b.r)) / d + d) / 2;
	LD h = sqrt (sqr (a.r) - sqr (x));
	if (sgn (h) == 0) return {a.c + r * x};
	return {a.c + r * x + r.rot90 () * h,
			  a.c + r * x - r.rot90 () * h}; }
// 返回按照顺时针方向
vector <point> tangent (cp a, cc b) {
	circle p = make_circle (a, b.c);
	return circle_inter (p, b); }
vector <line> extangent (cc a, cc b) {
	vector <line> ret;
	if (sgn(dis (a.c, b.c)-abs (a.r - b.r))<=0) return ret;
	if (sgn (a.r - b.r) == 0) {
		point dir = b.c - a.c;
		dir = (dir * a.r / dir.len ()).rot90 ();
		ret.push_back ({a.c + dir, b.c + dir});
		ret.push_back ({a.c - dir, b.c - dir});
	} else {
		point p = (b.c * a.r - a.c * b.r) / (a.r - b.r); 
		vector pp = tangent (p, a), qq = tangent (p, b);
		if (pp.size () == 2 && qq.size () == 2) {
			if (sgn (a.r-b.r) < 0)
				swap (pp[0], pp[1]), swap (qq[0], qq[1]);
			ret.push_back({pp[0], qq[0]});
			ret.push_back({pp[1], qq[1]}); } }
	return ret; }
vector <line> intangent (cc a, cc b) {
	vector <line> ret;
	point p = (b.c * a.r + a.c * b.r) / (a.r + b.r); 
	vector pp = tangent (p, a), qq = tangent (p, b);
	if (pp.size () == 2 && qq.size () == 2) {
		ret.push_back ({pp[0], qq[0]});
		ret.push_back ({pp[1], qq[1]}); }
	return ret; }
