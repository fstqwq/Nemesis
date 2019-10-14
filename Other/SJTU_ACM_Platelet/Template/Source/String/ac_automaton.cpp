struct Trie {
	Trie *next[26], *fail;
	int end;
} mem[maxn * maxl], *tot = mem, *q[maxn * maxl];
char s[maxl];
inline void insert(int v)
{
	Trie *now = mem; int n = strlen(s + 1);
	for (int i = 1; i <= n; ++i)
	{
		int v = s[i] - 'a';
		if (!now -> next[v])
		{
			now -> next[v] = ++tot;
			for (int i = 0; i < 26; ++i) tot -> next[i] = 0;
			tot -> fail = 0;
			tot -> end = 0;
		}
		now = now -> next[v];
	}
	now -> end |= v;
}
inline void build()
{
	int head = 0, tail = 0;
	for (int i = 0; i < 26; ++i)
		if (mem -> next[i]) (q[++tail] = mem -> next[i]) -> fail = mem;
		else mem -> next[i] = mem;
	while (head < tail)
	{
		Trie *now = q[++head];
		now -> end |= now -> fail -> end;
		for (int i = 0; i < 26; ++i)
			if (!now -> next[i])
				now -> next[i] = now -> fail -> next[i];
			else
				(q[++tail] = now -> next[i]) -> fail = now -> fail -> next[i];
	}
}
