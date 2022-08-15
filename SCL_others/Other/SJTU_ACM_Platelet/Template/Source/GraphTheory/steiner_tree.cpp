void Steiner_Tree()
{
	memset(f, 0x3f, sizeof(f));
	for(int i = 1; i <= n; i++)
		f[0][i] = 0;
	for(int i = 1; i <= p; i++)
		f[1 << (i - 1)][idx[i]] = 0;
	int S = 1 << p;
	for(int s = 1; s < S; s++)
	{
		for(int i = 1; i <= n; i++)
		{
			for(int k = (s - 1) & s; k; k = (k - 1) & s)
				f[s][i] = min(f[s][i], f[k][i] + f[s ^ k][i]);
		}
		SPFA(f[s]);
	}
	int ans = inf;
	for(int i = 1; i <= n; i++)
		ans = min(ans, f[S - 1][i]);
}
