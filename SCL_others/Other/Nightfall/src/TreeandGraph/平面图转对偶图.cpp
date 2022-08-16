int to[N],v[N],q[N];LL Area;
struct P{int x,y;double o;}p[N],e[N];
struct cmp{bool operator()(int a,int b){return e[a].o<e[b].o;}};
LL operator*(P a,P b){return 1ll*a.x*b.y-1ll*a.y*b.x;}
set<int,cmp>S[N];set<int,cmp>::iterator it;
void ADD(int x,int y){}//再新图中加边 不能有重复点 可以有多余边
void Planet(n,m){ //n为点数, m为边数, p[i].x/y为n个点坐标
	int j,x,y,cnt=0;
	fr(i,0,m-1){
		rd(x);rd(y); //第i条边连接第x个点和第y个点 
		e[i<<1]=P{x,y, atan2(p[y].x-p[x].x,p[y].y-p[x].y)}; //加双向边, 支持双向边权 
		e[i<<1|1]=P{y,x, atan2(p[x].x-p[y].x,p[x].y-p[y].y)};
	}m*=2;
	fr(i,0,m-1)S[e[i].x].insert(i);
	fr(i,0,m-1)if(!v[i]){
		for(q[t=1]=j=i;;q[++t]=j=*it){ //按极角排序选最少转动角度找出下一条边 
			it=S[e[j].y].upper_bound(j^1);
			if(it==S[e[j].y].end())it=S[e[j].y].begin();
			if(*it==i)break;
		}Area=0;fr(j,1,t) Area+=p[e[q[j]].x]*p[e[q[j]].y],v[q[j]]=1;
		if(Area>0){cnt++;fr(j,1,t)to[q[j]]=cnt;} //面积大于0是有限区域 
	}fr(i,0,m-1)ADD(to[i],to[i^1]);} //若这条边有边权, 在e[i].z中记录 // 如果to[i]为0不一定是外平面, 要判在一个最小的多边形内
