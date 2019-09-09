// 拉格朗日插值 n 为点数, x 为要求的 f(x), 已知 f(X[i])=Y[i]
D lagrange(int n,D x,D X[],D Y[]){
	int i,j;D ans,v;fr(i,n){
		v=1;fr(j,n)if(i!=j)v*=(x-X[j])/(X[i]-X[j]);
		ans+=v*Y[i];}
	return ans;}
// 牛顿插值, 给出 f(X[i])=Y[i]),i=0...n-1
void pre(){//O(n^2) 预处理 
	fr(i,0,n-1)f[i][0]=Y[i];
	fr(i,1,n-1)fr(j,1,i) f[i][j]=(f[i][j-1]-f[i-1][j-1])/(X[i]-X[i-j]); }
D getfx(D x){//O(n) 询问单点值 
	D an=f[0][0],v=1;
	fr(i,1,n-1)v*=(x-X[i-1]),an+=f[i][i]*v;
	return an;}
