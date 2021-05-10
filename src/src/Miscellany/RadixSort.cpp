void SORT(int a[], int c[], int n, int l) {
	for (int i = 0; i < SZ; i++) b[i] = 0;
	for (int i = 1; i <= n; i++) b[(a[i] >> l) & (SZ - 1)]++;
	for (int i = 1; i < SZ; i++) b[i] += b[i - 1];
	for (int i = n; i; i--) c[b[(a[i] >> l) & (SZ - 1)]--] = a[i]; }
void Sort(int *a, int b){
	if (b < 23333) sort(a + 1, a + b + 1);
	else {
		SORT(a, c, b, 0);
		SORT(c, a, b, 14); } }
