void tarjan(int u,int f) {
	low[u] = dfn[u] = ++df;
	for(int i = head[u]; i ; i = edge[i].next) {
		int v = edge[i].v;
		if(v == f) continue;
		if(!dfn[v]) {
			stack[++top] = i, tarjan(v, u);
			low[u] = std::min(low[u], low[v]);
			if(low[v] >= dfn[u]) {
				++tot;
				while(stack[top] != i) pbc[stack[top--]] = tot;
				pbc[stack[top--]] = tot;
			}
		}
		else if(dfn[v] < dfn[u]) {
			stack[++top] = i;
			low[u] = std::min(low[u], dfn[v]);
		}
	}
}
void work()
{
	for(int i = 1; i <= n; i++) if(!dfn[i]) tarjan(i, 0);
	for(int i = 1; i <= m; i++) pbc[i * 2 - 1] = pbc[i * 2] = std::max(pbc[i * 2 - 1], pbc[i * 2]);
}
