#include <cstdio>
#include <cmath>
 
#define R register
 
inline int qpow(R int base, R int power, R int mod)
{
	R int ret = 1;
	for (; power; power >>= 1, base = 1ll * base * base % mod)
		power & 1 ? ret = 1ll * ret * base % mod : 0;
	return ret;
}
const int mod = 19260817;
struct Hash
{
	Hash *next;
	int key, val;
} *last[mod], mem[100000], *tot = mem;
inline void insert(R int x, R int v)
{
	*++tot = (Hash) {last[x % mod], x, v}; last[x % mod] = tot;
}
inline int query(R int x)
{
	for (R Hash *iter = last[x % mod]; iter; iter = iter -> next)
		if (iter -> key == x) return iter -> val;
	return -1;
}
inline void del(R int x)
{
	last[x % mod] = 0;
}
int main()
{
	for (; T; --T)
	{
		R int y, z, p; scanf("%d%d%d", &y, &z, &p);
		R int m = (int) sqrt(p * 1.0);
		y %= p; z %= p;
		if (!y && !z) {puts("0"); continue;}
		if (!y) {puts("Orz, I cannot find x!"); continue;}
		R int pw = 1;
		for (R int i = 0; i < m; ++i, pw = 1ll * pw * y % p) insert(1ll * z * pw % p, i);
		R int ans = -1;
		for (R int i = 1, t, pw2 = pw; i <= p / m + 1; ++i, pw2 = 1ll * pw2 * pw % p)
			if ((t = query(pw2)) != -1) {ans = i * m - t; break;}
		if (ans == -1) puts("Orz, I cannot find x!");
		else printf("%d\n", ans );
		tot = mem; pw = 1;
		for (R int i = 0; i < m; ++i, pw = 1ll * pw * y % p) del(1ll * z * pw % p);
	}
	return 0;
}
/*
find min x : y^x = z(mod p)
*/
