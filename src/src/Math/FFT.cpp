const double pi = acos((double)-1.);
struct Complex { double a, b; // 通常没有必要用long double
	Complex(double a = 0., double b = 0.) : a(a), b(b) {}
	Complex operator + (const Complex &o) const {
		return Complex(a + o.a, b + o.b); }
	Complex operator - (const Complex &o) const {
		return Complex(a - o.a, b - o.b); }
	Complex operator * (const Complex &o) const {
		return Complex(a*o.a - b*o.b, a*o.b + b*o.a);}
	Complex operator * (double x) const {
		return Complex(a * x, b * x); }
	Complex &operator += (const Complex &o) {
		return *this = *this + o; }
	Complex conj() const { return Complex(a, -b); }
} omega[maxn], omega_inv[maxn];
const Complex ima = Complex(0, 1); // i = sqrt(-1)
int fft_n; // 如果调用次数很多就改成分层预处理，cache友好
void FFT_init(int n) { fft_n = n;
	for (int i = 0; i < n; i++)
		omega[i] = Complex(cos(2*pi/n*i), sin(2*pi/n*i));
	omega_inv[0] = omega[0];
	for (int i = 1; i < n; i++) omega_inv[i] = omega[n - i];
}
void FFT(Complex *a, int n, int tp) {
	for (int i = 1, j = 0; i < n - 1; i++) {
		int k = n;
		do j ^= (k >>= 1); while (j < k);
		if (i < j) swap(a[i], a[j]); }
	for (int k = 2, m = fft_n / 2; k <= n; k *= 2, m /= 2)
		for (int i = 0; i < n; i += k)
			for (int j = 0; j < k / 2; j++) {
				Complex u = a[i + j], v = (tp > 0 ? omega : omega_inv)[m * j] * a[i + j + k / 2];
				a[i + j] = u + v; a[i + j + k / 2] = u - v;}
	if (tp < 0) for (int i = 0; i < n; i++) {
		a[i].a /= n; a[i].b /= n; } } // 只有MTT时才需要除b