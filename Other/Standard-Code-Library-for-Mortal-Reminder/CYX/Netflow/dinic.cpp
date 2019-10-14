bool bfs() {
    for(int i = 1; i <= ind; i++) dep[i] = 0;
    
    dep[S] = 1, line.push(S);
    while(!line.empty()) {
        int u = line.front();
        line.pop();
        for(int i = head[u]; i ; i = edge[i].next) {
           	int v = edge[i].v;
            if(edge[i].cap && !dep[v])
                dep[v] = dep[u] + 1, line.push(v);
        }
    }

    if(dep[T]) {
        for(int i = 1; i <= ind; i++) cur[i] = head[i];
        return true;    
    }
    return false;
}
int dfs(int u,int flow) {
    if(u == T　|| flow == 0) return flow;
    int res = 0;
    for(int &i = cur[u]; i ; i = edge[i].next) {
    	int v = edge[i].v;
        if(dep[v] == dep[u] + 1 && edge[i].cap) {
            int det = DFS(v, std::min(flow, edge[i].cap));
            edge[i].cap -= det;
            edge[i ^ 1].cap += det;
            flow -= det, res += det;
            if(!flow) break;
        }
    }
	return res;
}
int solve() {
    int totflow = 0;
    while(bfs()) {
        totflow += dfs(S, inf);
    }
    return totflow;
}
