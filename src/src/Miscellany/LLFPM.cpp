// kactl,  $M \le 7.2\cdot 10^{18}$
ULL modmul(ULL a, ULL b, LL M) {
	LL ret = a * b - M * ULL(1.L / M * a * b);
	return ret + M * (ret < 0) - M * (ret >= (LL)M); }
// orz@CF, M in 63 bit
ULL modmul(ULL a, ULL b, LL M) {
	ULL c = (long double)a * b / M;
	LL ret = LL(x * y - c * M) % M; // must be signed
	return ret < 0 ? ret + M : ret;}
// use int128 instead if M > 63 bit
struct DIV { 
	ULL p, ip;
	void init (ULL _p) { p = _p; ip = -1llu / p; }
	int mod (ULL x) { // x < 2 ^ 64
		ULL q = ULL(((u128)iP * x) >> 64);
		ULL r = x - q * p;
		return int(r >= p ? r - p : r);
} }; // speedup only when mod is not const