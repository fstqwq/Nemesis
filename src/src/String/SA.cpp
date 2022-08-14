// height[i] = lcp(sa[i], sa[i - 1])
void get_sa(char *s, int n, int *sa,
		int *rnk, int *height) { // 1-based
	static int buc[maxn], id[maxn], p[maxn], t[maxn * 2];
	int m = 300;
	for (int i = 1; i <= n; i++) buc[rnk[i] = s[i]]++;
	for (int i = 1; i <= m; i++) buc[i] += buc[i - 1];
	for (int i = n; i; i--) sa[buc[rnk[i]]--] = i;
	memset(buc, 0, sizeof(int) * (m + 1));
	for (int k = 1, cnt; cnt != n; k *= 2, m = cnt) {
		cnt = 0;
		for (int i = n; i > n - k; i--) id[++cnt] = i;
		for (int i = 1; i <= n; i++)
			if (sa[i] > k) id[++cnt] = sa[i] - k;
		for (int i = 1; i <= n; i++) buc[p[i]=rnk[id[i]]]++;
		for (int i = 1; i <= m; i++) buc[i] += buc[i - 1];
		for (int i = n; i; i--) sa[buc[p[i]]--] = id[i];
		memset(buc, 0, sizeof(int) * (m + 1));
		memcpy(t, rnk, sizeof(int) * (max(n, m) + 1));
		cnt = 0; for (int i = 1; i <= n; i++) {
			if (t[sa[i]] != t[sa[i - 1]] ||
				t[sa[i] + k] != t[sa[i - 1] + k]) cnt++;
			rnk[sa[i]] = cnt; } }
	for (int i = 1; i <= n; i++) sa[rnk[i]] = i;
	for (int i = 1, k = 0; i <= n; i++) { if (k) k--;
		while (s[i + k] == s[sa[rnk[i] - 1] + k]) k++;
		height[rnk[i]] = k; } }
char s[maxn]; int sa[maxn], rnk[maxn], height[maxn];
int main() { cin >> (s + 1); int n = strlen(s + 1);
	get_sa(s, n, sa, rnk, height);
	for (int i = 1; i <= n; i++)
		cout << sa[i] << (i < n ? ' ' : '\n');
	for (int i = 2; i <= n; i++)
		cout << height[i] << (i < n ? ' ' : '\n');
	return 0; }