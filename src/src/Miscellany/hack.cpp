//fast = O3 + ffast-math + fallow-store-data-races
#pragma GCC optimize("Ofast")
#pragma GCC target("sse2,abm,fma,mmx,avx2,tune=native")
const int SZ = 1 << 16; int getc() {
	static char buf[SZ], *ptr = buf, *top = buf;
	if (ptr == top) {
		ptr = buf, top = buf + fread(buf, 1, SZ, stdin);
		if (top == buf) return -1; }
	return *ptr++; }
idx=b._Find_first();idx!=b.size();idx=b._Find_next(idx);
struct HashFunc{size_t operator()(const KEY &key)const{}};
__builtin_uaddll_overflow(a, b, &c) // binary big int
void GospersHack(int k, int n) {
	for (int s = (1 << k) - 1, c, r; s < (1 << n);
	c = s & -s, r = s + c, s = (((r ^ s) >> 2) / c) | r); }