double sector_area (cp a, cp b, double r) {
	double c = (2.0 * r * r - (a - b).norm2 ()) / (2.0 * r * r);
	double al = acos (c);
	return r * r * al / 2.0; }
double area(cp a,cp b, double r) {
	double dA = dot (a, a), dB = dot (b, b), dC = point_to_segment (point (), line (a, b)), ans = 0.0;
	if (sgn (dA - r * r) <= 0 && sgn (dB - r * r) <= 0) return det (a, b) / 2.0;
	point tA = a.unit () * r;
	point tB = b.unit () * r;
	if (sgn (dC - r) >= 0) return sector_area (tA, tB, r);
	pair <point, point> ret = line_circle_intersect (line (a, b), circle (point (), r));
	if (sgn (dA - r * r) > 0 && sgn (dB - r * r) > 0) {
		ans += sector_area (tA, ret.first, r);
		ans += det (ret.first, ret.second) / 2.0;
		ans += sector_area (ret.second, tB, r);
		return ans; }
	if (sgn (dA - r * r) > 0)
		return det (ret.first, b) / 2.0 + sector_area (tA, ret.first, r);
	else
		return det (a, ret.second) / 2.0 + sector_area (ret.second, tB, r); }
double solve(const vector<point> &p, cc c) {//多边形必须逆时针
	double ret = 0.0;
	for (int i = 0; i < (int) p.size (); ++i) {
		int s = sgn (det (p[i] - c.c, p[ (i + 1) % p.size ()] - c.c));
		if (s > 0)
			ret += area (p[i] - c.c, p[ (i + 1) % p.size ()] - c.c, c.r);
		else
			ret -= area (p[ (i + 1) % p.size ()] - c.c, p[i] - c.c, c.r); }
	return fabs (ret); }
