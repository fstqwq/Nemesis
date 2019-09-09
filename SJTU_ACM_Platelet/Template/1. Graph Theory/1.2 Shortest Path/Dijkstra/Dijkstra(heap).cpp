//  
//  Title: 堆优dijkstra
//  Date:17.12.2015
//  Test:YZOJ-1337(单源多汇)
//  Complexity:O(nlogn)
//  
/*
    用堆优化的Dijkstra 
*/
#include<cstdio>
#include<queue>
#include<cstring>
#define maxm 200010
#define maxn 50010
#define getc() (S==T&&(T=(S=B)+fread(B,1,1<<15,stdin),S==T)?EOF:*S++)
//#define getc() getchar()
#define R register
#define cmin(a,b) ((a)>(b)?(a)=(b):0)
char B[1<<15],*S=B,*T=B;
int w[2*maxm],to[2*maxm],next[2*maxm],ecnt;
int last[maxn],d[maxn],n,m,k;
bool vis[maxn],end[maxn];
struct Edge{
	int now,dis;	
};
bool operator < (const Edge &a,const Edge &b) {return a.dis>b.dis;}
inline int FastIn()
{
	R char ch=getc();R int cnt=0;
	while (ch<'0'||ch>'9') ch=getc();
	while (ch>='0'&&ch<='9') cnt=cnt*10+ch-'0',ch=getc();
	return cnt;
}
inline void add(int s,int t,int we){
	w[++ecnt]=we;
	next[ecnt]=last[s];
	to[ecnt]=t;
	last[s]=ecnt;
}
std::priority_queue<Edge> heap;
int main()
{
	n=FastIn();m=FastIn();k=FastIn();R int i,a,b,v,u,dist;
	for (i=1;i<=m;i++) {
		a=FastIn();b=FastIn();v=FastIn();
		add(a,b,v);
		add(b,a,v);
	}
	for (i=1;i<=k;i++) a=FastIn(),add(a,0,0);
	memset(d,63,sizeof(d));
	heap.push((Edge){1,0});
	while (!heap.empty()){
		u=heap.top().now;
		dist=heap.top().dis;
		heap.pop();
		if (vis[u]) continue;
		if (!u) return !printf("%d",dist);
		d[u]=dist;		
		vis[u]=1;
		for (i=last[u];i;i=next[i]){
			if (!vis[to[i]]) heap.push((Edge){to[i],dist+w[i]});
		}
	}
} 
