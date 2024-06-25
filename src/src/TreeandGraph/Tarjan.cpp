/** 求割边 **/
// 注意！建立边双树或者圆方树后【边表大小】是否开够
// 求边双：无视掉 bri 后搜出每个连通块，记得多测
int DFN[N], low[N], dfscnt; // clear DFN low bri dfscnt
bool bri[M << 1]; // 注意此处是边数
void tarjan(int x, int last) { // last 是边
	DFN[x] = low[x] = ++dfscnt;
	for (int i = head[x], d; i; i = h[i].next) {
		d = h[i].node;
		if (!DFN[d]) {
			tarjan(d, i);
			low[x] = min(low[x], low[d]);
			if (low[d] > DFN[x]) bri[i] = bri[i ^ 1] = 1;
		} else if (DFN[d] < DFN[x] && ((i ^ 1) != last))
			low[x] = min(low[x], DFN[d]); } }
/** 建立圆方树+求割点 **/
int is_cut[N], DFN[N], low[N], dfscnt, pcnt;
int stk[N], dep; // clear DFN low is_cut dfscnt, let pcnt=n
void tarjan(int x, int fa) {
	int child = 0;
	DFN[x] = low[x] = ++dfscnt; stk[++dep] = x;
	#define head org // org 是原图表头，tr 是圆方树表头
	for (int i = head[x], d; i; i = h[i].next) {
		d = h[i].node;
		if (!DFN[d]) {
			++child; tarjan(d, x);
			low[x] = min(low[x], low[d]);
			if (low[d] >= DFN[x]) {
				is_cut[x] = true;
				++pcnt; // square node index
				int j = 0, sz = 1;
				do {
					j = stk[dep--];
					addedge(pcnt, j, tr);
					++sz;
				} while (j != d);
				addedge(pcnt, x, tr); }
		} else if (DFN[d] < low[x]) low[x] = DFN[d]; }
	#undef head
	if (!fa && child == 1) is_cut[x] = false; }