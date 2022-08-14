void kmp(const char *s, int *fail, int n) { // 1-based
	int j = fail[0] = 0;
	for (int i = 1; i <= n; i++) {
		while (j && s[i] != s[j]) j = fail[j - 1];
		fail[i] = (j += s[i] == s[j]); } }

void exkmp(const char *s, int *a, int n) { // 0-based
	int l = 0, r = 0; a[0] = n;
	for (int i = 1; i <= n; i++) {
		a[i] = i > r ? 0 : min(r - i + 1, a[i - l]);
		while (i+a[i] < n && s[a[i]] == s[i+a[i]]) a[i]++;
		if (i + a[i] - 1 > r) {l = i; r = i + a[i] - 1;}}}