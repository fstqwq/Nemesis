LL mul(LL a, LL b, LL mod) {
	LL ret = (a * b - LL((LD)a / mod * b) * mod) % mod;
	return ret < 0 ? ret + mod : ret;
}
