//id[i]为点i的标号，seq[i]为标号为i的点，G[]存图 
int q[N],label[N],id[N],vis[N],seq[N],c[N]; vector<int>G[N];
struct P{int lab,u;bool operator<(const P&a) const {return lab<a.lab;}};
void mcs(){//MCS算法求标号序列,优先队列做到O(mlgn) 
	int i,j,u,v;CL(id);CL(label);
	CL(seq);priority_queue<P>Q;
	fr(i,1,n)Q.push(P{0,i}); //label_i表示第i个点与多少个已标号的点相邻 
	dr(i,n,1){
		for(;id[Q.top().u];)Q.pop(); //每次选label_i最大的未标号的点标号 
		u=Q.top().u;Q.pop();id[u]=i;
		for(j=0;j<G[u].size();j++)if(v=G[u][j],!id[v]) label[v]++,Q.push(P{label[v],v});
	}fr(i,1,n)seq[id[i]]=i;
}bool ok(){//O(m)判断是否是弦图 
	int i,j,t,u,v,w;CL(vis);
	dr(i,n,1){
		u=seq[i];t=0;//标号从小到大找点 
		for(j=0;j<G[u].size();j++)
			if(v=G[u][j],id[v]>id[u])q[++t]=v;
		if(!t)continue;w=q[1];//找标号大于它的点中最小的 
		fr(j,1,t)if(id[q[j]]<id[w])w=q[j];
		for(j=0;j<G[w].size();j++)vis[G[w][j]]=i;
		fr(j,1,t)if(q[j]!=w)if(vis[q[j]]!=i)return 0;
	}return 1;
int setcolor(){//弦图最小染色 团数=染色数 
	int an=0,i,j,u,v;CL(vis);CL(c);
	for(i=n;i;i--){
		u=seq[i];
		for(j=0;j<G[u].size();j++)vis[c[G[u][j]]]=i;
		for(j=1;vis[j]==i;j++);//找最小的没出现的颜色 
		c[u]=j;an=max(an,j);
	}return an;
}mcs();puts(ok()?"YES":"NO");printf("%d\n",setcolor());
