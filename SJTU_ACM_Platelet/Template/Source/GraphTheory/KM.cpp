long long KM(int n, long long w[N][N])
{
	long long ans = 0;
	int x, py, p;
	long long d;
	for(int i = 1; i <= n; i++)
		lx[i] = ly[i] = 0, lk[i] = -1;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			lx[i] = max(lx[i], w[i][j]);
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= n; j++)
			slk[j] = inf, vy[j] = 0;
		for(lk[py = 0] = i; lk[py]; py = p)
		{
			vy[py] = 1; d = inf; x = lk[py];
			for(int y = 1; y <= n; y++)
				if(!vy[y])
				{
					if(lx[x] + ly[y] - w[x][y] < slk[y])
						slk[y] = lx[x] + ly[y] - w[x][y], pre[y] = py;
					if(slk[y] < d)d = slk[y], p = y;
				}
			for(int y = 0; y <= n; y++)
				if(vy[y])lx[lk[y]] -= d, ly[y] += d;
				else slk[y] -= d;
		}
		for(; py; py = pre[py])lk[py] = lk[pre[py]];
	}
	for(int i = 1; i <= n; i++)
		ans += lx[i] + ly[i];
	return ans;
}
