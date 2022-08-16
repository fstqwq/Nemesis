//
//  Title : 广义后缀自动机
//  Date : 12.06.2016
//  Test : BZOJ-3277
//  Complexity : O(n)
//  
/*
	对于多串的子串匹配等问题——
	解决办法：广义后缀自动机（后缀树）
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
	#define setfile() 
#else
	#define debug(...)
	#define filename ""
	#define setfile() freopen(filename".in", "r", stdin); freopen(filename".out", "w", stdout);
#endif

#define R register
#define getc() (S == T && (T = (S = B) + fread(B, 1, 1 << 15, stdin), S == T) ? EOF : *S++)
#define dmax(_a, _b) ((_a) > (_b) ? (_a) : (_b))
#define dmin(_a, _b) ((_a) < (_b) ? (_a) : (_b))
#define cmax(_a, _b) (_a < (_b) ? _a = (_b) : 0)
#define cmin(_a, _b) (_a > (_b) ? _a = (_b) : 0)
char B[1 << 15], *S = B, *T = B;
inline int FastIn()
{
	R char ch; R int cnt = 0; R bool minus = 0;
	while (ch = getc(), (ch < '0' || ch > '9') && ch != '-') ;
	ch == '-' ? minus = 1 : cnt = ch - '0';
	while (ch = getc(), ch >= '0' && ch <= '9') cnt = cnt * 10 + ch - '0';
	return minus ? -cnt : cnt;
}
#define maxn 100010
struct sam
{
	sam *next[26], *fa;
	int val, last_vis, c;
	bool vis;
	long long sum;
}mem[maxn << 1], *tot = mem;
inline sam *extend(R sam *p, R int c)
{
	if (p -> next[c])
	{
		R sam *q = p -> next[c];
		if (q -> val == p -> val + 1)
			return q;
		else
		{
			R sam *nq = ++tot;
			memcpy(nq -> next, q -> next, sizeof nq -> next);
			nq -> val = p -> val + 1;
			nq -> fa = q -> fa;
			q -> fa = nq;
			for ( ; p && p -> next[c] == q; p = p -> fa)
				p -> next[c] = nq;
			return nq;
		}
	}
	R sam *np = ++tot;
	np -> val = p -> val + 1;
	for ( ; p && !p -> next[c]; p = p -> fa) p -> next[c] = np;
	if (!p)
		np -> fa = mem;
	else
	{
		R sam *q = p -> next[c];
		if (q -> val == p -> val + 1)
			np -> fa = q;
		else
		{
			R sam *nq = ++tot;
			memcpy(nq -> next, q -> next, sizeof nq -> next);
			nq -> val = p -> val + 1;
			nq -> fa = q -> fa;
			q -> fa = np -> fa = nq;
			for ( ; p && p -> next[c] == q; p = p -> fa)
				p -> next[c] = nq;
		}
	}
	return np;
}
void get_ans(R sam *x)
{
	if (x == mem || x -> vis) return;
	x -> vis = 1; get_ans(x -> fa); x -> sum += x -> fa -> sum;
}
char str[maxn], tot_str[maxn];
int left[maxn], right[maxn];
int main()
{
	R int n, k;
	scanf("%d%d", &n, &k);
	R int tot_len = 0;
	for (R int i = 1; i <= n; ++i)
	{
		scanf("%s", str);
		R sam* x = mem;
		R int len = strlen(str);
		left[i] = tot_len;
		right[i] = tot_len = len + tot_len - 1; ++tot_len;
		memcpy(tot_str + left[i], str, len * sizeof(char));
		for (R int j = 0; j < len; ++j)
			x = extend(x, str[j] - 'a');
	}
	for (R int i = 1; i <= n; ++i)
	{
		R sam *x = mem, *t;
		for (R int j = left[i]; j <= right[i]; ++j)
		{
			x = x -> next[tot_str[j] - 'a'];
			for (t = x; t && t -> last_vis != i; t = t -> fa)
				t -> last_vis = i, t -> c++;
		}
	}
	for (R sam *iter = mem + 1; iter <= tot; ++iter)
		iter -> sum = iter -> c >= k ? iter -> val - iter -> fa -> val : 0;
	for (R sam *iter = mem + 1; iter <= tot; ++iter)
		get_ans(iter);
	for (R int i = 1; i <= n; ++i)
	{
		R sam *x = mem; R long long ans = 0;
		for (R int j = left[i]; j <= right[i]; ++j)
			x = x -> next[tot_str[j] - 'a'], ans += x -> sum;
		printf("%lld ", ans );
	}
	return 0;
}
/*
3 1
abc
a
ab
*/
