struct blossom{

	struct Edge{
		int x, y, next;
	}edge[M];

	int n, W, tot, h, l, son[N];
	int mat[N], pre[N], tp[N], q[N], vis[N], F[N];

	void Prepare(int n_)
	{
		n = n_;
		W = tot = 0;
		for(int i = 1; i <= n; i++)
			son[i] = mat[i] = vis[i] = 0;
	}

	void add(int x, int y)
	{
		edge[++tot].x = x; edge[tot].y = y; edge[tot].next = son[x]; son[x] = tot;
	}

	int find(int x)
	{
		return F[x] ? F[x] = find(F[x]) : x;
	}

	int lca(int u, int v)
	{
		for(++W;; u = pre[mat[u]], swap(u, v))
			if(vis[u = find(u)] == W)return u;
			else vis[u] = u ? W : 0;
	}

	void aug(int u, int v)
	{
		for(int w; u; v = pre[u = w])
			w = mat[v], mat[mat[u] = v] = u;
	}

	void blo(int u, int v, int f)
	{
		for(int w; find(u) ^ f; u = pre[v = w])
			pre[u] = v, F[u] ? 0 : F[u] = f, F[w = mat[u]] ? 0 : F[w] = f, tp[w] ^ 1 ? 0 : tp[q[++l] = w] = -1;
	}

	int bfs(int x)
	{
		for(int i = 1; i <= n; i++)
			tp[i] = F[i] = 0;
		h = l = 0;
		q[++l] = x;
		tp[x]--;
		while(h < l)
		{
			x = q[++h];
			for(int i = son[x]; i; i = edge[i].next)
			{
				int y = edge[i].y, Lca;
				if(!tp[y])
				{
					if(!mat[y])return aug(y, x), 1;
					pre[y] = x, ++tp[y], --tp[q[++l] = mat[y]];
				}
				else if(tp[y] ^ 1 && find(x) ^ find(y))
					blo(x, y, Lca = lca(x, y)), blo(y, x, Lca);
			}
		}
		return 0;
	}

	int solve()
	{
		int ans = 0;
		for(int i = 1; i <= n; i++)
			if(!mat[i])ans += bfs(i);
		return ans;
	}
}G;
