bool cmp(int a,int b){return dep[a]<dep[b];}
path merge(path u, path v){
	int d[4], c[2];
	if (!u.x||!v.x) return path(0, 0);
	d[0]=lca(u.x,v.x); d[1]=lca(u.x,v.y);
	d[2]=lca(u.y,v.x); d[3]=lca(u.y,v.y);
	c[0]=lca(u.x,u.y); c[1]=lca(v.x,v.y);
	sort(d,d+4,cmp); sort(c,c+2,cmp);
	if (dep[c[0]] <= dep[d[0]] && dep[c[1]] <= dep[d[2]])
		return path(d[2],d[3]);
	else return path(0, 0); }
