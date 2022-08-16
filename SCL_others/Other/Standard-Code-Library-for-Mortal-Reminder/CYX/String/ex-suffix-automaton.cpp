inline void add_node(int x, int &last) {
	int lastnode = last;
	if (c[lastnode][x]) {
		int nownode = c[lastnode][x];
		if (l[nownode] == l[lastnode] + 1) last = nownode;
		else {
			int auxnode = ++cnt; l[auxnode] = l[lastnode] + 1;
			for (int i = 0; i < alphabet; ++i) c[auxnode][i] = c[nownode][i];
			par[auxnode] = par[nownode]; par[nownode] = auxnode;
			for (; lastnode && c[lastnode][x] == nownode; lastnode = par[lastnode]) {
				c[lastnode][x] = auxnode;
			}
			last = auxnode;
		}
	} else {
		int newnode = ++cnt; l[newnode] = l[lastnode] + 1;
		for (; lastnode && !c[lastnode][x]; lastnode = par[lastnode]) c[lastnode][x] = newnode;
		if (!lastnode) par[newnode] = 1;
		else {
			int nownode = c[lastnode][x];
			if (l[lastnode] + 1 == l[nownode]) par[newnode] = nownode;
			else {
				int auxnode = ++cnt; l[auxnode] = l[lastnode] + 1;
				for (int i = 0; i < alphabet; ++i) c[auxnode][i] = c[nownode][i];
				par[auxnode] = par[nownode]; par[nownode] = par[newnode] = auxnode;
				for (; lastnode && c[lastnode][x] == nownode; lastnode = par[lastnode]) {
					c[lastnode][x] = auxnode;
				}
			}
		}
		last = newnode;
	}
}
