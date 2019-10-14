#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>

#define R register
#define cmax(_a, _b) (_a < (_b) ? _a = (_b) : 0)
#define maxn 10010
struct Poi {
	double x, y, m;
}p[maxn];
double ans_x, ans_y, fans;
int n;
inline double rand01() {return rand() / 2147483647.0;}
inline double randp() {return (rand() & 1 ? 1 : -1) * rand01();}
inline double sqr(R double x) {return x * x;}
inline double f(R double x, R double y)
{
	R double maxx = 0;
	for (R int i = 1; i <= n; ++i)
		maxx += sqrt(sqr(x - p[i].x) + sqr(y - p[i].y)) * p[i].m;
	if (maxx < fans) {fans = maxx; ans_x = x; ans_y = y;}
	return maxx;
}
int main()
{
	srand(time(NULL) + clock());
	scanf("%d", &n);
	R double x = 0, y = 0, tot = 0;
	for (R int i = 1; i <= n; ++i)
		scanf("%lf%lf%lf", &p[i].x, &p[i].y, &p[i].m), x += p[i].x * p[i].m, y += p[i].y * p[i].m, tot += p[i].m;
	fans = 1e30; x /= tot; y /= tot;
	R double fnow = f(x, y);
	for (R double T = 1e4; T > 1e-4; T *= 0.997)
	{
		R double nx = x + randp() * T, ny = y + randp() * T, fnext = f(nx, ny);
		R double delta = fnext - fnow;
		if (delta < 1e-9 || exp(-delta / T) > rand01())
		{
			x = nx; y = ny; fnow = fnext;
		}
	}
	printf("%.3lf %.3lf\n", ans_x, ans_y);
	return 0;
}
