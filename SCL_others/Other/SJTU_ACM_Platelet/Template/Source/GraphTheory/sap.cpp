void SAP(int n, int st, int ed)
{
	for(int i = 1; i <= n; i++)
		now[i] = son[i];
	sumd[0] = n;
	int flow = inf, x = st;
	while(dis[st] < n)
	{
		back[x] = flow;
		int flag = 0;
		for(int i = now[x]; i != -1; i = edge[i].next)
		{
			int y = edge[i].y;
			if(edge[i].f && dis[y] + 1 == dis[x])
			{
				flag = 1;
				now[x] = i;
				pre[y] = i;
				flow = min(flow, edge[i].f);
				x = y;
				if(x == ed)
				{
					ans += flow;
					while(x != st)
					{
						edge[pre[x]].f -= flow;
						edge[pre[x] ^ 1].f += flow;
						x = edge[pre[x]].x;
					}
					flow = inf;
				}
				break;
			}
		}
		if(flag)continue;
		int minn = n - 1, tmp;
		for(int i = son[x]; i != -1; i = edge[i].next)
		{
			int y = edge[i].y;
			if(edge[i].f && dis[y] < minn)
			{
				minn = dis[y];
				tmp = i;
			}
		}
		now[x] = tmp;
		if(!(--sumd[dis[x]]))return;
		sumd[dis[x] = minn + 1]++;
		if(x != st)flow = back[x = edge[pre[x]].x];
	}
}
