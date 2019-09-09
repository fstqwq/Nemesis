#include <cmath>
#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <ctime>
 
#define maxn 1010
#define R register
#define cmin(_a, _b) (_a > (_b) ? _a = (_b) : 0)
#define cmax(_a, _b) (_a < (_b) ? _a = (_b) : 0)
int n;
typedef double db;
const db pi = acos(-1);
#define LF "lf"
struct Cir {
	db x, y, r;
}c[maxn];
struct Seg {
	db l, r;
	inline bool operator < (const Seg &that) const
	{
		return l < that.l || (l == that.l && r < that.r);
	}
}s[maxn];
inline db sqr(R db x) {return x * x;}
inline db len(R db x)
{
	R int scnt = 0;
	for (R int i = 1; i <= n; ++i)
		if (fabs(c[i].x - x) <= c[i].r)
		{
			R db t = sqrt(sqr(c[i].r) - sqr(c[i].x - x));
			s[++scnt] = (Seg) {c[i].y - t, c[i].y + t};
		}
	std::sort(s + 1, s + scnt + 1);
	R db ret = 0;
	R db l = 1e18, r = -1e18;
	for (R int i = 1; i <= scnt; ++i)
	{
		if (s[i].l > r)
		{
			if (l < r) ret += r - l;
			l = s[i].l; r = s[i].r;
		}
		else
			cmax(r, s[i].r);
	}
	if (l < r) ret += r - l;
	return ret;
}
inline db f(R db l, R db r, R db fl, R db fm, R db fr)
{
	return (r - l) * (fl + fr + fm * 4.0) / 6.0;
}
db ans(R db l, R db r, R db fl, R db fm, R db fr)
{
	R db mid = (l + r) * 0.5;
	R db mid1 = (l + mid) * 0.5, mid2 = (mid + r) * 0.5;
	R db fmid1 = len(mid1), fmid2 = len(mid2);
	R db ff = f(l, r, fl, fm, fr), flmid = f(l, mid, fl, fmid1, fm), fmidr = f(mid, r, fm, fmid2, fr);
	if (r - l < 1e-9 || fabs(ff - flmid - fmidr) < 1e-9) return ff;
	else return ans(l, mid, fl, fmid1, fm) + ans(mid, r, fm, fmid2, fr);
}
int main()
{
	srand(time(NULL));
	scanf("%d", &n);
	R db l = 1e18, r = -1e18, theta = rand(), co = cos(theta), si = sin(theta);
	for (R int i = 1; i <= n; ++i)
	{
		R db x, y;
		scanf("%"LF"%"LF"%"LF, &x, &y, &c[i].r);
		c[i].x = co * x - si * y;
		c[i].y = si * x + co * y;
		cmin(l, c[i].x - c[i].r);
		cmax(r, c[i].x + c[i].r);
	}
	R double mid = (l + r) * 0.5;
	printf("%.3"LF"\n", ans(l, r, len(l), len(mid), len(r)));
	return 0;
}
