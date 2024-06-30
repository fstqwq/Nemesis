// n为串长, 回文半径输出到p数组中，数组要开串长的两倍
void manacher(const char *t, int n) {
	static char s[MAXN * 2];
	for (int i = n; i; i--) s[i * 2] = t[i];
	for (int i = 0; i <= n; i++) s[i * 2 + 1] = '#';
	s[0] = '$'; s[(n + 1) * 2] = '\0'; n = n * 2 + 1;
	int mx = 0, j = 0;
	for (int i = 1; i <= n; i++) {
		p[i] = (mx > i ? min(p[j * 2 - i], mx - i) : 1);
		while (s[i - p[i]] == s[i + p[i]]) p[i]++;
		if (i + p[i] > mx) { mx = i + p[i]; j = i; } } }
