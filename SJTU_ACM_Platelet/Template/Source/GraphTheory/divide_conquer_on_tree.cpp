int root, son[maxn], size[maxn], sum;
bool vis[maxn];
void dfs_root(int x, int fa)
{
	size[x] = 1; son[x] = 0;
	for (Edge *iter = last[x]; iter; iter = iter -> next)
	{
		if (iter -> to == fa || vis[iter -> to]) continue;
		dfs_root(iter -> to, x);
		size[x] += size[iter -> to];
		cmax(son[x], size[iter -> to]);
	}
	cmax(son[x], sum - size[x]);
	if (!root || son[x] < son[root]) root = x;
}
void dfs_chain(int x, int fa)
{
	/*
		write your code here.
	*/
	for (Edge *iter = last[x]; iter; iter = iter -> next)
	{
		if (vis[iter -> to] || iter -> to == fa) continue;
		dfs_chain(iter -> to, x);
	}
}
void calc(int x)
{
	for (Edge *iter = last[x]; iter; iter = iter -> next)
	{
		if (vis[iter -> to]) continue;
		dfs_chain(iter -> to, x);
		/*
			write your code here.
		*/
	}
}
void work(int x)
{
	vis[x] = 1;
	calc(x);
	for (Edge *iter = last[x]; iter; iter = iter -> next)
	{
		if (vis[iter -> to]) continue;
		root = 0;
		sum = size[iter -> to];
		dfs_root(iter -> to, 0);
		work(root);
	}
}
int main()
{
	root = 0; sum = n;
	dfs_root(1, 0);
	work(root);
	return 0;
}
