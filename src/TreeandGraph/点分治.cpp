void dsz(int x,int fa){
	sz[x]=1;mv[x]=0;
	for(int i=fir[x],y;i;i=ne[i])if(!vis[y=la[i]]&&y!=fa)
		dsz(y,x),sz[x]+=sz[y],mv[x]=max(mv[x],sz[y]);
}void drt(int zs,int x,int fa,int&rt){/
	mv[x]=max(mv[x],sz[zs]-sz[x]);if(mv[x]<mv[rt]||!rt)rt=x;
	for(int i=fir[x],y;i;i=ne[i])
		if(!vis[y=la[i]]&&y!=fa)drt(zs,y,x,rt);
}int fz(int x){
	int i,p,y,rt=0;dsz(x,0);drt(x,x,0,rt);vis[rt]=1;
	for(i=fir[rt];i;i=ne[i])if(!vis[y=la[i]])INS(rt,fz(y));
	return rt;}