struct Sam{
	Sam *fa, *go[26];
	int val;
	
	void clear()
	{
		fa = 0;
		val = 0;
		memset(go, 0, sizeof(go));
	}
}*now, *root, *last, *cur, Pool[N << 1];

void Prepare()
{
	cur = Pool;
	cur -> clear();
	root = last = cur;
}

Sam *Insert(Sam *last, int now)
{
	Sam *p = last;
	if(p -> go[now])
	{
		Sam *q = p -> go[now];
		if(q -> val == p -> val + 1)return q;
		Sam *nt = ++cur;
		nt -> clear();
		nt -> val = p -> val + 1;
		memcpy(nt -> go, q -> go, sizeof(q -> go));
		nt -> fa = q -> fa;
		q -> fa = nt;
		while(p && p -> go[now] == q)p -> go[now] = nt, p = p -> fa;
		return nt;
	}
	Sam *np = ++cur;
	np -> clear();
	np -> val = p -> val + 1;
	while(p && !p -> go[now])p -> go[now] = np, p = p -> fa;
	if(!p)np -> fa = root;
	else
	{
		Sam *q = p -> go[now];
		if(q -> val == p -> val + 1)
		{
			np -> fa = q;
		}
		else
		{
			Sam *nt = ++cur;
			nt -> clear();
			nt -> val = p -> val + 1;
			memcpy(nt -> go, q -> go, sizeof q -> go);
			nt -> fa = q -> fa;
			q -> fa = nt;
			np -> fa = nt;
			while(p && p -> go[now] == q)p -> go[now] = nt, p = p -> fa;
		}
	}
	return np;
}
