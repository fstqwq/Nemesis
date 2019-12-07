int mx[N], my[N], tag[N];
vector<int> E[N]; 
bool dfs(int x) {
	for (auto y : E[x]) {
        int w = my[y];
        if (w == -1 || tag[x] + 1 == tag[w] && dfs(w)) {
            mx[x] = y; my[y] = x;
            return true;
        }
    }
    tag[x] = -1;
    return false;
}
int solve() {
    memset(mx, -1, sizeof(int) * n);
    memset(my, -1, sizeof(int) * m);
    for (int ans = 0; ; ) {
        vector<int> q;
        for (int i = 0; i < n; ++i) {
            if (mx[i] == -1) {
                tag[i] = 0;
                q.push_back(i);
            } else tag[i] = -1;
        }
        for (int h = 0; h < (int)q.size(); ++h) {
            int x = q[h];
			for (auto y : E[x]) {
                int w = my[y];
                if (w != -1 && tag[w] < 0) {
                    tag[w] = tag[x] + 1;
                    q.push_back(w);
                }
            }
        }
        int d = 0;
        for (int i = 0; i < n; ++i)
            if (mx[i] == -1 && dfs(i)) ++d;
        if (d == 0) return ans; else ans += d;
    }
}
