//
// Title : Splay Tree
// Date : 11.01.2016
// Complexity : O(nlogn) （期望）
// Test : BZOJ-1251
/*
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

#ifdef WIN32
	#define LL "%I64d"
#else
	#define LL "%lld"
#endif

#ifdef CT
	#define debug(...) printf(__VA_ARGS__)
#else
	#define debug(...)
#endif

#define R register
#define getc() (S==T&&(T=(S=B)+fread(B,1,1<<15,stdin),S==T)?EOF:*S++)
#define gmax(_a, _b) ((_a) > (_b) ? (_a) : (_b))
#define gmin(_a, _b) ((_a) < (_b) ? (_a) : (_b))
#define cmax(_a, _b) (_a < (_b) ? _a = (_b) : 0)
#define cmin(_a, _b) (_a > (_b) ? _a = (_b) : 0)
char B[1<<15],*S=B,*T=B;
inline int FastIn()
{
	R char ch;R int cnt=0;R bool minus=0;
	while (ch=getc(),(ch < '0' || ch > '9') && ch != '-') ;
	ch == '-' ?minus=1:cnt=ch-'0';
	while (ch=getc(),ch >= '0' && ch <= '9') cnt = cnt * 10 + ch - '0';
	return minus?-cnt:cnt;
}
#define maxn 50010
int n,Q,root;
int fa[maxn],ch[maxn][2],id[maxn],size[maxn];
int tag[maxn],mx[maxn],num[maxn];
bool rev[maxn];
inline void update(int x){
	R int ls=ch[x][0],rs=ch[x][1];
	mx[x]=num[x];
	cmax(mx[x],mx[ls]);cmax(mx[x],mx[rs]);
	size[x]=size[ls]+size[rs]+1;
}//更新
void build(int l,int r,int rt){
	if (l>r) return ;
	R int mid=l+r>>1;
	fa[mid]=rt;
	if (mid<rt) ch[rt][0]=mid;
	else ch[rt][1]=mid;
	build(l,mid-1,mid);
	build(mid+1,r,mid);
	update(mid);
}//建树
inline void pushdown(int x){
	R int ls=ch[x][0],rs=ch[x][1];
	if (tag[x]){
		R int lazy=tag[x];
		if (ls) tag[ls]+=lazy,num[ls]+=lazy,mx[ls]+=lazy;
		if (rs) tag[rs]+=lazy,num[rs]+=lazy,mx[rs]+=lazy;
		tag[x]=0;
	}
	if (rev[x]){
		if (ls) rev[ls]^=1;
		if (rs) rev[rs]^=1;
		ch[x][1]=ls;ch[x][0]=rs;
		rev[x]=0;
	}
}//具体下传的过程
inline void rotate(int x){//把x向上旋转到x的父亲
	R int f=fa[x],gf=fa[f],d=(ch[f][1]==x);//f表示x的父亲，gf是祖父，d是x在其父亲的位置
	if (f==root) root=x,ch[0][0]=x;
	(ch[f][d]=ch[x][d^1])>0 ? fa[ch[f][d]]=f : 0;//把x的儿子中与d相反的节点来代替x的位置
	(fa[x]=gf)>0 ? ch[gf][ch[gf][1]==f]=x : 0;//把x代替f的位置
	fa[ch[x][d^1]=f]=x;//把f接到x的下面
	update(f);//更新f节点
}
inline void splay(int x,int rt){//把x旋转到rt
	while (fa[x]!=rt){
		R int f=fa[x],gf=fa[f];
		if (gf!=rt) rotate((ch[gf][1]==f)^(ch[f][1]==x) ? x :f);//如果祖孙三代是相同方向就转父亲，不然转自己
		rotate(x);
	}
	update(x);
}
int find(int x,int rank){
	if (tag[x]||rev[x]) pushdown(x);
	R int ls=ch[x][0],rs=ch[x][1],lsize=size[ls];
	if (lsize+1==rank) return x;
	if (lsize>=rank) return find(ls,rank);
	else return find(rs,rank-lsize-1);
}//找第k小
inline int prepare(int l,int r){
	R int x=find(root,l-1);
	splay(x,0);
	x=find(root,r+1);
	splay(x,root);
	return ch[x][0];
}//把l-1旋到根，r+1旋到右儿子，然后返回r+1的左儿子，返回一个包含[l，r]的节点
inline void add(int l,int r,int w){
	R int x=prepare(l,r);
	tag[x]+=w,num[x]+=w,mx[x]+=w;
}//区间加
inline void rever(int l,int r){
	R int x=prepare(l,r);
	rev[x]^=1;
}//区间翻转
inline void query(int l,int r){
	R int x=prepare(l,r);
	printf("%d\n",mx[x] );
}//区间查询最大值
inline int split(R int k){
	R int ls;
	if (k<size[root])
	{
		R int kth=find(root,k+1);
		splay(kth);ls=ch[kth][0];
		fa[ls]=0;ch[kth][0]=0;
		size[kth]-=size[ls];
	}
	else{
		ls=root;root=0;
	}
	return ls;
}//删除数列
inline void merge(R int nwrt){
	if (!root) {root=nwrt;return;}
	R int nw=find(root,1);
	splay(nw);fa[nwrt]=nw;ch[nw][0]=nwrt;
	size[nw]+=size[nwrt];
}//合并数列
int main()
{
	n=FastIn()+2;Q=FastIn();R int i,l,r,v,cmd;mx[0]=-23333333;
	build(1,n,0);root=(1+n)>>1;
	for (;Q--;){
		cmd=FastIn();l=FastIn()+1;r=FastIn()+1;
		if (cmd==1) v=FastIn(),add(l,r,v);
		else if (cmd==2) rever(l,r);
		else query(l,r);
	}
	return 0;
}

