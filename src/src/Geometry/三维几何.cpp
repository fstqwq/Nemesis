/* 大拇指指向x轴正方向时, 4指弯曲由y轴正方向指向z轴正方向
 大拇指沿着原点到点(x, y, z)的向量,4指弯曲方向旋转w度 */
/* (x, y, z) * A = (x_new, y_new, z_new), 行向量右乘转移矩阵 */
void calc(D x, D y, D z, D w) { // 三维绕轴旋转
	w = w * pi / 180;
	memset(a, 0, sizeof(a));
	s1 = x * x + y * y + z * z;
	a[0][0] = ((y*y+z*z)*cos(w)+x*x)/s1; a[0][1] = x*y*(1-cos(w))/s1+z*sin(w)/sqrt(s1); a[0][2] = x*z*(1-cos(w))/s1-y*sin(w)/sqrt(s1);
	a[1][0] = x*y*(1-cos(w))/s1-z*sin(w)/sqrt(s1); a[1][1] = ((x*x+z*z)*cos(w)+y*y)/s1; a[1][2] = y*z*(1-cos(w))/s1+x*sin(w)/sqrt(s1);
	a[2][0] = x*z*(1-cos(w))/s1+y*sin(w)/sqrt(s1); a[2][1] = y*z*(1-cos(w))/s1-x*sin(w)/sqrt(s1); a[2][2] = ((x*x+y*y)*cos(w)+z*z)/s1;
}
point3D cross (const point3D & a, const point3D & b) {
	return point3D(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x); }
double mix(point3D a, point3D b, point3D c) {
	return dot(cross(a, b), c); }
struct Line { point3D s, t; };
struct Plane { // nor 为单位法向量, 离原点距离 m
	point3D nor; double m;
	Plane(point3D r, point3D a) : nor(r){
		nor = 1 / r.len() * r;
		m = dot(nor, a); } };
// 以下函数注意除以0的情况
// 点到平面投影
point3D project_to_plane(point3D a, Plane b) {
return a + (b.m - dot(a, b.nor)) * b.nor; }
// 点到直线投影
point3D project_to_line(point3D a, Line b) {
return b.s + dot(a - b.s, b.t - b.s) / dot(b.t - b.s, b.t - b.s) * (b.t - b.s); }
// 直线与直线最近点
pair<point3D, point3D> closest_two_lines(Line x, Line y) {
double a = dot(x.t - x.s, x.t - x.s);
double b = dot(x.t - x.s, y.t - y.s);
double e = dot(y.t - y.s, y.t - y.s);
double d = a*e - b*b; point3D r = x.s - y.s;
double c = dot(x.t - x.s, r), f = dot(y.t - y.s, r);
double s = (b*f - c*e) / d, t = (a*f - c*b) / d;
return {x.s + s*(x.t - x.s), y.s + t*(y.t - y.s)}; }
// 直线与平面交点
point3D intersect(Plane a, Line b) {
double t = dot(a.nor, a.m * a.nor - b.s) / dot(a.nor, b.t - b.s);
return b.s + t * (b.t - b.s); }
// 平面与平面求交线
Line intersect(Plane a, Plane b) {
point3D d=cross(a.nor,b.nor), d2=cross(b.nor,d);
double t = dot(d2, a.nor);
point3D s = 1 / t * (a.m - dot(b.m * b.nor, a.nor)) * d2 + b.m * b.nor;
return (Line) {s, s + d}; }
// 三个平面求交点
point3D intersect(Plane a, Plane b, Plane c) {
return intersect(a, intersect(b, c));
point3D c1 (a.nor.x, b.nor.x, c.nor.x);
point3D c2 (a.nor.y, b.nor.y, c.nor.y);
point3D c3 (a.nor.z, b.nor.z, c.nor.z);
point3D c4 (a.m, b.m, c.m);
return 1 / mix(c1, c2, c3) * point3D(mix(c4, c2, c3), mix(c1, c4, c3), mix(c1, c2, c4)); }
