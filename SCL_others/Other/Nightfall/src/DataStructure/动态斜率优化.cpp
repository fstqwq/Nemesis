const LL is_query = - (1LL << 62);
struct Line { LL k, b; // kx + b
mutable function<const Line*()> succ;
bool operator < (const Line &rhs) const {
	if (rhs.b != is_query) return k < rhs.k;
	const Line* s = succ();
	if (!s) return 0; LL x = rhs.k;
	// 根据范围和有无 __int128 调整 是否使用 1.0L* 下同
	return 1.0L * b - s->b < 1.0L * (s->k - k) * x; } };
struct HullDynamic : public multiset<Line> {
bool bad(iterator y) {    // upper hull for maximum
	auto z = next(y); if (y == begin()) {
		if (z == end()) return 0;
		return y->k == z->k && y->b <= z->b; }
	auto x = prev(y);
	if (z == end()) return y->k == x->k && y->b <= x->b;
	return 1.0L * (x->b - y->b) * (z->k - y->k) >= 1.0L * (y->b - z->b) * (y->k - x->k); }
void insert_line(LL k, LL b) {
	auto y = insert({k, b});
	y->succ = [=]{return next(y) == end() ? 0 : &*next(y);};
	if (bad(y)) { erase(y); return; }
	while (next(y) != end() && bad(next(y))) erase(next(y));
	while (y != begin() && bad(prev(y))) erase(prev(y)); }
LL eval(LL x) { Line u = {x, is_query};
	auto l = *lower_bound(u); return l.k * x + l.b; }};