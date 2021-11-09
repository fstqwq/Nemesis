// kactl,  $M \le 7.2\cdot 10^{18}$
ULL modmul(ULL a, ULL b, LL M) {
	LL ret = a * b - M * ULL(1.L / M * a * b);
	return ret + M * (ret < 0) - M * (ret >= (LL)M); }
// orz@CF, M in 63 bit
ULL modmul(ULL a, ULL b, LL M) {
	ULL c = (long double)a * b / M;
	LL ret = LL(x * y - c * M) % M;
	return ret < 0 ? ret + M : ret;}
// use int128 instead if c > 63 bit
