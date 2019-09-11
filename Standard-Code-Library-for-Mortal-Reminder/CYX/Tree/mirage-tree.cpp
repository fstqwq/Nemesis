bool cmp(const int lhs,const int rhs) { return dfn[lhs] < dfn[rhs]; }
void build()
{
	int top = 0;
	std::sort(h + 1, h + 1 + m, cmp);
	for(int i = 1; i <= m; i++) t[++tot] = h[i];
	for(int i = 1; i <= m; i++) {
		if (!top) father[st[++top] = h[i]] = 0;
		else {
		    int p = h[i], lca = LCA(h[i],st[top]);
		    while(d[st[top]] > d[lca]) {
		        if (d[st[top - 1]] <= d[lca]) father[st[top]] = lca;
		        top--;
		    }
		    if (st[top] != lca) t[++tot] = lca, father[lca] = st[top], st[++top] = lca;
		    father[p] = lca, st[++top] = p;
		}
	}
}
