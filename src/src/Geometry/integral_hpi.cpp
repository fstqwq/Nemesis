struct line : point {
	LD z; // ax + by + c >= 0
	line () {}
	line (LD a, LD b, LD c): point(a, b), z(c) {}
	line (cp a, cp b): point((b-a).rot90()), z(det(a, b)){}
	LD operator () (cp a) const{return dot(a, *this) + z;}};
point line_inter (cl u, cl v) {
return point(det({u.z, u.y}, {v.z, v.y}),
             det({u.x, u.z}, {v.x, v.z}) ) / -det(u, v); }
LD dis (cl l, cp x = {0, 0}) { return l(x) / l.len(); }
bool is_para(cl x, cl y) { return !sgn(det(x, y)); } 
LD det(cl a, cl b, cl c) {
	return det(a,b)*c.z + det(b,c)*a.z + det(c,a)*b.z;}
int check(cl a, cl b, cl c) { // sgn left(a, inter(b, c))
	return sgn(det(b, c, a)) * sgn(det(b, c)); }
bool turn_left(cl a, cl b, cl c){return check(a, b, c) >0;}
bool cmp (cl a, cl b) {
if (is_para(a, b) && dot(a, b) > 0) return dis(a) < dis(b);
return half(a) == half(b) ? sgn(det(a,b))>0 : half(b)>0;}
// 用以上函数替换 HPI 函数，需要 half(point)
line perp(cl l) { return {l.y, -l.x, 0}; } // 垂直
line para(cl l, cp o) { // 过一点平行
    return {l.x, l.y, l.z - l(o)}; }
point proj(cp x, cl l) {return x - l * (l(x)/l.len2());}
point refl(cp x, cl l) {return x - l * (l(x)/l.len2())*2;}
bool is_perp(cl x, cl y) { return !sgn(dot(x, y)); }
LD area(cl a, cl b, cl c) { // 0 when error
	LD d = det(a, b, c);
	return d * d / (det(a, b) * det(b, c) * det(c, a)); }
vector <line> cut (const vector <line>& o, line l){
	vector <line> ret; int n = (int) o.size();
	for (int i = 0; i < n; i++) {
		cl u = o[i], v = o[(i+1) % n], w = o[(i + 2) % n];
		int va = check(l, u, v), vb = check(l, v, w);
		if (va > 0 || vb > 0 || (va == 0 && vb == 0))
			ret.push_back(v);
		if (va >= 0 && vb < 0) ret.push_back(l);
	} return ret; }
