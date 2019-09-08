double an[N*2];int q[N*2];
void pivot(int l,int e){//转轴操作 
	int i,j;a[l][e]=1/a[l][e];b[l]*=a[l][e];
	fr(i,1,n)if(i!=e)a[l][i]*=a[l][e];
	fr(i,1,m)if(i!=l&&fabs(a[i][e])>eps){
		b[i]-=a[i][e]*b[l];
		fr(j,1,n)if(j!=e)a[i][j]-=a[i][e]*a[l][j];
		a[i][e]*=-a[l][e];
	}v+=c[e]*b[l];
	fr(i,1,n)if(i!=e)c[i]-=c[e]*a[l][i]; 
	c[e]*=-a[l][e];swap(q[e],q[l+n]);//记录方案 
}void pre(){//特殊处理b_i<0的情况, 没有这种情况可不写 
	for(;;){
		dr(i,m,1)if(b[i]<-eps)break; 
		if(!i)break;
		dr(j,n,1)if(a[i][j]<-eps)break;
		if(!j)return puts("Infeasible"),0;//无解 
		pivot(i,j);}
}//n为变量数, m为约束数, 令目标函数$F=\sum c_jx_j$最大, 第i条约束为$\sum a_{ij}x_j<=b_i$
int main(int n,int m,double c[N],double b[M],double a[M][N]){
	//输出答案, 并输出此时$x_1,x_2,...,x_n$的值 
	double v,p;int l,e;fr(i,1,n)q[i]=i;
	for(pre();;pivot(l,e)){//寻找更优解 
		dr(i,n,1)if(c[i]>eps)break;//选择系数大于0的 
		if(!i)break;//找到最优解
		p=inf;e=i;fr(i,1,m)if(a[i][e]>eps&&p>b[i]/a[i][e])
			p=b[i]/a[i][e],l=i;
		if(p==inf)return puts("Unbounded"),0; //找不到可行的基本变量, 最优解无穷大 
	}
	printf("%.8f",v);//输出答案 
	fr(i,n+1,n+m)an[q[i]]=b[i-n];
	fr(i,1,n)printf("%.8lf ",an[i]);}//输出方案 
// 标准型: maximize $\bf c^Tx$, subject to $\bf Ax\leq b$ and $\bf x\geq 0$
// 对偶型: minimize $\bf b^Ty$, subject to $\bf A^Tx\geq c$ and $\bf y\geq 0$