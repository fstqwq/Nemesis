template<class TAT>void checkmax(TAT &x,TAT y) { if(x < y) x = y; }
template<class TAT>void checkmin(TAT &x,TAT y) { if(y < x) x = y; }
void getsize(int u,int fa) {
	size[u] = 1, smax[u] = 0;
	for(int i = 0; i < G[u].size(); i++) {
		int v = G[u][i];
		if(v == fa || ban[v]) continue;
		getsize(v, u);
		size[u] += size[v];
		checkmax(smax[u], size[v]);
	}
}
int getroot(int u,int ts,int fa) {
	int res = u;
	checkmax(smax[u], ts - size[u]);
	for(int i = 0; i < G[u].size(); i++) {
		int v = G[u][i];
		if(v == fa || ban[v]) continue;
		int w = getroot(v, ts, u);
		if(smax[w] < smax[res]) res = w;
	}
	return res;
}
void solve() {
	static int line[maxn];
	static std::vector<int> vec;
	int f = 0, r = 0; line[r++] = 1;
	while(f != r) {
		int u = line[f++];
		getsize(u, 0), u = getroot(u, size[u], 0);
		ban[u] = true, vec.clear();
		for(int i = 0; i < G[u].size(); i++)
			if(!ban[G[u][i]]) vec.push_back(G[u][i]);
		/*
		do something you like...
		*/
		for(int i = 0; i < vec.size(); i++) line[r++] = vec[i];
	}
}
