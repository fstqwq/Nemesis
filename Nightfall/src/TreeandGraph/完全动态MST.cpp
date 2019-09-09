int v[N],to[N],F[N],R[N],nb[22],ans[N];
struct P{int x,y,z,id;}e[22][N],p[N],q[N];
bool cmp(P a,P b){return a.z<b.z;}
int gf(int x){return F[x]==x?x:F[x]=gf(F[x]);}
void cdq(int d,int l,int r,int z){
	int i,o,u,w=0,m=nb[d],mid=l+r>>1;
	if(l==r)v[q[l].x]=q[l].y;
	fr(i,1,m)e[d][i].z=v[e[d][i].id],p[i]=e[d][i], to[p[i].id]=i,F[p[i].x]=p[i].x,F[p[i].y]=p[i].y;
	if(l==r){
		sort(p+1,p+m+1,cmp);fr(i,1,m){
			o=gf(p[i].x);u=gf(p[i].y);
			if(o!=u)F[o]=u,z+=p[i].z;
		}ans[l]=z;return;
	}fr(i,l,r)p[to[q[i].x]].z=-inf;
	sort(p+1,p+m+1,cmp);fr(i,1,m){
		o=gf(p[i].x);u=gf(p[i].y);
		if(o!=u)F[o]=u,R[++w]=i;
	}fr(i,1,m)F[p[i].x]=p[i].x,F[p[i].y]=p[i].y;
	fr(i,1,w)if(p[R[i]].z!=-inf)
		z+=p[R[i]].z,F[gf(p[R[i]].x)]=gf(p[R[i]].y);
	nb[d+1]=0;fr(i,1,m){
		p[i].x=gf(p[i].x);p[i].y=gf(p[i].y);
		if(p[i].z==-inf)p[i].z=inf,e[d+1][++nb[d+1]]=p[i];
	}
	sort(p+1,p+m+1,cmp);fr(i,1,m){
		o=gf(p[i].x);u=gf(p[i].y);
		if(o!=u)if(F[o]=u,p[i].z!=inf)
			e[d+1][++nb[d+1]]=p[i];
	}cdq(d+1,l,mid,z);cdq(d+1,mid+1,r,z);
}int main(){rd(n,m,Q); // 点数 边数 询问数 
	fr(i,1,m)rd(e[0][i].x,e[0][i].y,e[0][i].z), e[0][i].id=i,v[i]=e[0][i].z;// 读入边和权值
	fr(i,1,Q)scanf("%d%d",&q[i].x,&q[i].y); // 将第 x 条边修改为 y, 然后询问最小生成树
	nb[0]=m;cdq(0,1,Q,0);fr(i,1,Q)printf("%lld\n",ans[i]);// 输出答案
}