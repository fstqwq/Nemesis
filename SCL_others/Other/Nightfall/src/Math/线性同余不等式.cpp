// Find the minimal non-negtive solutions for $ l \leq d \cdot x \bmod m \leq r $
// $0 \leq d, l, r < m; l \leq r, O(\log n)$
LL cal(LL m, LL d, LL l, LL r) {
	if (l==0) return 0; if (d==0) return MXL; // 无解
	if (d * 2 > m) return cal(m, m - d, m - r, m - l);
	if ((l - 1) / d < r / d) return (l - 1) / d + 1;
	LL k = cal(d, (-m % d + d) % d, l % d, r % d);
	return k==MXL ? MXL : (k*m + l - 1)/d+1;}// 无解 2
// return all x satisfying l1<=x<=r1 and l2<=(x*mul+add)%LIM<=r2
// here LIM = 2^32 so we use UI instead of "%".
// $O(\log p + #solutions)$
struct Jump { UI val, step;
	Jump(UI val, UI step) : val(val), step(step) { }
	Jump operator + (const Jump & b) const {
		return Jump(val + b.val, step + b.step); }
	Jump operator - (const Jump & b) const {
		return Jump(val - b.val, step + b.step); }};
inline Jump operator * (UI x, const Jump & a) {
	return Jump(x * a.val, x * a.step); }
vector<UI> solve(UI l1, UI r1, UI l2, UI r2, pair<UI,UI> muladd) {
	UI mul = muladd.first, add = muladd.second, w = r2 - l2;
	Jump up(mul, 1), dn(-mul, 1); UI s(l1 * mul + add);
	Jump lo(r2 - s, 0), hi(s - l2, 0);
	function<void(Jump&, Jump&)> sub=[&](Jump& a, Jump& b){
		if (a.val > w) {
			UI t(((LL)a.val-max(0LL, w+1LL-b.val)) / b.val);
			a = a - t * b; } };
	sub(lo, up), sub(hi, dn);
	while (up.val > w || dn.val > w) {
		sub(up, dn); sub(lo, up);
		sub(dn, up); sub(hi, dn); }
	assert(up.val + dn.val > w); vector<UI> res;
	Jump bg(s + mul * min(lo.step, hi.step), min(lo.step, hi.step));
	while (bg.step <= r1 - l1) {
		if (l2 <= bg.val && bg.val <= r2)
			res.push_back(bg.step + l1);
		if (l2 <= bg.val-dn.val && bg.val-dn.val <= r2) {
			bg = bg - dn;
		} else bg = bg + up; }
	return res; }
