//
// Title : KMP
// Date : 13.01.2016
// Complexity : O(n)
// Test : YZOJ-1677
/*
	匹配一个串是否是另一个串的子串。
	算法实现：KMP
	时间是均摊O（n）。
	以下是KMP的预处理，即p[i]表示在1～i的字符串中，1～p[i]既是1～i的前缀，又是1～i的后缀。预处理就是一个自我匹配的过程。
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
#define maxn 400010
char s[maxn];
int p[maxn], ans[maxn];
int main()
{
	while (scanf("%s\n", s + 1) != EOF)
	{
		R int i, j, len = 1, cnt = 0;
		for (i = 2, j = 0; s[i]; ++i, ++len)
		{
			for ( ; j && s[j + 1] != s[i]; j = p[j]) ;
			s[i] == s[j + 1] ? ++j : 0;
			p[i] = j;
		}//预处理！！！
		for (i = len; i; i = p[i]) ans[++cnt] = i;
		for (i = cnt; i; i--) printf("%d ", ans[i] );
		puts("");
	}
	return 0;
}
