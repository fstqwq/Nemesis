#define root 0
struct SAM_tbr{
    int e[N << 2][26];
    int lst, cur, link[N << 2], len[N << 2], cnt;
    bool isleaf[N << 2];
    void init(){
        memset(isleaf, 0, sizeof isleaf),
        memset(e, 0, sizeof e); cnt = 0;
        link[root] = -1, cur = root; }
    void extend(int c){
        c-='a', lst = cur, cur = ++cnt;
        len[cur] = len[lst]+1, isleaf[cur] = 1; 
        int u = lst, v;
        while(u!=-1 && !e[u][c]) e[u][c] = cur, u = link[u];
        if (u == -1) {link[cur] = root; return;} 
        v=e[u][c];
        if (len[v] == len[u]+1) {link[cur] = v; return;} 
        int clone = ++cnt;
        len[clone] = len[u]+1, link[clone] = link[v],
        memcpy(e[clone], e[v], sizeof e[v]);
        link[v] = link[cur] = clone;
        for (; u!=-1 && e[u][c]==v; u=link[u]) e[u][c] = clone; } };
struct SAM_yzh {
struct State {
	vector <int> E;
	int v[L]; int len, fa, pos; bool au;
} t[N * 2];
int tcnt, p;
SAM () {tcnt = 1; p = 1; t[1].len = t[1].fa = 0; t[1].au = 1;}
void add(int c, int k) {
	int cur = ++tcnt;
	t[cur].pos = k; t[cur].len = t[p].len + 1;
	while (p && !t[p].v[c])
		t[p].v[c] = cur, p = t[p].fa;
	if (!p) t[cur].fa = 1;
	else {
		int q = t[p].v[c];
		if (t[p].len + 1 == t[q].len) t[cur].fa = q;
		else {
			int r = ++tcnt;
			t[r] = t[q];
			t[r].au = 1; t[r].len = t[p].len + 1;
			while (p && t[p].v[c] == q)
				t[p].v[c] = r, p = t[p].fa;
			t[q].fa = t[cur].fa = r;
	} } p = cur; }
void dfs(int cur) {
	if (!t[cur].au) printf("%d ", 1 + t[cur].pos);
	for (auto &v : t[cur].E) dfs(v); }
void make() {
	vector < pair<int, int> > Edges;
	for (int i = 2; i <= tcnt; i++) 
		Edges.push_back({s[t[i].pos + t[t[i].fa].len], i});
	sort(Edges.begin(), Edges.end());
	for (auto &v : Edges) 
		t[t[v.second].fa].E.push_back(v.second);
	dfs(1); }
} sam;

