int F[N];struct P{int x,y,z,a,b;}an,a,b,V,p[N];
bool operator<(P a,P b) {return 1ll*a.x*a.y<1ll*b.x*b.y || 1ll*a.x*a.y==1ll*b.x*b.y&&a.x<b.x;}
P G(int A,int B){} //将边权变为A*X[i]+B*Y[i]做最小生成树 
void sol(P a,P b){
	P c=G(a.y-b.y,b.x-a.x);an=min(an,c); //更新答案 
	if(1ll*c.x*(a.y-b.y)+1ll*c.y*(b.x-a.x) >= -(1ll*a.x*b.y-1ll*a.y*b.x))return;//叉积大于0, 无点 
	sol(a,c);sol(c,b); //递归解决
}LL mul(n,m){//n是点数, m是边数, 返回答案   
	init();//读入每条边(x,y)权值为(a,b) 
	a=G(1,0);b=G(0,1); //先找出离x轴和y轴最近的最小生成树a,b 
	an=min(a,b);sol(a,b);
	return 1ll*an.x*an.y;}
