/* 
 * Point Bi-connected Component
 * Check: VALLA 5135
 */

typedef std::pair<int, int> pii;
#define mkpair std::make_pair

int n, m;
std::vector<int> G[MAXN];

int dfn[MAXN], low[MAXN], bcc_id[MAXN], bcc_cnt, stamp;
bool iscut[MAXN];

std::vector<int> bcc[MAXN]; // Unnecessary

pii stk[MAXN]; int stk_top;
// Use a handwritten structure to get higher efficiency

void Tarjan(int now, int fa) {
	int child = 0;
	dfn[now] = low[now] = ++stamp;
	for (int to: G[now]) {
		if (!dfn[to]) {
			stk[++stk_top] = mkpair(now, to); ++child;
			Tarjan(to, now);
			low[now] = std::min(low[now], low[to]);
			if (low[to] >= dfn[now]) {
				iscut[now] = 1;
				bcc[++bcc_cnt].clear();
				while (1) {
					pii tmp = stk[stk_top--];
					if (bcc_id[tmp.first] != bcc_cnt) {
						bcc[bcc_cnt].push_back(tmp.first);
						bcc_id[tmp.first] = bcc_cnt;
					}
					if (bcc_id[tmp.second] != bcc_cnt) {
						bcc[bcc_cnt].push_back(tmp.second);
						bcc_id[tmp.second] = bcc_cnt;
					}
					if (tmp.first == now && tmp.second == to)
						break;
				}
			}
		}
		else if (dfn[to] < dfn[now] && to != fa) {
			stk[++stk_top] = mkpair(now, to);
			low[now] = std::min(low[now], dfn[to]);
		}
	}
	if (!fa && child == 1)
		iscut[now] = 0;
}

void PBCC() {
	memset(dfn, 0, sizeof dfn);
	memset(low, 0, sizeof low);
	memset(iscut, 0, sizeof iscut);
	memset(bcc_id, 0, sizeof bcc_id);
	stamp = bcc_cnt = stk_top = 0;
	
	for (int i = 1; i <= n; ++i)
		if (!dfn[i]) Tarjan(i, 0);
}
