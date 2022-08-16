struct complex {
	double x , yi;
	complex(double x = 0,double yi = 0): x(x), yi(yi) {}
	friend complex operator + (const complex a,const complex b) {
		return complex(a.x + b.x, a.yi + b.yi);
	}
	friend complex operator - (const complex a,const complex b) {
		return complex(a.x - b.x, a.yi - b.yi);
	}
	friend complex operator * (const complex a,const complex b) {
		return complex(a.x * b.x - a.yi * b.yi , a.x * b.yi + a.yi * b.x);
	}
	friend complex operator / (const complex a,const double b) {
		return complex(a.x / b, a.yi / b);
	}
};
void FFT(complex *X,int n,int flag) {
	for(int i = 0; i < n; i++) {
		int p = 0, t = i;
		for(int j = 1; j < n; j <<= 1)
		  p <<= 1, p |= (t & 1), t >>= 1;
		if(i < p) std::swap(X[i], X[p]);
	}
	for(int m = 2; m <= n; m <<= 1) {
		complex wm = complex(cos((double) 2 * pi * flag / m), sin((double)2 * pi * flag / m));
		for(int i = 0 ; i < n; i += m) {
		    complex wk = complex(1, 0); 
			for(int j = 0; j < (m >> 1); wk = wk * wm, j++) {
				complex u = X[i + j], t = wk * X[i + j + (m >> 1)];
				X[i + j] = u + t, X[i + j + (m >> 1)] = u - t;
			}
		}
	}
	if(flag == -1) for(int i = 0; i < n; i++) X[i] = X[i] / n;
}
void solve(int l,int r) {
	if(l == r) return;
	static complex A[maxn], B[maxn];
	int mid = (l + r) >> 1;
	int len = 1;
	solve(l, mid);
	while(len < (r - l + 1)) len <<= 1;
	len <<= 1;
	for(int i = 0; i < len; i++) A[i] = B[i] = complex(0, 0);
	for(int i = 1; i <= r - l; i++) A[i] = complex(a[i], 0);
	for(int i = l; i <= mid; i++) B[i - l] = complex(f[i], 0);
	FFT(A, len, 1);
	FFT(B, len, 1);
	for(int i = 0; i < len; i++) A[i] = A[i] * B[i];
	FFT(A, len, -1);
	for(int i = mid + 1; i <= r; i++) (f[i] += round(A[i - l].x)) %= mod;
	solve(mid + 1, r);
}
