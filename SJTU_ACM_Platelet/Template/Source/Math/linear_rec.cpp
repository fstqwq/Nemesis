typedef vector<int> poly;
//{1, 3} {2, 1} an = 2an-1 + an-2, calc(3) = 7
struct LinearRec{
	int n, LOG;
	poly first, trans;
	vector<poly> bin;
	poly add(poly &a, poly &b)
	{
		poly res(n * 2 + 1, 0);
		for(int i = 0; i <= n; i++)
			for(int j = 0; j <= n; j++)
				(res[i + j] += 1ll * a[i] * b[j] % mo) %= mo;
		for(int i = 2 * n; i > n; i--)
		{
			for(int j = 0; j < n; j++)
				(res[i - 1 - j] += 1ll * res[i] * trans[j] % mo) %= mo;
			res[i] = 0;
		}
		res.erase(res.begin() + n + 1, res.end());
		return res;
	}
	LinearRec(poly &first, poly &trans, int LOG): LOG(LOG), first(first), trans(trans)
	{
		n = first.size();
		poly a(n + 1, 0);
		a[1] = 1;
		bin.push_back(a);
		for(int i = 1; i < LOG; i++)
			bin.push_back(add(bin[i - 1], bin[i - 1]));
	}
	int calc(long long k)
	{
		poly a(n + 1, 0);
		a[0] = 1;
		for(int i = 0; i < LOG; i++)
			if((k >> i) & 1)a = add(a, bin[i]);
		int ret = 0;
		for(int i = 0; i < n; i++)
			if((ret += 1ll * a[i + 1] * first[i] % mo) >= mo)ret -= mo;
		return ret;
	}
};
