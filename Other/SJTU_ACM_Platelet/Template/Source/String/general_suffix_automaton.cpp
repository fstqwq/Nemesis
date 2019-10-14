struct sam {
	sam *next[26], *fa;
	int val;
} mem[maxn << 1], *tot = mem;
inline sam *extend(sam *p, int c)
{
	if (p -> next[c])
	{
		sam *q = p -> next[c];
		if (q -> val == p -> val + 1)
			return q;
		else
		{
			sam *nq = ++tot;
			memcpy(nq -> next, q -> next, sizeof nq -> next);
			nq -> val = p -> val + 1;
			nq -> fa = q -> fa;
			q -> fa = nq;
			for ( ; p && p -> next[c] == q; p = p -> fa)
				p -> next[c] = nq;
			return nq;
		}
	}
	sam *np = ++tot;
	np -> val = p -> val + 1;
	for ( ; p && !p -> next[c]; p = p -> fa) p -> next[c] = np;
	if (!p)
		np -> fa = mem;
	else
	{
		sam *q = p -> next[c];
		if (q -> val == p -> val + 1)
			np -> fa = q;
		else
		{
			sam *nq = ++tot;
			memcpy(nq -> next, q -> next, sizeof nq -> next);
			nq -> val = p -> val + 1;
			nq -> fa = q -> fa;
			q -> fa = np -> fa = nq;
			for ( ; p && p -> next[c] == q; p = p -> fa)
				p -> next[c] = nq;
		}
	}
	return np;
}
