// height[i] = lcp(sa[i], sa[i - 1])
// 如果有多组数据，全部都清空到 max(n, m)
constexpr int MAXN = 1000005;
void get_sa(char *s, int n, int *sa,
		int *rnk, int *height) { // 1-based
	static int buc[MAXN], id[MAXN], p[MAXN], t[MAXN];
	int m = 300;
	for (int i = 1; i <= n; i++) buc[rnk[i] = s[i]]++;
	for (int i = 1; i <= m; i++) buc[i] += buc[i - 1];
	for (int i = n; i; i--) sa[buc[rnk[i]]--] = i;
	memset(buc, 0, sizeof(int) * (m + 1));
	for (int k = 1, cnt = 0; cnt != n; k *= 2, m = cnt) {
		cnt = 0;
		for (int i = n; i > n - k; i--) id[++cnt] = i;
		for (int i = 1; i <= n; i++)
			if (sa[i] > k) id[++cnt] = sa[i] - k;
		for (int i = 1; i <= n; i++) buc[p[i]=rnk[id[i]]]++;
		for (int i = 1; i <= m; i++) buc[i] += buc[i - 1];
		for (int i = n; i; i--) sa[buc[p[i]]--] = id[i];
		memset(buc, 0, sizeof(int) * (m + 1));
		memcpy(t, rnk, sizeof(int) * (n + 1));
		t[n + 1] = 0; // 记得清空 n + 1
		cnt = 0; for (int i = 1; i <= n; i++) {
			if (t[sa[i]] != t[sa[i - 1]] ||
				t[sa[i] + k] != t[sa[i - 1] + k]) cnt++;
			rnk[sa[i]] = cnt; } }
	for (int i = 1; i <= n; i++) sa[rnk[i]] = i;
	for (int i = 1, k = 0; i <= n; i++) { if (k) k--;
		if (rnk[i] > 1) while (sa[rnk[i] - 1] + k <= n &&
				s[i + k] == s[sa[rnk[i] - 1] + k]) k++;
		height[rnk[i]] = k; } } // 两个都要判，否则会左/右越界
char s[MAXN]; int sa[MAXN], rnk[MAXN], height[MAXN];
int main() { scanf("%s", s + 1); int n = strlen(s + 1);
	get_sa(s, n, sa, rnk, height); }
