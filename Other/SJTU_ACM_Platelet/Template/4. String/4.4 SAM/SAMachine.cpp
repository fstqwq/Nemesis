//
//  Title : SAMachine
//  Date : 10.03.2016
//  Test : CODEVS-3160
//  Complexity : O(n)
//  
/*
	对于子串匹配/处理等问题——
	解决办法：后缀自动机
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
#define maxn 250010
char str[maxn] ;
int ans ;
struct SAM
{
	int p , np , q , nq;
	int cnt , last;
	int a[maxn][26] , l[maxn] , fa[maxn];
	SAM()
	{
		last=++cnt;
	}
	void extend(R int c)
	{
		p = last ;	// p表示添加前的最后一个状态
		np = last = ++cnt;	// np表示当前的状态
		l[np] = l[p] + 1;	// 当前的长度为上一个状态的长度+1
		for (; !a[p][c] && p ; ) a[p][c] = np , p = fa[p] ;	// 如果p的fail指针的trie边没有被占用，那么就将其trie边连到np上
		if (!p) fa[np] = 1 ;	// 如果当前这单个字符没有出现过，那么就把当前状态的fail指针设为1（init,初始状态）
		else	// 如果p的fail指针被占用了，那么就————
		{
			q = a[p][c];	// q表示被占用掉的那个状态
			if (l[p] + 1 == l[q] ) fa[np] = q;	// 如果这个状态刚好是当前状态的上一个字符的状态，那么就意味着出现了两个相同的字符，此时就直接将fail指针建到q上
			else	// 否则就
			{
				nq = ++cnt ;	// 新建一个节点
				l[nq] = l[p] + 1 ;	// 新建的这个节点将会的长度等于当前状态的长度
				memcpy (a[nq] , a[q] , sizeof (a[q]) );	// 将当前占用掉的那个状态的trie边连到新的节点上
				fa[nq] = fa[q] ;	// 新建节点的fail指针指向上一个状态
				fa[np] = fa[q] = nq ;	// 当前的节点和被占用的节点的fail指针指向新的节点
				while (a[p][c] == q) a[p][c] = nq , p = fa[p] ;	// 把所有trie边指向q的点的trie边连向nq
			}
		}
	}
	void build()
	{
		scanf( "%s\n" , str );
		for (R int i = 0 ; str[i] ; i++ ) extend ( str[i] - 'a' ) ;
	}
	void solve()
	{
		scanf( "%s\n" , str );
		R int tmp = 0;
		for (R int i = 0 ; str[i] ; i++ )
		{
			R int c = str[i] - 'a';
			if ( a[p][c] ) p = a[p][c] , tmp ++ ;
			else
			{
				for ( ; p && !a[p][c] ; ) p = fa[p] ;
				if (!p) p = 1 ,tmp = 0;
				else tmp = l[p] + 1 , p = a[p][c];
			}
			cmax( ans , tmp );
		}
		printf("%d\n",ans );
	}
}sam;
int main()
{
	sam.build();
	sam.solve();
	return 0;
}

