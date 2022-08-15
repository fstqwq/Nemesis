int a[maxn], f[20][maxn], n;
int Log[maxn];
 
void build()
{
	for (int i = 1; i <= n; ++i) f[0][i] = a[i];
 
	int lim = Log[n];
	for (int j = 1; j <= lim; ++j)
	{
		int *fj = f[j], *fj1 = f[j - 1];
		for (int i = 1; i <= n - (1 << j) + 1; ++i)
			fj[i] = dmax(fj1[i], fj1[i + (1 << (j - 1))]);
	}
}
int Query(int l, int r)
{
	int k = Log[r - l + 1];
	return dmax(f[k][l], f[k][r - (1 << k) + 1]);
}
int main()
{
	scanf("%d", &n);
	Log[0] = -1;
	for (int i = 1; i <= n; ++i)
	{
		scanf("%d", &a[i]);
		Log[i] = Log[i >> 1] + 1;
	}
	build();
	int q;
	scanf("%d", &q);
	for (; q; --q)
	{
		int l, r; scanf("%d%d", &l, &r);
		printf("%d\n", Query(l, r) );
	}
}
