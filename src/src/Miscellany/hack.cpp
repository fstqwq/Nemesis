#define __ __attribute__ ((optimize ("-O3"))) 
#define _ __ __inline __attribute__ ((__gnu_inline__, __always_inline__, __artificial__)) 
const int BS = 16 << 20;
char buf[BS], *ptr = buf, *top = buf;
__inline int my() {
	if (ptr == top) {
		ptr = buf;
		if ((top = buf + fread(buf, 1, BS, stdin)) == buf) return -1; }
	return *ptr++; }
bitset._Find_first();bitset._Find_next(idx);
struct HashFunc{size_t operator()(const KEY &key)const{}};
