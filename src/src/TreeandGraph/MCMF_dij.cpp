pii solve() {
	LL res = 0, flow = 0; 
	for (int i = S; i <= T; i++) h[i] = 0;
	while (true) {// first time may SPFA
		priority_queue <pii, vector<pii>, greater<pii>> q;
		for (int i = S; i <= T; i++) dis[i] = INF;
		dis[S] = 0; q.push(pii(0, S));
		while (!q.empty()) {
			pii now = q.top(); q.pop(); int x = now.second;
			if (dis[x] < now.first) continue;
			for (int o = head[x]; o; o = e[o].nxt) {
				if (e[o].f > 0 && dis[e[o].v] > dis[x] + e[o].w + h[x] - h[e[o].v]) {
					 dis[e[o].v] = dis[x] + e[o].w + h[x] - h[e[o].v];
					 prevv[e[o].v] = x; pree[e[o].v] = o;
					 q.push(pii(dis[e[o].v], e[o].v)); } } }
		if (dis[T] == INF) break;
		for (int i = S; i <= T; i++) h[i] += dis[i];
		int d = INF;
		for (int v = t; v != S; v = prevv[v]) d = min(d, e[pree[v]].f);
		flow += d; res += (LL)d * h[t];
		for (int v = t; v != S; v = prevv[v]) {
			e[pree[v]].f -= d; e[pree[v] ^ 1].f += d; } }
	return make_pair(flow, res); }
