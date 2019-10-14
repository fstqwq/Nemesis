typedef int Matrix[maxn * maxn][maxn * maxn];
typedef int Vector[maxn * maxn];
inline void mul(Matrix A, Matrix B)
{
	Matrix C; int *ci, *bk; int aik;
	for (int i = 1; i <= size; ++i) memset(C[i] + 1, 0, size << 2);
	for (int i = 1; i <= size; ++i)
	{
		ci = C[i];
		for (int k = 1; k <= size; ++k)
			if (aik = A[i][k])
			{
				bk = B[k];
				for (int j = 1; j <= size; ++j)
					ci[j] = (ci[j] + 1ll * aik * bk[j]) % mod;
			}
	}
	for (int i = 1; i <= size; ++i) memcpy(A[i] + 1, C[i] + 1, size << 2);
}
inline void mul(Vector A, Matrix B)
{
	Vector C; memset(C + 1, 0, size << 2);
	for (int i = 1; i <= size; ++i)
		for (int j = 1; j <= size; ++j)
			C[i] = (C[i] + 1ll * A[j] * B[j][i]) % mod;
	memcpy(A + 1, C + 1, size << 2);
}