// 点双联通分量
void ins_new(int x,int y){}//点双树的边 
struct Tarjan{//n为点数，V[]中存每条边 
	int n,id,t,low[N],dfn[N],q[N];vector<int>V[N];void ins(x,y){}
	void in(int o){//初始化，标号从n+1开始 
		id=0;scc=o;fr(i,1,o)V[i].clear(),dfn[i]=low[i]=0;
	}void tj(int x,int fa){
		dfn[x]=low[x]=++id;q[++t]=x;int i,y,o;
		for(i=0;i<V[x].size();i++)if(!dfn[y=V[x][i]]){
			tj(y,x);low[x]=min(low[x],low[y]);
			if(low[y]>=dfn[x])for(ins_new(x,++scc),o=0;y!=o;)
				to[o=q[t--]]=scc,ins_new(scc,o);
		}else if(y!=fa)low[x]=min(low[x],dfn[y]);
	}
	void work(){for(int i=1;i<=n;i++)if(!dfn[i])tj(i,0);}
}G;
// 强连通分量
void tj(int x){
	int i,y,o=0,E=V[x].size();
	low[x]=dfn[x]=++id;is[x]=1;q[++t]=x;		
	for(i=0;i<E;i++)if(!dfn[y=V[x][i]]) tj(y),low[x]=min(low[x],low[y]);
		else if(is[y])low[x]=min(low[x],dfn[y]);
	if(dfn[x]==low[x])
		for(scc++;o!=x;o=q[t--],bl[o]=scc,is[o]=0);}