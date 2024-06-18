bool bfs() {
  for (int i = S; i <= T; i++) cur[i] = head[i]; // S-T?
  for (int i = S; i <= T; i++) dep[i] = 0; // S-T?
  dep[S] = 1; queue<int> q; q.push(S);
  while (!q.empty()) {
    int x = q.front(); q.pop();
    for (int i = head[x]; i; i = e[i].nxt) {
      auto [nxt, v, w, f] = e[i];
      if (f && h[v] == h[x] + w && !dep[v]) {
        dep[v] = dep[x] + 1, q.push(v);
  } } } return !!dep[T]; }
int dfs(int x, int flow) {
  if (x == T) return flow;
  int used = 0, ret;
  for (int &i = cur[x]; i; i = e[i].nxt) {
    auto [nxt, v, w, f] = e[o];
    if (dep[v] == dep[x] + 1 && h[v] == h[x] + w
    && f && (ret = dfs(d, min(flow - used, f))) ) {
      e[i].f -= ret; e[i ^ 1].f += f; used += ret;
      if (flow == used) break;
  } } return used; }
typedef pair <value, int> pii; // Unusual!
pii solve() { // return {cost, flow}
  value cost = 0; int flow = 0;
  for (int i = S; i <= T; i++) h[i] = 0; // S-T?
  for (bool first = true; ; ) {
    priority_queue<pii, vector<pii>, greater<pii>> q;
    for (int i = S; i <= T; i++) dis[i] = INF_value; // S-T?
    dis[S] = 0;
    if (first) {
      // TODO: SSSP, Bellman-Ford / DP on DAG
      first = false;
    } else { q.push({0, S});
      while (!q.empty()) {
        auto [d, x] = q.top(); q.pop();
        if (dis[x] != d) continue;
        for (int o = head[x]; o; o = e[o].nxt) {
          value w = d + e[o].w + h[x] - h[e[o].v];
          if (e[o].f > 0 && dis[e[o].v] > w) {
            dis[e[o].v] = w; q.push({w, e[o].v});
    } } } } if (dis[T] >= INF_value) break;
    // 所有点必须可达, 否则加 h[i] += min(dis[i], dis[T]) 
    for (int i = S; i <= T; i++) h[i] += dis[i]; // S-T?
    int f = 0; while (bfs()) f += dfs(S, INF_int);
    cost += f * h[T]; flow += f;
  } return {cost, flow}; }