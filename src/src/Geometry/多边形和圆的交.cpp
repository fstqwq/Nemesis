LD angle (cp a, cp b) {
	return 2 * asin(dis(a.unit(), b.unit()) / 2); }
LD area(cp a, cp b, LD r) { // 2 * area
	LD da = dot(a, a);
	LD db = dot(b, b);
	LD rr = r * r;
	int sa = sgn(da - rr);
	int sb = sgn(db - rr);
	int sc = sgn(point_to_segment({0, 0}, {a, b}) - r);
	if (sa <= 0 && sb <= 0) return det(a, b);
	if (sc >= 0) return angle(a, b) * rr;
	auto [u, v] = line_circle_inter({a, b}, {{0, 0}, r});
	if (sa > 0 && sb > 0)
		return det(u, v) + rr * (angle(a, u) + angle(v, b));
	if (sa > 0)
		return det(u, b) + angle(a, u) * rr;
	return det(a, v) + angle(v, b) * rr; }
LD solve(vector<point> &p, cc c) {
	LD ret = 0;
	for (int i = 0; i < (int) p.size (); ++i) {
		auto u = p[i] - c.c;
		auto v = p[(i + 1) % p.size()] - c.c;
		int s = sgn(det(u, v));
		if (s > 0)      ret += area (u, v, c.r);
		else if (s < 0) ret -= area (v, u, c.r);
	} return abs (ret) / 2; } //ret在p逆时针时为正