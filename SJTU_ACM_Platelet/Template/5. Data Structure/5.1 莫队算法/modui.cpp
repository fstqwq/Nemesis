//
//  Title: Modui
//  Date: 26.02.2016
//  Test:BZOJ-2038
//  Complexity:O(n^3/2)
//
/*
	莫队算法——将所有询问储存起来，然后分块暴力处理。
	时间复杂度为O（n×根号n）。
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
int col[maxn],num[maxn],size,pos[maxn];
long long up[maxn],dw[maxn],ans;
struct Query{
	int l,r,id;
}q[maxn];
inline bool cmp(const Query &i,const Query &j){
	return pos[i.l]!=pos[j.l] ? (i.l<j.l) : (pos[i.l]&1 ? i.r<j.r : i.r>j.r);
}
inline long long gcd(R long long a,R long long b){
	R long long tmp;
	while (b){
		tmp=b;
		b=a%b;
		a=tmp;
	}
	return a;
}
inline void update(R int x,R int d){
	ans-=num[col[x]]*num[col[x]];
	num[col[x]]+=d;
	ans+=num[col[x]]*num[col[x]];
}
int main()
{
	R int n=FastIn(),m=FastIn();size=(int)sqrt(n*1.0);
	for (R int i=1;i<=n;i++) col[i]=FastIn(),pos[i]=(i-1)/size+1;
	for (R int i=1;i<=m;i++){
		q[i].l=FastIn();q[i].r=FastIn();q[i].id=i;
	}
	std::sort(q+1,q+m+1,cmp);
	R int l=1,r=0;
	for (R int i=1;i<=m;i++){
		R int id_now=q[i].id;
		if (q[i].l==q[i].r){
			up[id_now]=0;dw[id_now]=1;continue;
		}
		for (;r<q[i].r;r++) update(r+1,1);
		for (;r>q[i].r;r--) update(r,-1);
		for (;l<q[i].l;l++) update(l,-1);
		for (;l>q[i].l;l--) update(l-1,1);
		R long long aa,bb,cc;
		aa=ans-q[i].r+q[i].l-1;
		bb=(long long)(q[i].r-q[i].l+1)*(q[i].r-q[i].l);
		cc=gcd(aa,bb);aa/=cc;bb/=cc;
		up[id_now]=aa;dw[id_now]=bb;
	}
	for (R int i=1;i<=m;i++) printf("%lld/%lld\n",up[i],dw[i] );
	return 0;
}

