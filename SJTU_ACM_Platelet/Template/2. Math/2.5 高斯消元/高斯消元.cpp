db a[maxn][maxn], x[maxn];
int main()
{
	int rank = 0;
	// the size of the matrix is m * (n + 1)
	// And it's an augmented matrix
	for (int i = 1, now = 1; i <= m && now <= n; ++now)
	{
		if (fabs(a[i][now]) < eps)
		{
			for (int j = i + 1; j <= m; ++j)
				if (fabs(a[j][now]) > fabs(a[i][now]))
				{
					for (int k = now; k <= n + 1; ++k)
						std::swap(a[i][k], a[j][k]);
				}
		}
		if (fabs(a[i][now]) < eps) continue;

		for (int j = i + 1; j <= m; ++j)
		{
			db temp = a[j][now] / a[i][now];
			for (int k = now; k <= n + 1; ++k)
				a[j][k] -= temp * a[i][k];
		}
		++i; ++rank;
	}

	if (rank == n)
	{
		x[n] = a[n][n + 1] / a[n][n];
		for (int i = n - 1; i; --i)
		{
			for (int j = i + 1; j <= n; ++j)
				a[i][n + 1] -= x[j] * a[i][j];
			x[i] = a[i][n + 1] / a[i][i];
		}
	}
	else puts("Infinite Solution!");
	return 0;
}
