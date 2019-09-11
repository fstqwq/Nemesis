void spfa(int *dist) {
    static int line[maxn + 5];
    static bool hash[maxn + 5];
    int f = 0, r = 0;

    for(int i = 1; i <= n; i++)
    	if(dist[i] < inf) {
    		line[r] = i;
    		hash[i] = true;
    		r = (r + 1) % (n + 1);
    	}

    while(f != r) {
        int u = line[f];
        
        hash[u] = false;
        f = (f + 1) % maxn;
        for(int i = head[u]; i ; i = edge[i].next) {
            int v = edge[i].v;
            int w = edge[i].w;
           
            if(dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                if(!hash[v]) {
                    if(dist[v] < dist[line[f]]) {
                    	f = (f - 1 + maxn) % maxn;
                    	line[f] = v;
                    }
                    else {
                    	line[r] = v;
                    	r = (r + 1) % maxn;
                    }
                    hash[v] = true;
                }
            }
        }
    }
}
void solve()
{
    for(int i = 1; i <= S; i++) {
        for(int j = 1; j <= N; j++)
            for(int k = (i - 1) & i; k ; k = (k - 1) & i) {
            	f[i][j] = std::min(f[i][j], f[k][j] + f[k ^ i][j]);
            }
        
        spfa(f[i]);
    }
}
