typedef double D;
#define cp const p3 & 
struct p3 {
	D x, y, z;
	void read() { ... }
	p3 () {x = y = z = 0;}
	p3 (D xx, D yy, D zz) {x = xx; y = yy; z = zz;}
	p3 operator + (cp a) {return {x + a.x, y + a.y, z + a.z};}
	p3 operator - (cp a) {return {x - a.x, y - a.y, z - a.z};}
	p3 operator * (D a) {return {x * a, y * a, z * a};}
	p3 operator / (D a) {return {x / a, y / a, z / a};}
	D &operator [] (int a) {return a == 0 ? x : (a == 1 ? y : z);}
	D len2() { return x * x + y * y + z * z; }
	void normalize() {
		D l = sqrt(len2()); 
		x /= l; y /= l; z /= l; }
};
const D pi = acos(-1);
D A[3][3];
void calc(p3 n, D cosw) {
	D sinw = sqrt(1 - cosw * cosw);
	n.normalize();
	for (int i = 0; i < 3; i++) {
		int j = (i + 1) % 3, k = (j + 1) % 3;
		D x = n[i], y = n[j], z = n[k];
		A[i][i] = (y * y + z * z) * cosw + x * x;
		A[i][j] = x * y * (1 - cosw) + z * sinw;
		A[i][k] = x * z * (1 - cosw) - y * sinw;
	} }
p3 turn(p3 x) {
	p3 y;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			y[i] += x[j] * A[j][i];
	return y; }
p3 cross(cp a, cp b) { return p3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x); }
D dot(cp a, cp b) {
	D ret = 0;
	for (int i = 0; i < 3; i++) 
		ret += a[i] * b[i];
	return ret; }
const int N = 5e4 + 5;
const D eps = 1e-5;
int sgn(D x) { return (x > eps ? 1 : (x < -eps ? -1 : 0)); }
D det(cp a, cp b) { return a.x * b.y - b.x * a.y; }
p3 base;
bool cmp(cp a, cp b) {
	int d = sgn(det(a - base, b - base)); 
	if (d) return d > 0;
	else return (a - base).len2() < (b - base).len2();
}
bool turn_left(cp a, cp b, cp c) { return sgn(det(b - a, c - a)) >= 0; }
vector <p3> convex_hull (vector <p3> a) {
	int n = (int) a.size(), cnt = 0;
	base = a[0];
	for (int i = 1; i < n; i++) {
		int s = sgn(a[i].x - base.x);
		if (s == -1 || (s == 0 && a[i].y < base.y))
			base = a[i];
	}
	sort(a.begin(), a.end(), cmp);
	vector <p3> ret;
	for (int i = 0; i < n; i++) {
		while (cnt > 1 && turn_left(ret[cnt - 2], a[i], ret[cnt - 1])) {
			--cnt; ret.pop_back();
		}
		ret.push_back(a[i]); ++cnt;
	}
	int fixed = cnt;
	for (int i = n - 2; i >= 0; i--) {
		while (cnt > fixed && turn_left(ret[cnt - 2], a[i], ret[cnt - 1])) {
			--cnt; ret.pop_back();
		}
		ret.push_back(a[i]); ++cnt;
	}
	ret.pop_back();
	return ret; }
int n, m;
p3 ap[N], bp[N];
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) ap[i].read();
	ap[0].read();
	scanf("%d", &m);
	for (int i = 1; i <= m; i++) bp[i].read();
	bp[0].read();
	p3 from = ap[0] - bp[0], to = {0, 0, 1};
	if (from.len2() < eps) return puts("NO"), 0;
	from.normalize();
	p3 c = cross(from, to);
	if (abs(c.len2()) < eps) ;
	else {
		D cosw = dot(from, to);
		calc(c, cosw);
		for (int i = 1; i <= n; i++) {
			ap[i] = turn(ap[i]);
			ap[i].z = 0;
		}
		for (int i = 1; i <= m; i++) bp[i] = turn(bp[i]), bp[i].z = 0;
	}
	vector <p3> a[2];	
	for (int i = 1; i <= n; i++) a[0].push_back(ap[i]);
	for (int i = 1; i <= m; i++) a[1].push_back(p3()-bp[i]);
	a[0] = convex_hull (a[0]);
	a[1] = convex_hull (a[1]);

	vector <p3> mnk;
	{
		a[0].push_back(a[0].front()); a[1].push_back(a[1].front());
		int i[2] = {0, 0};
		int len[2] = {(int)a[0].size() - 1, (int)a[1].size() - 1};
		mnk.push_back(a[0][0] + a[1][0]);
		do { 
			int d = sgn(det(a[1][i[1] + 1] - a[1][i[1]],
						a[0][i[0] + 1] - a[0][i[0]])) >= 0;
			mnk.push_back(a[d][i[d] + 1] - a[d][i[d]] + mnk.back());
			i[d] = (i[d] + 1) % len[d];
		} while(i[0] || i[1]);
	}
	//mnk = convex_hull(mnk);
	p3 p; // 0
	for (int i = 0; i < (int)mnk.size(); i++) {
		p3 u = mnk[i], v = mnk[(i + 1) % int(mnk.size())];
		if (det(p - u, v - u) > eps)
			return puts("NO"), 0;
	}
	puts("YES"); }
