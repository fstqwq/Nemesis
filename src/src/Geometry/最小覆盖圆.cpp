struct circle {
	point p; double r;
	circle () {}
	circle (point pp, double rr) {p = pp, r = rr;} };
bool in_circle(cp a, const circle &b) {
	return (b.p - a).len() <= b.r; }
circle make_circle(point u, point v) {
	point p = (u + v) / 2;
	return circle(p, (u - p).len()); }
double sq(double x) {return x * x;}
circle make_circle(point u, point v, point w) {
	double a = u.x - v.x, b = u.y - v.y,
		c = u.x - w.x, d = u.y - w.y,
		e = ((sq(u.x) - sq(v.x)) - (sq(v.y) - sq(u.y))) / 2,
		f = ((sq(u.x) - sq(w.x)) - (sq(w.y) - sq(u.y))) / 2;
	point p = {-(d * e - b * f) / (b * c - a * d),
			   -(a * f - c * e) / (b * c - a * d)};
	return circle(p, (u - p).len());
}
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
