/** 边双 **/
int n, m, head[N], nxt[M << 1], to[M << 1], ed;
int dfn[N], low[N], bcc_id[N], bcc_cnt, stp;
bool bri[M << 1], vis[N];
vector<int> bcc[N];
void tar(int now, int last) {
	dfn[now] = low[now] = ++stp;
	for (int i = head[now], d; i; i = h[i].next) {
		d = h[i].node;
		if (!dfn[d]) {
			tar(d, i);
			low[now] = min(low[now], low[d]);
			if (low[d] > dfn[now])
				bri[i] = bri[i ^ 1] = 1; }
		else if (dfn[d] < dfn[now] && ((i ^ 1) != last))
			low[now] = min(low[now], dfn[d]); } }
void DFS(int now) {
	vis[now] = 1;
	bcc_id[now] = bcc_cnt;
	bcc[bcc_cnt].push_back(now);
	for (int i = head[now], d; i; i = h[i].node) {
		d = h[i].node;
		if (bri[i]) continue;
		if (!vis[d]) DFS(d); } }
void EBCC() {// clear dfn low bri bcc_id vis
	bcc_cnt = stp = 0;
	for (int i = 1; i <= n; ++i) if (!dfn[i]) tar(i, 0);
	for (int i = 1; i <= n; ++i)
		if (!vis[i]) ++bcc_cnt, DFS(i); }
/** 建立圆方树+求割点 **/
int is_cut[N], DFN[N], low[N], cnt;
int stk[N], dep; // clear dfn low is_cut cnt, let pcnt=n
void tarjan(int x, int fa) {
    int child = 0;
    DFN[x] = low[x] = ++cnt; stk[++dep] = x;
    #define head org
    for (int i = head[x], d; i; i = h[i].next) {
        d = h[i].node;
        if (!DFN[d]) { ++child; tarjan(d, x);
            low[x] = std::min(low[x], low[d]);
            if (low[d] >= DFN[x]) {
                is_cut[x] = true;
                ++pcnt; // square node index
                int j = 0, sz = 1;
                do {
                    j = stk[dep--];
                    addedge(pcnt, j, tr);
                    ++sz;
                } while (j != d);
                addedge(pcnt, x, tr);
        }   } else if (DFN[d] < low[x]) {
            low[x] = DFN[d]; } }
    #undef head
    if (!fa && child == 1) is_cut[x] = false;}