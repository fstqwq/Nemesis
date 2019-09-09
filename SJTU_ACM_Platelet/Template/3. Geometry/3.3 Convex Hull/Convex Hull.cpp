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
#define maxn 10010
#define eps 1e-6
#define cabs(_a) ((_a)>0?(_a):-(_a))
int n;
struct Point{
	int x,y;
	inline Point operator - (const Point &that) const {return (Point){x-that.x,y-that.y};}
	inline int operator * (const Point &that) const {return x*that.y-y*that.x;}
	inline bool operator < (const Point &that) const {return x<that.x||(x==that.x&&y<that.y);}
	inline bool operator == (const Point &that) const {return cabs(x-that.x)<eps&&cabs(y-that.y)<eps;}
}p[maxn],stack[maxn];
int main()
{
	n=FastIn();
	R int i,top=0,ans=0,t;
	for (i=1;i<=n;i++)
	{
		p[i].x=FastIn();
		p[i].y=FastIn();
	}
	std::sort(p+1,p+n+1);
	n=std::unique(p+1,p+n+1)-p-1;
	for (i=1;i<=n;i++)
	{
		while (top>=2&&((stack[top]-stack[top-1])*(p[i]-stack[top-1])<=0)) top--;
		stack[++top]=p[i];
	}
	for (i=n-1,t=top+1;i;i--)
	{
		while (top>=t&&((stack[top]-stack[top-1])*(p[i]-stack[top-1])<=0)) top--;
		stack[++top]=p[i];
	}
	if (n>1) top--;
	for (i=3;i<=top;i++)
	{
		ans+=(stack[i]-stack[1])*(stack[i-1]-stack[1]);
	}
	ans=cabs(ans);
	printf("%d\n",ans%100?ans/100:ans/100+1);
	return 0;
}
