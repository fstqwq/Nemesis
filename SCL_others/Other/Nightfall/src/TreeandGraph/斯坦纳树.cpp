void Steiner(n,m,k){
	//n为点数,m为边数,1~k为要联通的点, 加双向边 
	rd(n,m,k);E=(1<<k)-1;fr(i,1,n)fr(j,1,E)f[i][j]=inf;
	fr(i,1,k)f[i][1<<(i-1)]=0;
	fr(w,1,E){
		fr(i,1,n)for(S=w&(w-1);S;S=w&(S-1))
			f[i][w]=min(f[i][w],f[i][S]+f[i][w-S]);//DP
		for(h=t=0,i=1;i<=n;i++)if(f[i][w]<inf)q[++t]=i,v[i]=1;
		for(;h^t;)for(v[x=q[h=h%n+1]]=0,i=fir[x];i;i=ne[i])//SPFA
			if(f[y=la[i]][w]>f[x][w]+va[i])
				if(f[y][w]=f[x][w]+va[i],!v[y])v[q[t=t%n+1]=y]=1;
	}
	for(an=inf,i=1;i<=n;i++)an=min(an,f[i][E]);