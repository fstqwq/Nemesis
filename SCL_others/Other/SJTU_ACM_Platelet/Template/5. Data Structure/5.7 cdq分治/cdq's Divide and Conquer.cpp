//
//  Title : cdq 分治
//  Date : 18.04.2016
//  Test : BZOJ-1176
//  Complexity : O(nlog^2n)
//  
/*
	对于三维偏序等问题——
	解决办法：离线询问，分治降维，剩下一维用随便什么树乱搞。这样就不用写树套树啦！
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
#define maxn 200010
#define maxm 2000010
struct event
{
	int x, y, pos, opet, ans;
	inline bool operator < (const event &that) const {return pos < that.pos ;}
}t[maxn], q[maxn];
#define lowbit(_x) ((_x) & -(_x))
int bit[maxm], last[maxm], s, w, cnt, now;
inline void add(R int x, R int val)
{
	for (; x <= w; x += lowbit(x))
	{
		if (last[x] != now)
			bit[x] = 0;
		bit[x] += val;
		last[x] = now;
	}
}
inline int query(R int x)
{
	R int ans = 0;
	for (; x ; x -= lowbit(x))
	{
		if (last[x] == now)
			ans += bit[x];
	}
	return ans;
}
void cdq(R int left, R int right)
{
	if (left == right) return ;
	R int mid = left + right >> 1;
	cdq(left, mid); cdq(mid + 1, right);
	//分成若干个子问题
	++now;
	for (R int i = left, j = mid + 1; j <= right; ++j)
	{
		for (; i <= mid && q[i].x <= q[j].x; ++i)
			if (!q[i].opet)
				add(q[i].y, q[i].ans);
		//考虑前面的修改操作对后面的询问的影响
		if (q[j].opet)
			q[j].ans += query(q[j].y);
	}
	R int i, j, k = 0;
	//以下相当于归并排序
	for (i = left, j = mid + 1; i <= mid && j <= right; )
	{
		if (q[i].x <= q[j].x)
			t[k++] = q[i++];
		else
			t[k++] = q[j++];
	}
	for (; i <= mid; )
		t[k++] = q[i++];
	for (; j <= right; )
		t[k++] = q[j++];
	for (R int i = 0; i < k; ++i)
		q[left + i] = t[i];
}
int main()
{
//	setfile();
	s = FastIn();
	w = FastIn();
	while (1)
	{
		R int opt = FastIn();
		if (opt == 1)
		{
			R int x = FastIn(), y = FastIn(), a = FastIn();
			q[++cnt] = (event){x, y, cnt, 0, a};
		}
		if (opt == 2)
		{
			R int x = FastIn() - 1, y = FastIn() - 1, a = FastIn(), b = FastIn();
			q[++cnt] = (event) {x, y, cnt, 1, x * y * s};
			q[++cnt] = (event) {a, b, cnt, 2, a * b * s};
			q[++cnt] = (event) {x, b, cnt, 2, x * b * s};
			q[++cnt] = (event) {a, y, cnt, 2, a * y * s};
		}
		if (opt == 3) break;
	}
	cdq(1, cnt);
	std::sort(q + 1, q + cnt + 1);
	for (R int i = 1; i <= cnt; ++i)
		if (q[i].opet == 1)
			printf("%d\n",q[i].ans + q[i + 1].ans - q[i + 2].ans - q[i + 3].ans ), i += 3;
	return 0;
}
