vector <array <int, 3>> tri;
void solve () {
	list <int> l;
	for (int k = 0; k < n; k++) l.push_back(k);
	auto check = [&](auto u, auto v, auto w) {
		if (turn(u, v, w) <= 0) return false;
		for (auto i : l)
			if (turn(u, v, p[i]) == 1 &&
			    turn(v, w, p[i]) == 1 &&
			    turn(w, u, p[i]) == 1) return false;
		return true; };
	for (auto it = l.begin(); l.size() > 3; ) {
		auto u = (it == l.begin() ? prev(l.end()) : prev(it));
		auto v = (next(it) == l.end() ? l.begin() : next(it));
		if (!check(p[*u], p[*it], p[*v])) it = v;
		else {
			tri.push_back({*u, *it, *v});
			l.erase(it);
			it = u; } }
	tri.push_back({l.front(), *next(l.begin()), l.back()}); }
