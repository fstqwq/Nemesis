bool point_on_segment(cp a,cl b){
	return sgn (det (a - b.s, b.t - b.s)) == 0
		&& sgn (dot (b.s - a, b.t - a)) <= 0; }
bool two_side(cp a,cp b,cl c) {
	return sgn (det (a - c.s, c.t - c.s))
		* sgn (det (b - c.s, c.t - c.s)) < 0; }
bool intersect_judgment(cl a,cl b) {
	if (point_on_segment (b.s, a)
	|| point_on_segment (b.t, a)) return true;
	if (point_on_segment (a.s, b)
	|| point_on_segment (a.t, b)) return true;
	return two_side (a.s, a.t, b)
		&& two_side (b.s, b.t, a); }
point line_intersect(cl a, cl b) {
	double s1 = det (a.t - a.s, b.s - a.s);
	double s2 = det (a.t - a.s, b.t - a.s);
	return (b.s * s2 - b.t * s1) / (s2 - s1); }
double point_to_line (cp a, cl b) {
	return abs (det (b.t-b.s, a-b.s)) / dis (b.s, b.t); }
point project_to_line (cp a, cl b) {
	return b.s + (b.t - b.s)
	* (dot (a - b.s, b.t - b.s) / (b.t - b.s).norm2 ()); }
double point_to_segment (cp a, cl b) {
	if (sgn (dot (b.s - a, b.t - b.s))
	* sgn (dot (b.t - a, b.t - b.s)) <= 0)
		return abs (det (b.t - b.s, a - b.s))
			/ dis (b.s, b.t);
	return min (dis (a, b.s), dis (a, b.t)); }
bool in_polygon (cp p, const vector <point> & po) {
	int n = (int) po.size (); int counter = 0;
	for (int i = 0; i < n; ++i) {
		point a = po[i], b = po[(i + 1) % n];
		if (point_on_segment (p, line (a, b))) return true;
		int x = sgn (det (p - a, b - a)),
			y = sgn (a.y - p.y), z = sgn (b.y - p.y);
		if (x > 0 && y <= 0 && z > 0) ++counter;
		if (x < 0 && z <= 0 && y > 0) --counter; }
	return counter != 0; }
vector <point> line_circle_intersect (cl a, cc b) {
	if (sgn (point_to_line (b.c, a) - b.r) > 0)
		return vector <point> ();
	double x = sqrt(sq(b.r)-sq(point_to_line (b.c, a)));
	return vector <point>
	({project_to_line (b.c, a) + (a.s - a.t).unit () * x,
	project_to_line (b.c, a) - (a.s - a.t).unit () * x});}
double circle_intersect_area (cc a, cc b) {
	double d = dis (a.c, b.c);
	if (sgn (d - (a.r + b.r)) >= 0) return 0;
	if (sgn (d - abs(a.r - b.r)) <= 0) {
		double r = min (a.r, b.r);
		return r * r * PI; }
	double x = (d * d + a.r * a.r - b.r * b.r) / (2 * d),
		   t1 = acos (min (1., max (-1., x / a.r))),
		   t2 = acos (min (1., max (-1., (d - x) / b.r)));
	return sq(a.r)*t1 + sq(b.r)*t2 - d*a.r*sin(t1);}
vector <point> circle_intersect (cc a, cc b) {
	if (a.c == b.c
		|| sgn (dis (a.c, b.c) - a.r - b.r) > 0
		|| sgn (dis (a.c, b.c) - abs (a.r - b.r)) < 0)
		return {};
	point r = (b.c - a.c).unit ();
	double d = dis (a.c, b.c);
	double x = ((sqr (a.r) - sqr (b.r)) / d + d) / 2;
	double h = sqrt (sqr (a.r) - sqr (x));
	if (sgn (h) == 0) return {a.c + r * x};
	return {a.c + r * x + r.rot90 () * h,
			  a.c + r * x - r.rot90 () * h}; }
// 返回按照顺时针方向
vector <point> tangent (cp a, cc b) {
	circle p = make_circle (a, b.c);
	return circle_intersect (p, b); }
vector <line> extangent (cc a, cc b) {
	vector <line> ret;
	if (sgn(dis (a.c, b.c)-abs (a.r - b.r))<=0) return ret;
	if (sgn (a.r - b.r) == 0) {
		point dir = b.c - a.c;
		dir = (dir * a.r / dir.norm ()).rot90 ();
		ret.push_back (line (a.c + dir, b.c + dir));
		ret.push_back (line (a.c - dir, b.c - dir));
	} else {
		point p = (b.c * a.r - a.c * b.r) / (a.r - b.r); 
		vector pp = tangent (p, a), qq = tangent (p, b);
		if (pp.size () == 2 && qq.size () == 2) {
			if (sgn (a.r-b.r) < 0)
				swap (pp[0], pp[1]), swap (qq[0], qq[1]);
			ret.push_back(line (pp[0], qq[0]));
			ret.push_back(line (pp[1], qq[1])); } }
	return ret; }
vector <line> intangent (cc a, cc b) {
	point p = (b.c * a.r + a.c * b.r) / (a.r + b.r); 
	vector pp = tangent (p, a), qq = tangent (p, b);
	if (pp.size () == 2 && qq.size () == 2) {
		ret.push_back (line (pp[0], qq[0]));
		ret.push_back (line (pp[1], qq[1])); }
	return ret; }
