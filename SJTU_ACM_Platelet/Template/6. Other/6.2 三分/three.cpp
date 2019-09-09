#define maxn 200010
#define inf 1e9
int a[maxn], n;
inline double check(R double x)
{
	R double tmp, tmp1 = 0, tmp2 = 0, maxx = -inf, minn = -inf;
	for (R int i = 1; i <= n; ++i)
	{
		tmp = (double) a[i] - x;
 
		tmp1 += tmp;
		cmax(maxx, tmp1);
		tmp1 < 0 ? tmp1 = 0 : 0;
 
		tmp2 -= tmp;
		cmax(minn, tmp2);
		tmp2 < 0 ? tmp2 = 0 : 0;
	}
	return dmax(maxx, minn);
}
int main()
{
	n = F();
	for (R int i = 1; i <= n; ++i) a[i] = F();
	R double l = -1e4, r = 1e4;
	for (R int i = 1; i <= 100; ++i)
	{
		R double ll = (l + r) * 0.5;
		R double rr = (ll + r) * 0.5;
		if (check(ll) < check(rr)) r = rr;
		else l = ll;
	}
	printf("%.6lf\n", check((l + r) * 0.5) );
	return 0;
}
