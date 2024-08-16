struct hull { // upper hull, left to right
set <point> a; LL tot;
hull () {tot = 0;}
LL calc(auto it) {
	auto u = it == a.begin() ? a.end() : prev(it);
	auto v = next(it);
	LL ret = 0;
	if (u != a.end()) ret += det(*u, *it);
	if (v != a.end()) ret += det(*it, *v);
	if (u != a.end() && v != a.end()) ret -= det(*u, *v);
	return ret; }
void insert (point p) {
	if (!a.size()) { a.insert (p); return; }
	auto it = a.lower_bound (p);
	bool out;
	if (it == a.begin()) out = (p < *it); // special case
	else if (it == a.end()) out = true;
	else out = turn(*prev(it), *it, p) > 0;
	if (!out) return;
	while (it != a.begin()) {
		auto o = prev(it);
		if (o == a.begin() || turn(*prev(o), *o, p) < 0) break;
		else erase(o); }
	while (it != a.end()) {
		auto o = next(it);
		if (o == a.end() || turn(p, *it, *o) < 0) break;
		else erase(it), it = o; }
	tot += calc(a.insert(p).first); }
void erase(auto it) { tot -= calc(it); a.erase(it); } };