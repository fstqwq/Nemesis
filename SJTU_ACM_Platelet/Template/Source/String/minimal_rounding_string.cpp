int main()
{
	int i = 0, j = 1, k = 0;
	while (i < n && j < n && k < n)
	{
		int tmp = a[(i + k) % n] - a[(j + k) % n];
		if (!tmp) k++;
		else
		{
			if (tmp > 0) i += k + 1;
			else j += k + 1;
			if (i == j) ++j;
			k = 0;
		}
	}
	j = dmin(i, j);
	for (int i = j; i < n; ++i) printf("%d ", a[i]);
	for (int i = 0; i < j - 1; ++i) printf("%d ", a[i]);
	if (j > 0) printf("%d\n", a[j - 1]);
	return 0;
}
