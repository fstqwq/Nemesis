int F[N],FF[N];namespace Left_Tree{//可持久化左偏树 
	struct P{int l,r,h,v,x,y;}Tr[N*40];int RT[N],num;
	//l和r是左右儿子,h是高度,v是数值,x和y是在图中的两点 
	int New(P o){Tr[++num]=o;return num;}
	void start(){num=0;Tr[0].l=Tr[0].r=Tr[0].h=0;Tr[0].v=inf;}
	int mg(int x,int y){
		if(!x)return y;
		if(Tr[x].v>Tr[y].v)swap(x,y);
		int o=New(Tr[x]);Tr[o].r=mg(Tr[o].r,y);
		if(Tr[Tr[o].l].h<Tr[Tr[o].r].h)swap(Tr[o].l,Tr[o].r);
		Tr[o].h=Tr[Tr[o].r].h+1;return o;}
	void add(int&k,int v,int x,int y){
		int o=New(Tr[0]);
		Tr[o].v=v;Tr[o].x=x;Tr[o].y=y;
		k=mg(k,o);	}}
using namespace Left_Tree;
struct SPFA{//SPFA, 这里要记录路径 
	void in(){tot=0;CL(fir);}void ins(x,y,z){}
	void work(int S,int n){//F[]求最短路从哪个点来，FF[]记最短路从哪条边来
}}A;
struct Kshort{
int tot,n,m,S,T,k,fir[N],va[M],la[M],ne[M];bool v[N];
struct P{
	int x,y,z;P(){}P(int x,int y,int z):x(x),y(y),z(z){}
	bool operator<(P a)const{return a.z<z;}};
priority_queue<P>Q;void in(){tot=0;CL(fir);}
void ins(x,y,z){}
void init(){//将图读入 
	int i,x,y,z;in();A.in();start();rd(n,m)
	fr(i,1,m)rd(x,y,z),A.ins(y,x,z),ins(x,y,z);
	rd(S,T,k);if(S==T)k++;//注意起点终点相同的情况 
	A.work(T,n);}//A是反向边 
void dfs(int x){
	if(v[x])return;v[x]=1;if(F[x])RT[x]=RT[F[x]];
	for(int i=fir[x],y;i;i=ne[i])if(y=la[i],A.d[y]!=inf&&FF[x]!=i)
		add(RT[x],A.d[y]-A.d[x]+va[i],x,y);
	for(int i=A.fir[x];i;i=A.ne[i])if(F[A.la[i]]==x)dfs(A.la[i]);} 
int work(){//返回答案, 没有返回-1 
	int i,x;dfs(T);
	if(!--k)return A.d[S]==inf?-1:A.d[S]; 
	P u,w;if(RT[S])Q.push(P(S,RT[S],A.d[S]+Tr[RT[S]].v));
	for(;k--;){
		if(Q.empty())return -1;u=Q.top();Q.pop();
		if(x=mg(Tr[u.y].l,Tr[u.y].r))
			Q.push(P(u.x,x,Tr[x].v-Tr[u.y].v+u.z));
		if(RT[x=Tr[u.y].y])Q.push(P(x,RT[x],u.z+Tr[RT[x]].v));}
	return u.z;}}G;
