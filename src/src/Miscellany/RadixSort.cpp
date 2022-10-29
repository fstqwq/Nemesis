const int SZ = 1 << 8; // almost always fit in L1 cache
void SORT(int a[], int c[], int n, int w) {
	for(int i=0; i<SZ; i++) b[i] = 0;
	for(int i=1; i<=n; i++) b[(a[i]>>w) & (SZ-1)]++;
	for(int i=1; i<SZ; i++) b[i] += b[i - 1];
	for(int i=n; i; i--) c[b[(a[i]>>w) & (SZ-1)]--] = a[i];}
void Sort(int *a, int n){
	SORT(a, c, n, 0); SORT(c, a, n, 8);
	SORT(a, c, n, 16); SORT(c, a, n, 24); }