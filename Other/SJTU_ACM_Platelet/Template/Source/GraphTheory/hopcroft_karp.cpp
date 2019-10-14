int BFS()
{
	int flag = 0, h = 0, l = 0;
	for(int i = 1; i <= k; i++)
		dy[i] = 0;
	for(int i = 1; i <= n; i++)
	{
		dx[i] = 0;
		if(!matx[i])q[++l] = i;
	}
	while(h < l)
	{
		int x = q[++h];
		for(int i = son[x]; i; i = edge[i].next)
		{
			int y = edge[i].y;
			if(!dy[y])
			{
				dy[y] = dx[x] + 1;
				if(!maty[y])flag = 1;
				else
				{
					dx[maty[y]] = dx[x] + 2;
					q[++l] = maty[y];
				}
			}
		}
	}
	return flag;
}

int DFS(int x)
{
	for(int i = son[x]; i; i = edge[i].next)
	{
		int y = edge[i].y;
		if(dy[y] == dx[x] + 1)
		{
			dy[y] = 0;
			if(!maty[y] || DFS(maty[y]))
			{
				matx[x] = y, maty[y] = x;
				return 1;
			}
		}
	}
	return 0;
}

void Hopcroft()
{
	for(int i = 1; i <= n; i++)
		matx[i] = maty[i] = 0;
	while(BFS())
		for(int i = 1; i <= n; i++)
			if(!matx[i])DFS(i);
}
