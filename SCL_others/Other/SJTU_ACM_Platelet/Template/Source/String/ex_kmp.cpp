int next[maxn], extend[maxn], fail[maxn];
void getnext(R char *s, R int len)
{
	fail[1] = 0;
	R int p = 0;
	memset(next, 0, (len + 2) << 2);
	for (R int i = 2; i <= len; ++i)
	{
		while (p && s[p + 1] != s[i]) p = fail[p];
		s[p + 1] == s[i] ? ++p : 0;
		fail[i] = p;
		p ? cmax(next[i - p + 1], p) : 0;
	}
}
void getextend(R char *s, R int lens, R char *t, R int lent)
{
	getnext(t, lent);
	R int a = 1, p = 0;
 
	for (R int i = 1; i <= lens; ++i)
	{
		if (i + next[i - a + 1] - 1 >= p)
		{
			cmax(p, i - 1);
			while (p < lens && p - i + 1 < lent && s[p + 1] == t[p - i + 2]) ++p;
			a = i;
			extend[i] = p - i + 1;
		}
		else extend[i] = next[i - a + 1];
	}
}
