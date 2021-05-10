#define root 0
struct SAM{
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

struct ST_SA{
    int e[N << 2][26];
    int lst, cur, link[N << 2], len[N << 2], sufid[N], left[N << 2], occur[N << 2], cnt;
    int tr[N << 2][26];//ST的带字符转移.卡空间时直接用vector再排序.  
    void extend(char c, int id){
        c-='a';
        lst = cur, cur = ++cnt;
        len[cur] = len[lst]+1, left[cur] = occur[cur] = id, sufid[id] = cur; 
        int u = lst, v;
        while(u!=-1 && !e[u][c]) e[u][c] = cur, u = link[u];
        if (u == -1) {link[cur] = root; return;} 
        v=e[u][c]; if (len[v] == len[u]+1) {link[cur] = v; return;} 
        int clone = ++cnt; len[clone] = len[u]+1, link[clone] = link[v],
        memcpy(e[clone], e[v], sizeof e[v]);
        link[v] = link[cur] = clone;
        for (; u!=-1 && e[u][c]==v; u=link[u]) e[u][c] = clone;
    }
    void buildST(const string& s){
        for (int i = 0; i <= s.size() * 4; i++)
            left[i] = occur[i] = 0, memset(e[i], 0, sizeof e[i]), memset(tr[i], 0, sizeof tr[i]);
        cnt = 0; link[root] = -1, cur = root; 
        for (int i = s.size() - 1; i >= 0; i--) extend(s[i], i + 1);
        for (int i = cnt; i; i--) if (!occur[link[i]]) occur[link[i]] = occur[i];
        for (int i = cnt; i; i--){
            int L = len[link[i]];
            tr[link[i]][s[occur[i] + L - 1] - 'a'] = i; } }

    int sa[N], rank[N], height[N], num, minlen;
    void dfs(int u){
        if (left[u]){
            if (!num) height[++num] = len[u];
            else height[++num] = minlen;
            rank[num] = left[u]; minlen = len[u]; }
        for (int i = 0; i < 26; i++) if (tr[u][i]){
                dfs(tr[u][i]); minlen = min(minlen, len[u]); } }
    void buildSA(const string& s){
        num = minlen = 0, dfs(root);
        for (int i = 1; i <= s.size(); i++) sa[rank[i]] = i; } };
