//
//  Title : 随机增量法求最小覆盖圆
//  Date : 29.03.2016
//  Test : YZOJ-1834 BZOJ-3564,2823,1336,1337
//  Complexity : O(n)
//  
/*
	对于求最小覆盖圆等问题——
	解决办法：随机增量法
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

#ifdef WIN32
	#define LL "%I64d"
#else
	#define LL "%lld"
#endif

#ifdef CT
	#define debug(...) printf(__VA_ARGS__)
	#define setfile() 
#else
	#define debug(...)
	#define filename ""
	#define setfile() freopen(filename".in", "r", stdin); freopen(filename".out", "w", stdout);
#endif

#define R register
#define getc() (S == T && (T = (S = B) + fread(B, 1, 1 << 15, stdin), S == T) ? EOF : *S++)
#define dmax(_a, _b) ((_a) > (_b) ? (_a) : (_b))
#define dmin(_a, _b) ((_a) < (_b) ? (_a) : (_b))
#define cmax(_a, _b) (_a < (_b) ? _a = (_b) : 0)
#define cmin(_a, _b) (_a > (_b) ? _a = (_b) : 0)
char B[1 << 15], *S = B, *T = B;
inline int FastIn()
{
	R char ch; R int cnt = 0; R bool minus = 0;
	while (ch = getc(), (ch < '0' || ch > '9') && ch != '-') ;
	ch == '-' ? minus = 1 : cnt = ch - '0';
	while (ch = getc(), ch >= '0' && ch <= '9') cnt = cnt * 10 + ch - '0';
	return minus ? -cnt : cnt;
}
inline double FastIn2()
{
	R char ch = getc(); R double cnt = 0, ee = 1; R bool minus = 0, e = 0;
	while (ch != '-' && (ch < '0' || ch > '9')) ch = getc();
	if (ch == '-') minus = 1, ch = getc();
	while (ch >= '0' && ch <= '9') cnt = cnt * 10 + ch - '0' , ch = getc();
	if (ch == '.') e = 1, ee *= 0.1, ch = getc();
	while (ch >= '0' && ch <= '9' && e) cnt += (ch - '0') * ee, ee *= 0.1, ch = getc();
	return minus ? -cnt : cnt;
}
#define maxn 1000010
struct Point
{
	double x, y;
}p[maxn], o;
Point cir(Point a, Point b, Point c)
{
	R Point res;
	R double a1 = b.x - a.x, b1 = b.y - a.y, c1 = (a1 * a1 + b1 * b1);
	R double a2 = c.x - a.x, b2 = c.y - a.y, c2 = (a2 * a2 + b2 * b2);
	R double d = (a2 * b1 - a1 * b2) * 2;
	res.x = a.x + (c2 * b1 - c1 * b2) / d;
	res.y = a.y + (c1 * a2 - c2 * a1) / d;
	return res;
} 
#define dist(_a, _b) (sqrt((_a.x - _b.x) * (_a.x - _b.x) + (_a.y - _b.y) * (_a.y - _b.y) ) )
int main()
{
//	setfile();
	R int n = FastIn();
	for (R int i = 1; i <= n; ++i)
		p[i] = (Point) {FastIn2(), FastIn2()};
	std::random_shuffle(p + 1, p + n + 1);
	o = p[1];
	R double r = 0;
	for (R int i = 2; i <= n; ++i)
		if (dist(p[i], o) > r)
		{
			o = p[i]; r = 0;
			for (R int j = 1; j < i; ++j)
				if (dist(p[j], o) > r)
				{
					o.x = (p[i].x + p[j].x) / 2;
					o.y = (p[i].y + p[j].y) / 2;
					r = dist(p[i], o);
					for (R int k = 1; k < j; ++k)
						if (dist(p[k], o) > r)
						{
							o = cir(p[i], p[j], p[k]);
							r = dist(p[i], o);
						}
				}
		}
	printf("%.6f\n%.6f %.6f", r, o.x, o.y);
	return 0;
}
