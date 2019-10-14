// double 精度对$10^9+7$ 取模最多可以做到$2^{20}$
// FFT(Reverse(FFT(a,N)),N)=Na, Reverse是a_0不变,1到N-1反过来
const int MOD = 1e9 + 7; const double PI = acos(-1);
typedef complex<double> Complex;
const int MAXN = 262144, L = 15, MASK = (1<<L) - 1;
Complex w[MAXN];
void FFTInit(int N) {
	for (int i = 0; i < N; ++i)
		w[i] = Complex(cos(2*i*PI/N), sin(2*i*PI/N));}
void FFT(Complex p[], int n) { FFTInit(N);
	for (int i = 1, j = 0; i < n - 1; ++i) {
		for (int s = n; j ^= s >>= 1, ~j & s;);
		if (i < j) swap(p[i], p[j]); }
	for (int d = 0; (1 << d) < n; ++d) {
		int m = 1 << d, m2 = m * 2, rm = n >> (d+1);
		for (int i = 0; i < n; i += m2) {
			for (int j = 0; j < m; ++j) {
				Complex &p1 = p[i+j+m], &p2 = p[i+j];
				Complex t = w[rm * j] * p1;
				p1 = p2 - t, p2 = p2 + t; } } } }
void FFT_inv(Complex p[],int n) {
	FFT(p,n); reverse(p + 1, p + n);
	for (int i = 0; i < n; ++ i) p[i] /= n; }
Complex A[MAXN], B[MAXN], C[MAXN], D[MAXN];
void mul(int *a, int *b, int N) {
	for (int i = 0; i < N; ++i) {
		A[i] = Complex(a[i] >> L, a[i] & MASK);
		B[i] = Complex(b[i] >> L, b[i] & MASK); }
	FFT(A, N), FFT(B, N);
	for (int i = 0; i < N; ++i) { int j = (N - i) % N;
		Complex da = (A[i]-conj(A[j]))*Complex(0, -0.5),
				db = (A[i]+conj(A[j]))*Complex(0.5, 0),
				dc = (B[i]-conj(B[j]))*Complex(0, -0.5),
				dd = (B[i]+conj(B[j]))*Complex(0.5, 0);
		C[j] = da * dd + da * dc * Complex(0, 1);
		D[j] = db * dd + db * dc * Complex(0, 1); }
	FFT(C, N), FFT(D, N);
	for (int i = 0; i < N; ++i) {
		LL  da = (LL)(C[i].imag() / N + 0.5) % MOD,
			db = (LL)(C[i].real() / N + 0.5) % MOD,
			dc = (LL)(D[i].imag() / N + 0.5) % MOD,
			dd = (LL)(D[i].real() / N + 0.5) % MOD;
		a[i]=((dd << (L*2)) + ((db+dc) << L) + da) %MOD;}}
// 4179340454199820289LL (4e18) 原根=3 两倍不会爆 LL
// 2013265921 原根=31 两倍平方不会爆 LL
// 998244353 原根=3 // 1004535809 原根=3 // 469762049 原根=3
void NTT(int *a,int n,int f=1){
	int i,j,k,m,u,v,w,wm;
	for(i=n>>1,j=1,k;j<n-1;j++){
		if(i>j)swap(a[i],a[j]);
		for(k=n>>1;k<=i;k>>=1)i^=k;i^=k;
	}for(m=2;m<=n;m<<=1)
		for(i=0,wm=Pw(G,f==1?(M-1)/m:(M-1)/m*(m-1),M);i<n;i+=m)
			for(j=i,w=1;j<i+(m>>1);j++){
				u=a[j],v=1ll*w*a[j+(m>>1)]%M;
				if((a[j]=u+v)>=M)a[j]-=M;
				if((a[j+(m>>1)]=u-v)<0) a[j+(m>>1)]+=M;
				w=1ll*w*wm%M;
			}
	if(f==-1)for(w=Pw(n,M-2,M),i=0;i<n;i++)a[i]=1ll*a[i]*w%M;
}
void FWT(int w){//w=1为正运算, w=0为逆运算 
	int i,j,k,x,y;
	for(i=1;i<N;i*=2)for(j=0;j<N;j+=i*2){
		for(k=0;k<i;k++) {
		x=a[j+k],y=a[i+j+k];
		if(w){
			//xor a[j+k]=x+y a[i+j+k]=x-y
			//and a[j+k]=x+y
			//or  a[i+j+k]=x+y
		}else{
			//xor a[j+k]=(x+y)/2 a[i+j+k]=(x-y)/2
			//and a[j+k]=x-y
			//or  a[i+j+k]=y-x
		} } } }