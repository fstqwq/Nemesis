struct Dominator_Tree{
	int n, s, cnt;
	int dfn[N], id[N], pa[N], semi[N], idom[N], p[N], mn[N];
	vector<int> e[N], dom[N], be[N];
	
	void ins(int x, int y){e[x].push_back(y);}
	
	void dfs(int x)
	{
		dfn[x] = ++cnt; id[cnt] = x;
		for(auto i:e[x])
		{
			if(!dfn[i])dfs(i), pa[dfn[i]] = dfn[x];
			be[dfn[i]].push_back(dfn[x]);
		}
	}
	
	int get(int x)
	{
		if(p[x] != p[p[x]])
		{
			if(semi[mn[x]] > semi[get(p[x])])mn[x] = get(p[x]);
			p[x] = p[p[x]];
		}
		return mn[x];
	}
	
	void LT()
	{
		for(int i = cnt; i > 1; i--)
		{
			for(auto j:be[i])semi[i] = min(semi[i], semi[get(j)]);
			dom[semi[i]].push_back(i);
			int x = p[i] = pa[i];
			for(auto j:dom[x])
				idom[j] = (semi[get(j)] < x ? get(j) : x);
			dom[x].clear();
		}
		for(int i = 2; i <= cnt; i++)
		{
			if(idom[i] != semi[i])idom[i] = idom[idom[i]];
			dom[id[idom[i]]].push_back(id[i]);
		}
	}
	void build()
	{
		for(int i = 1; i <= n; i++)
			dfn[i] = 0, dom[i].clear(), be[i].clear(), p[i] = mn[i] = semi[i] = i;
		cnt = 0, dfs(s), LT();
	}
};
