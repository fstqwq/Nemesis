bool cmp(int a,int b){return dep[a]<dep[b];}
path merge(path o1,path o2){
	static int d[4], c[2];
    if(!o1.x||!o2.x)return path({0,0});
    d[0]=lca(o1.x,o2.x);d[1]=lca(o1.x,o2.y);d[2]=lca(o1.y,o2.x);d[3]=lca(o1.y,o2.y);
    c[0]=lca(o1.x,o1.y);c[1]=lca(o2.x,o2.y);
    sort(d,d+4,cmp); sort(c, c + 1, cmp);
    if(dep[c[0]]<=dep[d[0]]&&dep[c[1]]<=dep[d[2]])
	return path({d[2],d[3]});else return path({0, 0});//
}    