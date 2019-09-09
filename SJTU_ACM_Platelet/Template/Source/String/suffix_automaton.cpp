struct SAM {
	SAM *next[26], *fa;
	int val;
} mem[maxn], *last = mem, *tot = mem;
void extend(int c)
{
	R SAM *p = last, *np;
	last = np = ++tot; np -> val = p -> val + 1;
	for (; p && !p -> next[c]; p = p -> fa) p -> next[c] = np;
	if (!p) np -> fa = rt[id];
	else
	{
		SAM *q = p -> next[c];
		if (q -> val == p -> val + 1) np -> fa = q;
		else
		{
			SAM *nq = ++tot;
			memcpy(nq -> next, q -> next, sizeof nq -> next);
			nq -> val = p -> val + 1;
			nq -> fa = q -> fa;
			q -> fa = np -> fa = nq;
			for (; p && p -> next[c] == q; p = p -> fa) p -> next[c] = nq;
		}
	}
}
