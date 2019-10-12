for (i = 0; i < n; i++)
	for (j = 0; j < (1 << n); j++)
		if (j >> i & 1) x[j] += x[j ^ (1 << i)]
