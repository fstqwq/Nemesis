//
//  Title: Shortest Path Faster Algorithm (SPFA)
//  Date:  29.11.2015
//  Complexity:
//      Time:  O(KE) K为所有顶点进队的平均次数，E为边数
//      Space: O(N+E)
//  Test：FZOJ-1127
/*
    已知一幅图G，求两点间的最短距离
	非常实用！！！ 
*/ 
#include<cstdio>
#include<cstring>
#include<queue>
#define maxn 23333
#define maxm 40000
#define R register
#define INF 23333
int d[maxn],n,m,s,t,last[maxn];
bool vis[maxm+10];
std::queue<int> q;

struct Edge{
	int w,to,next;
}e[maxm+10];//边表，w代表边权，to代表连接的另一端点，next代表这一端点的上一条边 

inline int FastIn()
{
	R char ch=getchar();R int cnt=0;
	while (ch<'0'||ch>'9') ch=getchar();
	while (ch>='0'&&ch<='9') cnt=cnt*10+ch-'0',ch=getchar();
	return cnt;
}

int main()
{
	n=FastIn();m=FastIn();s=FastIn();t=FastIn();
	R int i,x,y,c,head=0,tail=1;
	for (i=1;i<=m;i++)
	{
		 x=FastIn();y=FastIn();c=FastIn();
		 e[i]=(Edge){c,y,last[x]};
		 last[x]=i;
	}//建表（单向） 
	memset(d,INF,sizeof(d));
	d[s]=0;q.push(s);
	while (!q.empty())
	{
		x=q.front();q.pop() ;
		vis[x]=0;
		for (i=last[x];i;i=e[i].next)
		{
			if (d[e[i].to]>d[x]+e[i].w)
			{
				d[e[i].to]=d[x]+e[i].w;//如果有更优的解，那就更新这个端点的值 
				if (!vis[e[i].to)
				{
					q.push(e[i].to);//如果这个点不在队中就将这个端点入队 
					vis[e[i].to]=1;
				}
			}
		}
	}
	return !printf("%d",d[t]);
}
