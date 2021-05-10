bool point_on_segment(const point &a,const line &b){
	return sgn (det (a - b.s, b.t - b.s)) == 0 && sgn (dot (b.s - a, b.t - a)) <= 0; }
bool two_side(const point &a,const point &b,const line &c) {
	return sgn (det (a - c.s, c.t - c.s)) * sgn (det (b - c.s, c.t - c.s)) < 0; }
bool intersect_judgment(const line &a,const line &b) {
	if (point_on_segment (b.s, a) || point_on_segment (b.t, a)) return true;
	if (point_on_segment (a.s, b) || point_on_segment (a.t, b)) return true;
	return two_side (a.s, a.t, b) && two_side (b.s, b.t, a); }
point line_intersect(const line &a, const line &b) {
	double s1 = det (a.t - a.s, b.s - a.s);
	double s2 = det (a.t - a.s, b.t - a.s);
	return (b.s * s2 - b.t * s1) / (s2 - s1); }
double point_to_line (const point &a, const line &b) {
	return fabs (det (b.t-b.s, a-b.s)) / dis (b.s, b.t); }
point project_to_line (const point &a, const line &b) {
	return b.s + (b.t - b.s) * (dot (a - b.s, b.t - b.s) / (b.t - b.s).norm2 ()); }
double point_to_segment (const point &a, const line &b) {
	if (sgn (dot (b.s - a, b.t - b.s)) * sgn (dot (b.t - a, b.t - b.s)) <= 0)
		return fabs (det (b.t - b.s, a - b.s)) / dis (b.s, b.t);
	return std::min (dis (a, b.s), dis (a, b.t)); }
bool in_polygon (const point &p, const std::vector <point> & po) {
	int n = (int) po.size (); int counter = 0;
	for (int i = 0; i < n; ++i) {
		point a = po[i], b = po[(i + 1) % n];
		if (point_on_segment (p, line (a, b))) return true;
		int x = sgn (det (p - a, b - a)), y = sgn (a.y - p.y), z = sgn (b.y - p.y);
		if (x > 0 && y <= 0 && z > 0) ++counter;
		if (x < 0 && z <= 0 && y > 0) --counter; }
	return counter != 0; }
std::vector <point> line_circle_intersect (const line &a, const circle &b) {
	if (cmp (point_to_line (b.c, a), b.r) > 0) return std::vector <point> ();
	double x = sqrt (sqr (b.r) - sqr (point_to_line (b.c, a)));
	return std::vector <point> ({project_to_line (b.c, a) + (a.s - a.t).unit () * x, project_to_line (b.c, a) - (a.s - a.t).unit () * x}); }
double circle_intersect_area (const circle &a, const circle &b) {
	double d = dis (a.c, b.c);
	if (sgn (d - (a.r + b.r)) >= 0) return 0;
	if (sgn (d - abs(a.r - b.r)) <= 0) {
		double r = std::min (a.r, b.r);
		return r * r * PI; }
	double x = (d * d + a.r * a.r - b.r * b.r) / (2 * d),
		   t1 = acos (min (1., max (-1., x / a.r))),
		   t2 = acos (min (1., max (-1., (d - x) / b.r)));
	return a.r * a.r * t1 + b.r * b.r * t2 - d * a.r * sin (t1); }
std::vector <point> circle_intersect (const circle &a, const circle &b) {
	if (a.c == b.c || cmp (dis (a.c, b.c), a.r + b.r) > 0 || cmp (dis (a.c, b.c), std::abs (a.r - b.r)) < 0)
		return std::vector <point> ();
	point r = (b.c - a.c).unit ();
	double d = dis (a.c, b.c);
	double x = ((sqr (a.r) - sqr (b.r)) / d + d) / 2;
	double h = sqrt (sqr (a.r) - sqr (x));
	if (sgn (h) == 0) return std::vector <point> ({a.c + r * x});
	return std::vector <point> ({a.c + r * x + r.rot90 () * h, a.c + r * x - r.rot90 () * h}); }
// 返回按照顺时针方向
std::vector <point> tangent (const point &a, const circle &b) {
	circle p = make_circle (a, b.c);
	return circle_intersect (p, b); }
std::vector <line> extangent (const circle &a, const circle &b) {
	std::vector <line> ret;
	if (cmp (dis (a.c, b.c), std::abs (a.r - b.r)) <= 0) return ret;
	if (sgn (a.r - b.r) == 0) {
		point dir = b.c - a.c;
		dir = (dir * a.r / dir.norm ()).rot90 ();
		ret.push_back (line (a.c + dir, b.c + dir));
		ret.push_back (line (a.c - dir, b.c - dir));
	} else {
		point p = (b.c * a.r - a.c * b.r) / (a.r - b.r); 
		std::vector pp = tangent (p, a), qq = tangent (p, b);
		if (pp.size () == 2 && qq.size () == 2) {
			if (cmp (a.r, b.r) < 0) std::swap (pp[0], pp[1]), std::swap (qq[0], qq[1]);
			ret.push_back(line (pp[0], qq[0]));
			ret.push_back(line (pp[1], qq[1])); } }
	return ret; }
std::vector <line> intangent (const circle &a, const circle &b) {
	point p = (b.c * a.r + a.c * b.r) / (a.r + b.r); 
	std::vector pp = tangent (p, a), qq = tangent (p, b);
	if (pp.size () == 2 && qq.size () == 2) {
		ret.push_back (line (pp[0], qq[0]));
		ret.push_back (line (pp[1], qq[1])); }
	return ret; }