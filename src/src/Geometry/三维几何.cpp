/* 右手系逆时针绕轴旋转, $(x, y, z)  A = (x_\text{new}, y_\text{new}, z_\text{new})$
new[i] += old[j] * A[j][i] */
void calc(p3 n, LD cosw) {
	LD sinw = sqrt(1 - cosw * cosw);
	n = n.unit();
	for (int i = 0; i < 3; i++) {
		int j = (i + 1) % 3, k = (j + 1) % 3;
		LD x = n[i], y = n[j], z = n[k];
		A[i][i] = (y * y + z * z) * cosw + x * x;
		A[i][j] = x * y * (1 - cosw) + z * sinw;
		A[i][k] = x * z * (1 - cosw) - y * sinw; } }
p3 cross (p3 a, p3 b) { return p3(
 a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x);}
LD mix(p3 a, p3 b, p3 c) { return dot(cross(a, b), c); }
struct l3 { p3 s, t; };
struct plane { // nor 为单位法向量, 离原点距离 m
	p3 nor; LD m;
	plane(p3 r, p3 a) : nor(r.unit()), m(dot(nor, a)) {} };
// 除法注意除零； 点到直线投影: 与二维一致
p3 project_to_plane(p3 a, plane b) { // 点到平面投影
	return a + b.nor * (b.m - dot(a, b.nor)); }
pair<p3, p3> l3_closest(l3 x, l3 y) { // 两直线最近点
	LD a = dot(x.t - x.s, x.t - x.s);
	LD b = dot(x.t - x.s, y.t - y.s);
	LD e = dot(y.t - y.s, y.t - y.s);
	LD d = a*e - b*b; p3 r = x.s - y.s;
	LD c = dot(x.t - x.s, r), f = dot(y.t - y.s, r);
	LD s = (b*f - c*e) / d, t = (a*f - c*b) / d;
	return {x.s + (x.t - x.s)*s, y.s + (y.t - y.s)*t}; }
p3 intersect(plane a, l3 b) { // 直线与平面交点
	LD t = dot(a.nor, a.nor*a.m - b.s)/dot(a.nor, b.t - b.s);
	return b.s + (b.t - b.s) * t; }
// 平面与平面求交线
l3 intersect(plane a, plane b) {
	p3 d = cross(a.nor, b.nor), d2 = cross(b.nor, d);
	LD t = dot(d2, a.nor);
	p3 s = d2 * (a.m - dot(b.nor*b.m, a.nor))/t + b.nor*b.m;
	return {s, s + d}; }
// 三个平面求交点
p3 intersect(plane a, plane b, plane c) {
return intersect(a, intersect(b, c));
p3 c1 (a.nor.x, b.nor.x, c.nor.x);
p3 c2 (a.nor.y, b.nor.y, c.nor.y);
p3 c3 (a.nor.z, b.nor.z, c.nor.z);
p3 c4 (a.m, b.m, c.m);
return 1 / mix(c1, c2, c3) * p3(mix(c4, c2, c3), mix(c1, c4, c3), mix(c1, c2, c4)); }
