bool bfs() {
  memcpy(cur, head, sizeof cur);
  memset(dep, 0x3f, sizeof dep);
  dep[S] = 0; std::queue<int> q; q.push(S);
  while (!q.empty()) {
    int x = q.front(); q.pop();
    for (int i = head[x], d; i; i = e[i].nxt) {
      d = e[i].v;
      if (e[i].f > 0 && (h[d] == h[x] + e[i].w)
      && (dep[d] > dep[x] + 1)) {
        dep[d] = dep[x] + 1;
        q.push(d);
  } } } return dep[T] < INF;
}

int dfs(int x, int lim) {
  if (x == T || !lim) return lim;
  int f = 0, flow = 0;
  for (int i = cur[x], d; i && lim; i = e[i].nxt) {
    cur[x] = i; d = e[i].v; if (d == S) continue;
    if ((dep[d] == dep[x] + 1) && h[e[i].v] == e[i].w + h[x] 
    && (f = dfs(d, std::min(lim, e[i].f)))) {
      e[i].f -= f; e[i ^ 1].f += f;
      flow += f; lim -= f;
  } } return flow;
}

std::pair<int, int> solve() {
  // return <flow, cost>
  int res = 0, flow = 0;
  for (int i = 0; i <= T; ++i) h[i] = 0;
  int first = true;
  while (true) {
    std::priority_queue<pii, std::vector<pii>,
    std::greater<pii>> q;
    memset(dis, 0x3f, sizeof dis);
    memset(vis, 0, sizeof vis); dis[S] = 0;
    if (first) { // Run SPFA or topo sort
      std::vector<int> tmpq; tmpq.push_back(S);
      for (int i = 1; i <= n + n; ++i)
        tmpq.push_back(i);
      dis[S] = 0;
      for (auto x : tmpq) {
        for (int i = head[x], d; i; i = e[i].nxt) {
          d = e[i].v;
          if (e[i].f) {
            dis[d] = std::min(dis[d], dis[x] + e[i].w);
      } } } first = false;
    } else { q.push(pii(0, S));
      while (!q.empty()) {
        pii now = q.top(); q.pop(); int x = now.second;
        if (dis[x] < now.first) continue;
        for (int o = head[x]; o; o = e[o].nxt) {
          int w = dis[x] + e[o].w + h[x] - h[e[o].v];
          if (e[o].f > 0 && dis[e[o].v] > w) {
            dis[e[o].v] = w; q.push(pii(w, e[o].v));
    } } } }
    if (dis[T] >= INF) break;
    for (int i = 0; i <= T; ++i) h[i] += dis[i];
    int fl = 0; while (bfs())  fl += dfs(S, 1e9);
    res += fl * h[T]; flow += fl;
  } return std::make_pair(flow, res);
}
