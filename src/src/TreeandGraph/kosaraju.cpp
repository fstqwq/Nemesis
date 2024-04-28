bitset<N> e[N], re[N], vis; vector<int> sta;
void dfs0(int x, bitset<N> e[]) {
	vis.reset(x);
	while (true) {
		int go = (e[x] & vis)._Find_first();
		if(go == N) break;
		dfs0(go, e); }
	sta.push_back(x); }
vector<vector<int>> solve() { // re 需要连好反向边
	vis.set();
	for(int i = 1;i <= n;++i) if(vis.test(i)) dfs0(i, e);
	vis.set();
	auto s = sta;
	vector<vector<int>> ret;
	for(int i = n - 1;i >= 0;--i) if(vis.test(s[i])) {
		sta.clear(), dfs0(s[i], re), ret.push_back(sta); }
	return ret; }