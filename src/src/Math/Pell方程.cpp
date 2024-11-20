// $x^2 - n * y^2 = 1$ 最小正整数根, n 为完全平方数时无解
// $ x_{k+1} = x_0x_k + ny_0y_k $
// $ y_{k+1} = x_0y_k + y_0x_k $
pair<LL, LL> pell(LL n) {
	static LL p[N], q[N], g[N], h[N], a[N];
	p[1] = q[0] = h[1] = 1; p[0] = q[1] = g[1] = 0;
	a[2] = (LL)(floor(sqrtl(n) + 1e-7L));
	for(int i = 2; ; i ++) {
		g[i] = -g[i - 1] + a[i] * h[i - 1];
		h[i] = (n - g[i] * g[i]) / h[i - 1];
		a[i + 1] = (g[i] + a[2]) / h[i];
		p[i] = a[i] * p[i - 1] + p[i - 2];
		q[i] = a[i] * q[i - 1] + q[i - 2];
		if(p[i] * p[i] - n * q[i] * q[i] == 1)
			return {p[i], q[i]}; }}