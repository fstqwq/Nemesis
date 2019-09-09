//
//  Title: 树链剖分 for LCA
//  Date: 23.12.2015
//  Test:YZOJ-1345
//  Complexity:
//      dfs:O(n)
//      getLCA:O(logn)
//      total:O(n+mlogn)
//
/*
    树链剖分才是LCA最正统的写法。
    出题人为了卡倍增，增加树高，甚至不惜构造链。但树高越高，划分成的链越少！链的情况下，树剖是O（1）的！
    所以就愉悦极了！——CJK
*/
#include <cstdio>
#define R register
#define maxn 100010
//#define getc() (S==T&&(T=(S=B)+fread(B,1,1<<15,stdin),S==T)?EOF:*S++)
#define getc() getchar()
int to[maxn],last[maxn],next[maxn],cnt;
int top[maxn],fa[maxn],son[maxn],size[maxn],depth[maxn],n;
char B[1<<15],*S=B,*T=B;
inline int FastIn(){
	R char ch=getc();R int cnt=0;
	while (ch<'0'||ch>'9') ch=getc();
	while (ch>='0'&&ch<='9') cnt=cnt*10+ch-'0',ch=getc();
	return cnt;
}
void dfs1(int x)
{
	depth[x]=depth[fa[x]]+1;size[x]=1;
	for (R int i=last[x];i;i=next[i])
	{
		R int pre=to[i];
		fa[pre]=x;
		dfs1(pre);
		size[x]+=size[pre];
		size[son[x]]<size[pre]?son[x]=pre:0;
	}
}
void dfs2(int x)
{
	x==son[fa[x]]?top[x]=top[fa[x]]:top[x]=x;
	for (R int i=last[x];i;i=next[i]) dfs2(to[i]);
}
int getLCA(int a,int b)
{
	while (top[a]!=top[b])
	  depth[top[a]]>depth[top[b]]?a=fa[top[a]]:b=fa[top[b]];
	return depth[a]>depth[b]?b:a;
}
#define add(a,b) to[++cnt]=b,next[cnt]=last[a],last[a]=cnt
int main()
{
	n=FastIn();R int i,a,b,Q=FastIn();
	for (i=1;i<n;i++) a=FastIn(),b=FastIn(),add(a,b);
	dfs1(1);dfs2(1);
	for (;Q;Q--)
	{
		a=FastIn();b=FastIn();
		printf("%d\n",getLCA(a,b));
	}
}
