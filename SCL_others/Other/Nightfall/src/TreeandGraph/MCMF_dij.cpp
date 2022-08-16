
const LL INF = 1e18; struct Edge { LL f, c; int to, r; };
vector<Edge> G[N]; LL d[N]; bool fst = true;
int S, T, prv[N], prp[N], cur[N], vst[N];
bool SPFA(int S) {
	if(fst) { fst = 0;
		// 此处为第一次求最短路, 可 Dij 就和下面一样, 不可就 SPFA 或根据图性质 DP
		return d[T] != INF; }
	fill(d + 1, d + 1 + T, INF); // 此处为 Dij
	priority_queue<pair<LL,int>> pq; pq.push({0,S}); d[S]=0;
	while(1) {
		while(!pq.empty() && -pq.top().first != d[pq.top().second]) pq.pop();
		if(pq.empty()) break;
		int v(pq.top().second); pq.pop(); int cnt(0);
		for (Edge e : G[v]) {
			if (e.f && d[e.to] > d[v] + e.c) {
				d[e.to] = d[v] + e.c; prv[e.to] = v;
				prp[e.to]=cnt; pq.push({-d[e.to], e.to}); }
			cnt++; } }
	return d[T] != INF; }
LL aug(int v, LL flow) {
	if(v == T) return flow; vst[v] = 1; LL flow1(flow);
	for(int & i(cur[v]); i < (int)G[v].size(); i++) {
		Edge & e = G[v][i];
		if(e.f && d[v] + e.c == d[e.to] && !vst[e.to]) {
			LL flow1(aug(e.to, min(flow, e.f)));
			flow-=flow1; e.f-=flow1; G[e.to][e.r].f += flow1; }
		if(flow == 0) { vst[v] = 0; return flow1 - flow; } }
	return flow1 - flow; }
LL mcmf() { LL ans = 0, sT = 0;
	while (SPFA(S)) { sT += d[T]; // 多路增广
		for(int i(1); i <= T; i++) cur[i] = 0, vst[i] = 0;
		ans += sT * aug(S, INF);
		for(int i(1); i <= T; i++)
			for(auto & e : G[i]) e.c += d[i] - d[e.to];}
	return ans; }
void add(int u, int v, int f, int c) {
	G[u].push_back({f, c, v, (int) G[v].size()});
	G[v].push_back({0, -c, u, (int) G[u].size() - 1}); }
int main() { // 初始化 S, T, T 编号最大, 1base
	// add(x, y, cap, cost)
	LL ans = mcmf(); }