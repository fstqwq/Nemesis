void Inv(int*A,int*B,int n){ //注意数组大小2n
//多项式求逆, $B=A^{-1}$,n需为2的幂次 
	static int C[N];B[0]=Pw(A[0],M-2,M);B[1]=0; //n=1时$B[0]=A[0]^{-1}$ 
	for(int m=2,i;m<=n;m<<=1){//递归转递推 
		for(i=0;i<m;i++)C[i]=A[i];
		for(i=m;i<2*m;i++)C[i]=B[i]=0; //在模$x^m$意义下超过m次均为0 
		NTT(C,m*2);NTT(B,m*2);
            //$g(x)=g_0(x)(2-f(x)g_0(x))(\mod x^n)$
		for(i=0;i<m*2;i++)
            B[i]=1ll*B[i]*(2-1ll*B[i]*C[i]%M+M)%M;
		NTT(B,m*2,-1);for(i=m;i<m*2;i++)B[i]=0;}
}
void Sqrt(int*A,int*B,int n){//多项式开根, B=sqrt(A), n为2的幂次 
	static int D[N],IB[N];
	B[0]=1;B[1]=0;//n=1时根据题意或二次剩余求解 
	int I2=Pw(2,M-2,M),m,i;
	for(m=2;m<=n;m<<=1){//递归转递推 
		for(i=0;i<m;i++)D[i]=A[i];
		for(i=m;i<2*m;i++)D[i]=B[i]=0;
		NTT(D,m*2);Inv(B,IB,m);NTT(IB,m*2);NTT(B,m*2);
		for(i=0;i<m*2;i++)
            B[i]=(1ll*B[i]*I2+1ll*I2*D[i]%M*IB[i])%M;
		NTT(B,m*2,-1);for(i=m;i<m*2;i++)B[i]=0;
	}
}
// 多项式除法: 给定$n$次多项式$A(x)$和$m\leq n$次多项式$B(x)$, 求出$D(x)$, $R(x)$满足$A(x)=D(x)B(x)+R(x)$, 并且 $degD\leq n-m$, $degR<m$, 复杂度$O(n\log n)$, 常用于线性递推将$2k$项系数拍回$k$项时的优化: 本质是将$2k$项的多项式除以$k$项零化多项式得到的余数
void Div(int *a, int n, int *b, int m, int *d, int *r) {
	// 注意这里$n$和$m$为多项式长度, 注意需要4倍空间
	static int A[MAXN], B[MAXN]; while (!b[m - 1]) m --;
	int p = 1, t = n - m + 1; while (p < t << 1) p <<= 1;
	fill(A, A+p, 0); reverse_copy(b, b+m, A); Inv(A, B, p);
	fill(B+t, B+p, 0); NTT(B, p); reverse_copy(a, a+n, A);
	fill(A + t, A + p, 0); NTT(A, p);
	for (int i = 0; i < p; ++i) A[i] = 1LL*A[i]*B[i] % M;
	NTT(A, p, -1); reverse(A,A+t); copy(A,A+t,d); //lenD<=t
	for (p = 1; p < n; p <<= 1);
	fill(A + t, A + p, 0); NTT(A, p); copy(b, b + m, B);
	fill(B + m, B + p, 0); NTT(B, p);
	for (int i = 0; i < p; ++i) A[i] = 1LL*A[i]*B[i] % M;
	NTT(A, p, -1);
	for (int i = 0; i < m; ++i) r[i] = (a[i]-A[i]+M) % M;
	fill(r+m, r+p, 0); assert(r[m-1] == 0); } //lenR < m