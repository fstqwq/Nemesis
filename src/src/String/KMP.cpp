void kmp(char *s, int n) { // 1-based
	fail[0] = fail[1] = 0;
	for (int i = 1; i < n; i++) { int j = fail[i];
		while (j && s[i + 1] != s[j + 1]) j = fail[j];
		if (s[i + 1] == s[j + 1]) fail[i + 1] = j + 1;
		else fail[i + 1] = 0; } }
void exkmp(char *s, int *a, int n) { // 1-based
	int l = 0, r = 0; a[1] = n;
	for (int i = 2; i <= n; i++) {
		a[i] = i > r ? 0 : min(r - i + 1, a[i - l + 1]);
		while (i+a[i] <= n && s[1+a[i]] == s[i+a[i]]) a[i]++;
		if (i + a[i] - 1 > r) {l = i; r = i + a[i] - 1;}}}