struct circle {
	point p; double r;
	circle () {}
	circle (point pp, double rr) {p = pp, r = rr;} };
bool in_circle(cp a, const circle &b) {
	return (b.p - a).len() <= b.r; }
circle make_circle(point u, point v) {
	point p = (u + v) / 2;
	return circle(p, (u - p).len()); }
circle make_circle(cp a, cp b, cp c) {
	point p = b - a, q = c - a,
		s(dot(p, p) / 2, dot(q, q) / 2);
	double d = det(p, q);
	p = point( det(s, point(p.y, q.y)),
		det(point(p.x, q.x), s) ) / d;
	return circle(a + p, p.len());
} // make_circle : 过参数点的最小圆
circle min_circle (vector <point> p) {
	circle ret;
	random_shuffle (p.begin (), p.end ());
	for (int i = 0; i < (int) p.size (); ++i)
		if (!in_circle (p[i], ret)) {
			ret = circle (p[i], 0);
			for (int j = 0; j < i; ++j) if (!in_circle (p[j], ret)) {
				ret = make_circle (p[j], p[i]);
				for (int k = 0; k < j; ++k)
					if (!in_circle (p[k], ret))
						ret = make_circle(p[i],p[j],p[k]);
		} } return ret; }
