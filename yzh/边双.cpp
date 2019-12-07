/* 
 * Edge Bi-connected Component
 * Check: hihoCoder 1184
 */

int n, m;
int head[MAXN], nxt[MAXM << 1], to[MAXM << 1], ed;
// Opposite edge exists, set head[] to -1.

int dfn[MAXN], low[MAXN], bcc_id[MAXN], bcc_cnt, stamp;
bool isbridge[MAXM << 1], vis[MAXN];

std::vector<int> bcc[MAXN];

void Tarjan(int now, int fa) {
	dfn[now] = low[now] = ++stamp;
	for (int i = head[now]; ~i; i = nxt[i]) {
		if (!dfn[to[i]]) {
			Tarjan(to[i], now);
			low[now] = std::min(low[now], low[to[i]]);
			if (low[to[i]] > dfn[now])
				isbridge[i] = isbridge[i ^ 1] = 1;
		}
		else if (dfn[to[i]] < dfn[now] && to[i] != fa)
			low[now] = std::min(low[now], dfn[to[i]]);
	}
}

void DFS(int now) {
	vis[now] = 1;
	bcc_id[now] = bcc_cnt;
	bcc[bcc_cnt].push_back(now);
	for (int i = head[now]; ~i; i = nxt[i]) {
		if (isbridge[i]) continue;
		if (!vis[to[i]]) DFS(to[i]);
	}
}

void EBCC() {
	memset(dfn, 0, sizeof dfn);
	memset(low, 0, sizeof low);
	memset(isbridge, 0, sizeof isbridge);
	memset(bcc_id, 0, sizeof bcc_id);
	bcc_cnt = stamp = 0;
	
	for (int i = 1; i <= n; ++i)
		if (!dfn[i]) Tarjan(i, 0);
	
	memset(vis, 0, sizeof vis);
	for (int i = 1; i <= n; ++i)
		if (!vis[i]) {
			++bcc_cnt;
			DFS(i);
		}
}
