bool SPFA() {
    static int line[maxv];
    static bool hash[maxv];
    register int f = 0, r = 0;
	for(int i = 1; i <= ind; i++) dist[i] = inf, from[i] = 0;
    dist[S] = 0, line[r] = S, r = (r + 1) % maxv, hash[S] = true;
    while(f != r) {
        int x = line[f];
        line[f] = 0, f = (f + 1) % maxv, hash[x] = false;
        for(int i = head[x]; i; i = edge[i].next)
            if(edge[i].cap) {
                int v = edge[i].v, w = dist[x] + edge[i].cost;
                if(w < dist[v]) {
                    dist[v] = w, from[v] = i;
                    if(!hash[v]) {
                        if(f != r && dist[v] <= dist[line[f]]) f = (f - 1 + maxv) % maxv, line[f] = v;
                        else line[r] = v, r = (r + 1) % maxv;
                        hash[v] = true;
                    }
                }
            }
    }
    return from[T];
}
int back(int x,int flow) {
	if(from[x]) {
		flow = back(edge[from[x] ^ 1].v, std::min(flow, edge[from[x]].cap));
		edge[from[x]].cap -= flow, edge[from[x] ^ 1].cap += flow;
	}
	return flow;
}
int solve() {
    int mincost = 0, maxflow = 0;
    while(SPFA()) {
        int flow = back(T, inf);
        mincost += dist[T] * flow, maxflow += flow;
    }
    return mincost;
}


