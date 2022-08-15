#define __ __attribute__ ((optimize ("-O3"))) 
#define _ __ __inline __attribute__ ((__gnu_inline__, __always_inline__, __artificial__)) 
__inline int next_uint () {
	const int SIZE = 110000; static char buf[SIZE + 1]; static int p = SIZE;
	register int ans = 0, f = 1, sgn = 1;
	while ((p < SIZE || (p = 0, buf[fread (buf, 1, SIZE, stdin)] = 0, buf[0])) && (isdigit (buf[p]) && (ans = ans * 10 + buf[p] - '0', f = 0, 1) || f /* && (buf[p] == '-' && (sgn = 0), 1) */ )) ++p;
	return sgn ? ans : -ans; }
bitset._Find_first();bitset._Find_next(idx);
struct HashFunc{size_t operator()(const KEY &key)const{}};