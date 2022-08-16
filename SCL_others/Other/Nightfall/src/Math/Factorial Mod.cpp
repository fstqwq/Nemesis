// n! mod p^q Time : $O(pq^2\frac{\log^2n}{\log p})$
// Output : {a, b} means a*p^b
using Val=unsigned long long; //Val 需要 mod p^q 意义下 + *
typedef vector<Val> poly;
poly polymul(const poly &a,const poly &b){
	int n = (int) a.size(); poly c (n, Val(0));
	for (int i = 0; i < n; ++ i) {
		for (int j = 0; i + j < n; ++ j) {
			c[i + j] = c[i + j] + a[i] * b[j]; } }
	return c; } Val choo[70][70];
poly polyshift(const poly &a, Val delta) {
	int n = (int) a.size(); poly res (n, Val(0));
	for (int i = 0; i < n; ++ i) { Val d = 1;
		for (int j = 0; j <= i; ++ j) {
			res[i - j] = res[i - j]+a[i]*choo[i][j]*d;
			d = d * delta; } } return res; }
void prepare(int q) {
	for (int i = 0; i < q; ++ i) { choo[i][0] = Val(1);
		for (int j = 1; j <= i; ++ j)
			choo[i][j]=choo[i-1][j-1]+choo[i-1][j]; } }
pair<Val, LL> fact(LL n, LL p, LL q) { Val ans = 1;
	for (int r = 1; r < p; ++ r) {
		poly x (q, Val(0)), res (q, Val(0));
		res[0] = 1; LL _res = 0; x[0] = r; LL _x = 0;
		if (q > 1) x[1] = p, _x = 1; LL m = (n - r + p) / p;
		while (m) { if (m & 1) {
				res=polymul(res,polyshift(x,_res)); _res+=_x; }
			m >>= 1; x = polymul(x, polyshift(x, _x)); _x+=_x; }
		ans = ans * res[0]; }
	LL cnt = n / p; if (n >= p) { auto tmp=fact(n / p, p, q);
		ans = ans * tmp.first; cnt += tmp.second; }
	return {ans, cnt}; }