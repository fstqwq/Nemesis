void fwt_or(int *a, int n, int tp) {
	for (int j = 0; (1 << j) < n; j++)
		for (int i = 0; i < n; i++) if (i >> j & 1) {
				if (tp > 0) a[i] += a[i ^ (1 << j)];
				else a[i] -= a[i ^ (1 << j)]; } }
// and自然就是or反过来
void fwt_and(int *a, int n, int tp) {
	for (int j = 0; (1 << j) < n; j++)
		for (int i = 0; i < n; i++) if (!(i >> j & 1)) {
				if (tp > 0) a[i] += a[i | (1 << j)];
				else a[i] -= a[i | (1 << j)]; } }
// xor同理