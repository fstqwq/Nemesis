struct Dominator_Tree{
	//n为点数，s为起点，e[]中记录每条边 
	int n,s,cnt;int dfn[N],id[N],pa[N], semi[N],idom[N],p[N],mn[N];
	vector<int>e[N],dom[N],be[N];
	void ins(x,y){e[x].pb(y);}
	void dfs(int x){//先得到DFS树 
		dfn[x]=++cnt;id[cnt]=x;
		for(auto i:e[x]){
			if(!dfn[i])dfs(i),pa[dfn[i]]=dfn[x];
			be[dfn[i]].push_back(dfn[x]);
		}}
	int get(int x){//带权并查集 
		if(p[x]!=p[p[x]]){
			if(semi[mn[x]]>semi[get(p[x])]) mn[x]=get(p[x]);
			p[x]=p[p[x]];
		}return mn[x];
	}void LT(){//求出semi和idom得到支配树 
		for(int i=cnt;i>1;i--){
			for(auto j:be[i]) semi[i]=min(semi[i],semi[get(j)]);
			dom[semi[i]].push_back(i); int x=p[i]=pa[i];
			for(auto j:dom[x]) idom[j]=(semi[get(j)]<x?get(j):x);
			dom[x].clear();
		}fr(i,2,cnt){
			if(idom[i]!=semi[i])idom[i]=idom[idom[i]];
			dom[id[idom[i]]].push_back(id[i]);
		}
	}void build(){//建立支配树 
		fr(i,1,n)dfn[i]=0,dom[i].clear(), be[i].clear(),p[i]=mn[i]=semi[i]=i; 
		cnt=0;dfs(s);LT();
	}
}G;
