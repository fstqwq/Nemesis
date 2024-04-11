using B = bitset<N>; B edge[N];
bool dfs(int x, B& unvis, vector<int>& match) {
	for(B z = edge[x];;) {
		z &= unvis;
		int y = z._Find_first();
		if(y == N) return 0;
		unvis.reset(y);
		if(!match[y] || dfs(match[y], unvis, match))
			return match[y] = x, 1; } }
vector<int> match(int nl, int nr) {
	B unvis; unvis.set();
	vector<int> match(nr + 1), ret(nl + 1);
	for(int i = 1;i <= nl;++i)
		if(dfs(i, unvis, match)) unvis.set();
	for(int i = 1;i <= nr;++i) ret[match[i]] = i;
	return ret[0] = 0, ret; }