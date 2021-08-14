/* 右手系逆时针绕轴旋转, $(x, y, z)  A = (x_\text{new}, y_\text{new}, z_\text{new})$
new[i] += old[j] * A[j][i] */
void calc(p3 n, double cosw) {
	double sinw = sqrt(1 - cosw * cosw);
	n.normalize();
	for (int i = 0; i < 3; i++) {
		int j = (i + 1) % 3, k = (j + 1) % 3;
		double x = n[i], y = n[j], z = n[k];
		A[i][i] = (y * y + z * z) * cosw + x * x;
		A[i][j] = x * y * (1 - cosw) + z * sinw;
		A[i][k] = x * z * (1 - cosw) - y * sinw; } }
p3 cross (const p3 & a, const p3 & b) {
	return p3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x); }
double mix(p3 a, p3 b, p3 c) {
	return dot(cross(a, b), c); }
struct Line { p3 s, t; };
struct Plane { // nor 为单位法向量, 离原点距离 m
	p3 nor; double m;
	Plane(p3 r, p3 a) : nor(r){
		nor = 1 / r.len() * r;
		m = dot(nor, a); } };
// 以下函数注意除以0的情况
// 点到平面投影
p3 project_to_plane(p3 a, Plane b) {
return a + (b.m - dot(a, b.nor)) * b.nor; }
// 点到直线投影
p3 project_to_line(p3 a, Line b) {
return b.s + dot(a - b.s, b.t - b.s) / dot(b.t - b.s, b.t - b.s) * (b.t - b.s); }
// 直线与直线最近点
pair<p3, p3> closest_two_lines(Line x, Line y) {
double a = dot(x.t - x.s, x.t - x.s);
double b = dot(x.t - x.s, y.t - y.s);
double e = dot(y.t - y.s, y.t - y.s);
double d = a*e - b*b; p3 r = x.s - y.s;
double c = dot(x.t - x.s, r), f = dot(y.t - y.s, r);
double s = (b*f - c*e) / d, t = (a*f - c*b) / d;
return {x.s + s*(x.t - x.s), y.s + t*(y.t - y.s)}; }
// 直线与平面交点
p3 intersect(Plane a, Line b) {
double t = dot(a.nor, a.m * a.nor - b.s) / dot(a.nor, b.t - b.s);
return b.s + t * (b.t - b.s); }
// 平面与平面求交线
Line intersect(Plane a, Plane b) {
p3 d=cross(a.nor,b.nor), d2=cross(b.nor,d);
double t = dot(d2, a.nor);
p3 s = 1 / t * (a.m - dot(b.m * b.nor, a.nor)) * d2 + b.m * b.nor;
return (Line) {s, s + d}; }
// 三个平面求交点
p3 intersect(Plane a, Plane b, Plane c) {
return intersect(a, intersect(b, c));
p3 c1 (a.nor.x, b.nor.x, c.nor.x);
p3 c2 (a.nor.y, b.nor.y, c.nor.y);
p3 c3 (a.nor.z, b.nor.z, c.nor.z);
p3 c4 (a.m, b.m, c.m);
return 1 / mix(c1, c2, c3) * p3(mix(c4, c2, c3), mix(c1, c4, c3), mix(c1, c2, c4)); }
