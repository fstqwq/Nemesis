rd(m);v[1]=a[1]=1,t=++m; //选定m个关键点, 1号点直接加入虚树 
fr(i,2,m)rd(x),v[a[i]]=V[a[i]]=1; //v[]表示是选的点或LCA后的点, V[]表示选的点 
for(sort(a+1,a+m+1,cmp),i=1;i<m;i++) //新加必要关键点
	if(!v[x=lca(a[i],a[i+1])])v[a[++t]=x]=1;
for(m=t,sort(a+1,a+m+1,cmp),ed=0,q[t=1]=1,i=2; i<=m; ins(q[t],a[i]),q[++t]=a[i++])
	for(;st[a[i]]<st[q[t]]||en[a[i]]>en[q[t]];t--); //再排一遍序, 单调栈建虚数 
fr(i,1,m)v[a[i]]=V[a[i]]=fir[a[i]]=0; //求解答案后还原 