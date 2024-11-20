struct circle { point c; LD r;};
bool in_circle(cp a, const circle &b) {
	return sgn(b.r - dis(b.c, a)) >= 0; }
circle make_circle(cp a, cp b) { // 以 a b 为直径的圆
	point p = (a + b) / 2;
	return {p, dis(a, p)}; }
circle make_circle(cp a, cp b, cp c) { // 三点共线 inf / nan
	point bc = c - b, ca = a - c, ab = b - a;
	point o = (b + c - bc.rot90()*dot(ca,ab)/det(ca,ab)) / 2;
	return {o, dis(o, a)}; } // 检查上一行正负号
circle min_circle (vector <point> p) { // 最小覆盖圆
 circle ret({0, 0}, 0);
 shuffle (p.begin (), p.end (), rng);
 for (int i = 0; i < (int) p.size (); i++)
  if (!in_circle(p[i], ret)) {
   ret = circle (p[i], 0);
   for (int j = 0; j < i; j++) if (!in_circle(p[j], ret)) {
    ret = make_circle (p[i], p[j]);
    for (int k = 0; k < j; k++) if (!in_circle(p[k], ret))
     ret = make_circle (p[i], p[j], p[k]);
  } } return ret; }
pair <point, point> line_circle_inter (cl a, circle c) {
	LD d = p2l (c.c, a);
	// 需要的话返回 vector <point>
	/* if (sgn (d - R) >= 0) return {}; */
	LD x = sqrt (sqr(c.r) - sqr(d)); // sqrt(max(0., ...))
	return {
		proj_to_line (c.c, a) + (a.s - a.t).unit() * x,
		proj_to_line (c.c, a) - (a.s - a.t).unit() * x }; }
LD circle_inter_area (circle a, circle b) { // 圆面积交
	LD d = dis (a.c, b.c);
	if (sgn (d - (a.r + b.r)) >= 0) return 0;
	if (sgn (d - abs(a.r - b.r)) <= 0) {
		LD r = min (a.r, b.r);
		return r * r * PI; }
	LD x = (d * d + a.r * a.r - b.r * b.r) / (2 * d),
		   t1 = acos (min (1., max (-1., x / a.r))),
		   t2 = acos (min (1., max (-1., (d - x) / b.r)));
	return sqr(a.r)*t1 + sqr(b.r)*t2 - d*a.r*sin(t1);}
vector <point> circle_inter (circle a, circle b) { // 圆交点
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
vector <point> tangent (cp a, circle b) {
	return circle_inter (make_circle (a, b.c), b); }
vector <line> extangent (circle a, circle b) {
	vector <line> ret; // 未考虑两圆内切的一条外切线
	if (sgn(dis(a.c, b.c)-abs(a.r - b.r))<=0) return ret;
	if (sgn(a.r - b.r) == 0) {
		point dir = b.c - a.c;
		dir = (dir * a.r / dir.len()).rot90();
		ret.push_back({a.c + dir, b.c + dir});
		ret.push_back({a.c - dir, b.c - dir});
	} else {
		point p = (b.c * a.r - a.c * b.r) / (a.r - b.r); 
		auto u = tangent(p, a), v = tangent(p, b);
		if (u.size() == 2 && v.size() == 2) {
			if (sgn(a.r-b.r) < 0)
				swap(u[0], u[1]), swap(v[0], v[1]);
			ret.push_back({u[0], v[0]});
			ret.push_back({u[1], v[1]}); } }
	return ret; }
vector <line> intangent(circle a, circle b) {
	vector <line> ret; // 未考虑两圆外切的一条内切线
	point p = (b.c * a.r + a.c * b.r) / (a.r + b.r); 
	vector u = tangent(p, a), v = tangent(p, b);
	if (u.size() == 2 && v.size() == 2) {
		ret.push_back({u[0], v[0]});
		ret.push_back({u[1], v[1]}); } return ret; }