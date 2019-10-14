namespace Game {
#define maxn 300010
#define maxs 30010
uint b1[32][maxs], b2[32][maxs];
int popcnt[256];
inline void set(R uint *s, R int pos)
{
	s[pos >> 5] |= 1u << (pos & 31);
}
inline int popcount(R uint x)
{
	return popcnt[x >> 24 & 255]
		 + popcnt[x >> 16 & 255]
		 + popcnt[x >> 8  & 255]
		 + popcnt[x 	  & 255];
}
void main() {
	int n, q;
	scanf("%d%d", &n, &q);
 
	char *s1 = new char[n + 1];
	char *s2 = new char[n + 1];
	scanf("%s%s", s1, s2);
 
	uint *anss = new uint[q];
 
	for (R int i = 1; i < 256; ++i) popcnt[i] = popcnt[i >> 1] + (i & 1);
 
	#define modify(x, _p)\
	{\
		for (R int j = 0; j < 32 && j <= _p; ++j)\
			set(b##x[j], _p - j);\
	}
	for (R int i = 0; i < n; ++i)
		if (s1[i] == '0') modify(1, 3 * i)
		else if (s1[i] == '1') modify(1, 3 * i + 1)
		else modify(1, 3 * i + 2)
 
	for (R int i = 0; i < n; ++i)
		if (s2[i] == '1') modify(2, 3 * i)
		else if (s2[i] == '2') modify(2, 3 * i + 1)
		else modify(2, 3 * i + 2)
 
	for (int Q = 0; Q < q; ++Q) {
		R int x, y, l;
		scanf("%d%d%d", &x, &y, &l); x *= 3; y *= 3; l *= 3;
		uint *f1 = b1[x & 31], *f2 = b2[y & 31], ans = 0;
		R int i = x >> 5, j = y >> 5, p, lim;
		for (p = 0, lim = l >> 5; p + 8 < lim; p += 8, i += 8, j += 8)
		{
			ans += popcount(f1[i + 0] & f2[j + 0]);
			ans += popcount(f1[i + 1] & f2[j + 1]);
			ans += popcount(f1[i + 2] & f2[j + 2]);
			ans += popcount(f1[i + 3] & f2[j + 3]);
			ans += popcount(f1[i + 4] & f2[j + 4]);
			ans += popcount(f1[i + 5] & f2[j + 5]);
			ans += popcount(f1[i + 6] & f2[j + 6]);
			ans += popcount(f1[i + 7] & f2[j + 7]);
		}
		for (; p < lim; ++p, ++i, ++j) ans += popcount(f1[i] & f2[j]);
		R uint S = (1u << (l & 31)) - 1;
		ans += popcount(f1[i] & f2[j] & S);
		anss[Q] = ans;
	}
 
	output_arr(anss, q * sizeof(uint));
}
}
