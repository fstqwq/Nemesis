struct circle { point c; LD r;};
bool in_circle(cp a, const circle &b) {
	return (b.c - a).len() <= b.r; }
circle make_circle(point u, point v) {
	point p = (u + v) / 2;
	return circle(p, (u - p).len()); }
circle make_circle(cp a, cp b, cp c) {
	point p = b - a, q = c - a,
		s(dot(p, p) / 2, dot(q, q) / 2);
	LD d = det(p, q);
	p = point( det(s, point(p.y, q.y)),
		det(point(p.x, q.x), s) ) / d;
	return circle(a + p, p.len());
} // make_circle : 过参数点的最小圆
pair <point, point> line_circle_inter (cl a, cc c) {
	LD d = point_to_line (c.c, a);
	// 需要的话返回 vector <point>
	/* if (sgn (d - R) >= 0) return {}; */
	LD x = sqrt (sqr(c.r) - sqr(d)); // sqrt(max(0., ...))
	return {
		proj_to_line (c.c, a) + (a.s - a.t).unit() * x,
		proj_to_line (c.c, a) - (a.s - a.t).unit() * x }; }
LD circle_inter_area (cc a, cc b) { // 圆面积交
	LD d = dis (a.c, b.c);
	if (sgn (d - (a.r + b.r)) >= 0) return 0;
	if (sgn (d - abs(a.r - b.r)) <= 0) {
		LD r = min (a.r, b.r);
		return r * r * PI; }
	LD x = (d * d + a.r * a.r - b.r * b.r) / (2 * d),
		   t1 = acos (min (1., max (-1., x / a.r))),
		   t2 = acos (min (1., max (-1., (d - x) / b.r)));
	return sqr(a.r)*t1 + sqr(b.r)*t2 - d*a.r*sin(t1);}
vector <point> circle_inter (cc a, cc b) { // 圆交点
	if (a.c == b.c || sgn (dis (a.c, b.c) - a.r - b.r) > 0
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
	return circle_inter (make_circle (a, b.c), b); }
vector <line> extangent (cc a, cc b) {
	vector <line> ret;
	if (sgn(dis(a.c, b.c)-abs(a.r - b.r))<=0) return ret;
	if (sgn(a.r - b.r) == 0) {
		point dir = b.c - a.c;
		dir = (dir * a.r / dir.len()).rot90();
		ret.push_back({a.c + dir, b.c + dir});
		ret.push_back({a.c - dir, b.c - dir});
	} else {
		point p = (b.c * a.r - a.c * b.r) / (a.r - b.r); 
		vector u = tangent(p, a), v = tangent(p, b);
		if (u.size() == 2 && v.size() == 2) {
			if (sgn(a.r-b.r) < 0)
				swap(u[0], u[1]), swap(v[0], v[1]);
			ret.push_back({u[0], v[0]});
			ret.push_back({u[1], v[1]}); } }
	return ret; }
vector <line> intangent(cc a, cc b) {
	vector <line> ret;
	point p = (b.c * a.r + a.c * b.r) / (a.r + b.r); 
	vector u = tangent(p, a), v = tangent(p, b);
	if (u.size() == 2 && v.size() == 2) {
		ret.push_back({u[0], v[0]});
		ret.push_back({u[1], v[1]}); } return ret; }
circle min_circle (vector <point> p) { // 最小覆盖圆
 circle ret({0, 0}, 0);
 random_shuffle (p.begin (), p.end ());
 for (int i = 0; i < (int) p.size (); ++i)
  if (!in_circle(p[i], ret)) {
   ret = circle (p[i], 0);
   for (int j = 0; j < i; ++j) if (!in_circle(p[j], ret)) {
    ret = make_circle (p[j], p[i]);
    for (int k = 0; k < j; ++k) if (!in_circle(p[k], ret))
     ret = make_circle(p[i],p[j],p[k]);
  } } return ret; }