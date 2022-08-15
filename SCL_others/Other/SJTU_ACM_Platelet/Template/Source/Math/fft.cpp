typedef double db;
const db pi = acos(-1);

struct Complex {
	db x, y;
	inline Complex operator * (const Complex &that) const {return (Complex) {x * that.x - y * that.y, x * that.y + y * that.x};}
	//inline Complex operator + (const Complex &that) const {return (Complex) {x + that.x, y + that.y};}
	inline Complex operator += (const Complex &that){x+=that.x;y+=that.y;}
	inline Complex operator - (const Complex &that) const {return (Complex) {x - that.x, y - that.y};}
} buf_a[maxn], buf_b[maxn], buf_c[maxn], w[maxn], c[maxn], a[maxn], b[maxn];

int n;
void bit_reverse(Complex *x, Complex *y)
{
	for (int i = 0; i < n; ++i) y[i] = x[i];
	Complex tmp;
	for (int i = 0, j = 0; i < n; ++i)
	{
		(i>j)?tmp=y[i],y[i]=y[j],y[j]=tmp,0:1;
		for (int l = n >> 1; (j ^= l) < l; l >>= 1);
	}
}
void init()
{
	int h=n>>1;
	for (int i = 0; i < h; ++i) w[i+h] = (Complex) {cos(2 * pi * i / n), sin(2 * pi * i / n)};
	for (int i = h; i--; )w[i]=w[i<<1];
}
void dft(Complex *a)
{
	Complex tmp;
	for(int p = 2, m = 1; m != n; p = (m = p) << 1)
		for(int i = 0; i != n; i += p) for(int j = 0; j != m; ++j)
		{
			tmp = a[i + j + m] * w[j + m];
			a[i + j + m] = a[i + j] - tmp;
			a[i + j] += tmp;
		}
}

int main()
{
	fread(S, 1, 1 << 20, stdin);
	int na = F(), nb = F(), x;
	for (int i = 0; i <= na; ++i) a[i].x=F();
	for (int i = 0; i <= nb; ++i) b[i].x=F();
	for (n = 1; n < na + nb + 1; n <<= 1) ;
	bit_reverse(a, buf_a);
	bit_reverse(b, buf_b);
	init();
	dft(buf_a);
	dft(buf_b);
	for (int i = 0; i < n; ++i) c[i] = buf_a[i] * buf_b[i];
	std::reverse(c + 1, c + n);
	bit_reverse(c, buf_c);
	dft(buf_c);
	for (int i = 0; i <= na + nb; ++i) printf("%d%c", int(buf_c[i].x / n + 0.5), " \n"[i==na+nb]);
	return 0;
}
