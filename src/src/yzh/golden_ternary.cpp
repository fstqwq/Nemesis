constexpr R = (sqrt(5) - 1) / 2;
auto split = [](LD l, LD r) { return l + (r - l) * R; };
LD solve(LD a, LD c, auto f) {
	LD b = split(a, b), bv = f(b);
	for (int _ = T; _; _--) {
		LD x = split(a, b), xv = f(x);
		if (xv > bv) c = b, b = x, bv = xv;
		else a = c, c = x;
	} return bv; }