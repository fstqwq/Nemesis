/** 边双 **/
int n, m, head[N], nxt[M << 1], to[M << 1], ed;
int dfn[N], low[N], bcc_id[N], bcc_cnt, stp;
bool bri[M << 1], vis[N];
vector<int> bcc[N];
void Tarjan(int now, int fa) {
	dfn[now] = low[now] = ++stp;
	for (int i = head[now]; ~i; i = nxt[i]) {
		if (!dfn[to[i]]) {
			Tarjan(to[i], now);
			low[now] = min(low[now], low[to[i]]);
			if (low[to[i]] > dfn[now])
				bri[i] = bri[i ^ 1] = 1; }
		else if (dfn[to[i]] < dfn[now] && to[i] != fa)
			low[now] = min(low[now], dfn[to[i]]); } }
void DFS(int now) {
	vis[now] = 1;
	bcc_id[now] = bcc_cnt;
	bcc[bcc_cnt].push_back(now);
	for (int i = head[now]; ~i; i = nxt[i]) {
		if (bri[i]) continue;
		if (!vis[to[i]]) DFS(to[i]); } }
void EBCC() {// clear dfn low bri bcc_id vis
	bcc_cnt = stp = 0;
	for (int i = 1; i <= n; ++i) if (!dfn[i]) Tarjan(i, 0);
	for (int i = 1; i <= n; ++i)
		if (!vis[i]) ++bcc_cnt, DFS(i); }
/** 点双 **/
vector<int> G[N],bcc[N];
int dfn[N], low[N], bcc_id[N], bcc_cnt, stp;
bool iscut[N]; pii stk[N]; int top;
void Tarjan(int now, int fa) {
	int child = 0;
	dfn[now] = low[now] = ++stp;
	for (int to: G[now]) {
		if (!dfn[to]) {
			stk[++top] = mkpair(now, to); ++child;
			Tarjan(to, now);
			low[now] = min(low[now], low[to]);
			if (low[to] >= dfn[now]) {
				iscut[now] = 1;
				bcc[++bcc_cnt].clear();
				while (1) {
					pii tmp = stk[top--];
					if (bcc_id[tmp.first] != bcc_cnt) {
						bcc[bcc_cnt].push_back(tmp.first);
						bcc_id[tmp.first] = bcc_cnt; }
					if (bcc_id[tmp.second] != bcc_cnt) {
						bcc[bcc_cnt].push_back(tmp.second);
						bcc_id[tmp.second] = bcc_cnt; }
					if (tmp.first == now && tmp.second == to)
						break; } } }
		else if (dfn[to] < dfn[now] && to != fa) {
			stk[++top] = mkpair(now, to);
			low[now] = min(low[now], dfn[to]); } }
	if (!fa && child == 1) iscut[now] = 0; }
void PBCC() { // clear dfn low iscut bcc_id
	stp = bcc_cnt = top = 0;
	for (int i = 1; i <= n; ++i) if (!dfn[i]) Tarjan(i, 0); }
		
