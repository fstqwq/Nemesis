LL KM(int n,LL w[N][N]){ // n 为点, w 为边权  不存在的边权开 -n*(|maxv|+1),inf 设为 3n*(|maxv|+1)
	static LL lx[N],ly[N],slk[N];
	static int lk[N],pre[N];static bool vy[N];
	LL ans=0;int x,py,d,p;
	fr(i,1,n)fr(j,1,n)lx[i]=max(lx[i],w[i][j]);
	fr(i,1,n){
		fr(j,1,n)slk[j]=inf,vy[j]=0;
		for(lk[py=0]=i;lk[py];py=p){
			vy[py]=1;d=inf;x=lk[py];
			fr(y,1,n)if(!vy[y]){
				if(lx[x]+ly[y]-w[x][y]<slk[y])
					slk[y]=lx[x]+ly[y]-w[x][y],pre[y]=py;
				if(slk[y]<d)d=slk[y],p=y;
			}fr(y,0,n) if(vy[y])lx[lk[y]]-=d,ly[y]+=d; else slk[y]-=d;
		}for(;py;py=pre[py])lk[py]=lk[pre[py]];}
	fr(i,1,n)ans+=lx[i]+ly[i];
	return ans;}//lk[] 为与右部点连的左部点
