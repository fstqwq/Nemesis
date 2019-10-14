//
//  Title:ZKW Segment Tree
//  Date:19.11.2015
//  Complexity:
//    Build Tree:O(N)
//    Query:O(logN)
//    Change:O(logN)
/*
    区间内动态修改和查询 
	算法实现：线段树
	ZKW线段树：非递归！！！ 
*/

#include<cstdio>
#include<cmath>
#define maxn 100000
#define R register
int T[1<<18|1],n,m,M;

inline int FastIn()
{
	R char ch=getchar();R int cnt=0;R bool minus=0;
	while ((ch<'0'||ch>'9')&&ch!='-') ch=getchar();
	if (ch=='-') minus=1,ch=getchar();
	while (ch>='0'&&ch<='9') cnt=cnt*10+ch-'0',ch=getchar();
	return minus?-cnt:cnt;
}

inline void Build_Tree()
{
	for (R int i=M-1;i>=1;i--)
	  T[i]=T[2*i]+T[2*i+1];
} 

inline int Query(int s,int t)
{
    R int Ans;
	for (Ans=0,s=s+M-1,t=t+M+1;s^t^1;s>>=1,t>>=1)
	{
		if (~s&1) Ans+=T[s^1];
		if (t&1) Ans+=T[t^1];
	}
	return Ans;
}

inline void Change(int x,int NewValue)
{
	R int i=M+x;
	for (T[i]=NewValue,i>>=1;i;i>>=1)
	  T[i]=T[2*i]+T[2*i+1];
}

int main()
{
	n=FastIn();m=FastIn();
	for (M=1;M<=n;M<<=1);
	for (R int i=0;i<n;i++)
	  T[M+i]=FastIn();
	Build_Tree();
	for (R int i=1;i<=m;i++)
	{
		R char cmd=getchar();
		if (cmd=='Q')
		{
			R int a=FastIn()-1,b=FastIn()-1;
			printf("%d\n",Query(a,b)); 
		}
		if (cmd=='M')
		{
			R int a=FastIn()-1,b=FastIn();
			Change(a,b);
		}
	}
	return 0;
} 
