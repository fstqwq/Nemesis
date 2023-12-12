using poly = vector<int>;
poly omega[25]; // 单位根

// n 是 DFT 的最大长度，例如如果最多有两个长为 m 的多项式相乘，
// 或者求逆的长度为 m，那么 n 需要 >= 2m
void ntt_init(int n) { // n = 2^k
	for (int k = 2, d = 0; k <= n; k *= 2, d++) {
		omega[d].resize(k + 1);

		int wn = qpow(3, (p - 1) / k), tmp = 1;
		for (int i = 0; i <= k; i++) {
			omega[d][i] = tmp;
			tmp = (long long)tmp * wn % p;
		}
	}

	inv[0] = inv[1] = 1;
	for (int i = 2; i < n; i++)
		inv[i] = (ll)inv[p % i] * (p - p / i) % p;
}

// 传入的必须是 [0, p) 范围内，不能有负的
// 否则把 d == 16 改成 d % 8 == 0 之类
void ntt(int *c, int n, int t) {
	static ull a[MAXN];
	for (int i = 0; i < n; i++) a[i] = c[i];

	for (int i = 1, j = 0; i < n - 1; i++) {
		int k = n;
		do
			j ^= (k >>= 1);
		while (j < k);

		if (i < j)
			swap(a[i], a[j]);
	}

	for (int k = 1, d = 0; k < n; k *= 2, d++) {
		if (d == 16)
			for (int i = 0; i < n; i++)
				a[i] %= p;

		for (int i = 0; i < n; i += k * 2)
			for (int j = 0; j < k; j++) {
				int w = omega[d][t > 0 ? j : k * 2 - j];
				ull u = a[i + j], v = w * a[i + j + k] % p;
				a[i + j] = u + v;
				a[i + j + k] = u - v + p;
			}
		}
		
	if (t > 0) {
		for (int i = 0; i < n; i++)
			c[i] = a[i] % p;
	}
	else {
		int inv = qpow(n, p - 2);
		for (int i = 0; i < n; i++)
			c[i] = a[i] * inv % p;
	}
}

// u, v 长度要相同，返回长度是两倍
poly poly_calc(const poly& u, const poly& v, function<int(int, int)> op) {
	static int a[MAXN], b[MAXN], c[MAXN];

	int n = (int)u.size();

	memcpy(a, u.data(), sizeof(int) * n);
	fill(a + n, a + n * 2, 0);
	memcpy(b, v.data(), sizeof(int) * n);
	fill(b + n, b + n * 2, 0);

	ntt(a, n * 2, 1);
	ntt(b, n * 2, 1);

	for (int i = 0; i < n * 2; i++)
		c[i] = op(a[i], b[i]);

	ntt(c, n * 2, -1);

	return poly(c, c + n * 2);
}

// 乘法，返回长度是两倍
poly poly_mul(const poly& u, const poly& v) {
	return poly_calc(u, v, [](int a, int b) { return (ll)a * b % p; });
}

// 求逆，返回长度不变
poly poly_inv(const poly& a) {
	poly c{qpow(a[0], p - 2)}; // 常数项一般都是 1

	for (int k = 2; k <= (int)a.size(); k *= 2) {
		c.resize(k);

		poly b(a.begin(), a.begin() + k);
		c = poly_calc(b, c, [](int bi, int ci) {
			return ((2 - (ll)bi * ci) % p + p) * ci % p;
		});
		memset(c.data() + k, 0, sizeof(int) * k);
	}

	c.resize(a.size());
	return c;
}

// 开根，返回长度不变
poly poly_sqrt(const poly& a) {
	poly c{1}; // 常数项不是 1 的话要写二次剩余

	for (int k = 2; k <= (int)a.size(); k *= 2) {
		c.resize(k);

		poly b(a.begin(), a.begin() + k);
		b = poly_mul(b, poly_inv(c));

		for (int i = 0; i < k; i++)
			c[i] = (ll)(c[i] + b[i]) * inv_2 % p; // inv_2 是 2 的逆元
	}

	c.resize(a.size());
	return c;
}

// 求导
poly poly_derivative(const poly& a) {
	poly c(a.size());
	for (int i = 1; i < (int)a.size(); i++)
		c[i - 1] = (ll)a[i] * i % p;
	return c;
}

// 不定积分，最好预处理逆元
poly poly_integrate(const poly& a) {
	poly c(a.size());
	for (int i = 1; i < (int)a.size(); i++)
		c[i] = (ll)a[i - 1] * inv[i] % p;
	return c;
}

// ln，常数项不能为 0，返回长度不变
poly poly_ln(const poly& a) {
	auto c = poly_mul(poly_derivative(a), poly_inv(a));
	c.resize(a.size());
	return poly_integrate(c);
}

// exp，常数项必须是 0，返回长度不变
// 常数很大并且总代码很长, 一般可以改用分治 FFT
// 依据: 设 $G(x) = \exp F(x)$, 则 $g_i = \sum_{k=1}^{i-1} f_{i-k} * k * g_k$
poly poly_exp(const poly& a) {
	poly c{1};

	for (int k = 2; k <= (int)a.size(); k *= 2) {
		c.resize(k);
		
		auto b = poly_ln(c);
		for (int i = 0; i < k; i++) {
			b[i] = a[i] - b[i];
			if (b[i] < 0)
				b[i] += p;
		}
		(++b[0]) %= p;

		c = poly_mul(b, c);
		memset(c.data() + k, 0, sizeof(int) * k);
	}

	c.resize(a.size());
	return c;
}
