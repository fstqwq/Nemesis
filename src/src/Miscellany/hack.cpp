//fast = O3 + ffast-math + fallow-store-data-races
#pragma GCC optimize("Ofast")
#pragma GCC target("lzcnt,popcnt")
const int SZ = 1 << 16;
int getc() {
	static char buf[SZ], *ptr = buf, *top = buf;
	if (ptr == top) {
		ptr = buf, top = buf + fread(buf, 1, SZ, stdin);
		if (top == buf) return -1; }
	return *ptr++; }
bitset._Find_first();bitset._Find_next(idx);
struct HashFunc{size_t operator()(const KEY &key)const{}};
