LL quadraticResidue(LL a, LL p)
{
	if (pow(a, (p - 1) / 2, p) == p - 1) return -1;
	LL s = p - 1;
	int t = 0;
	for (; ~s & 1; s >>= 1) t++;
	LL b = 1;
	for (; pow(b, (p - 1) / 2, p) % p == 1; b++);
	LL inva = inv(a, p);
	
	LL x = pow(a, (s + 1) / 2, p);  
	LL e = pow(a, s, p);
	for (int k = 1; k < t; k++)
	{
		if (pow(e, pow(2, t - (k + 1), p - 1), p) % p != 1)
			x = x * pow(b, (pow(2, k - 1, p - 1) * s) % (p - 1), p) % p;
		e = inva * x % p * x % p;
	}
	return x;
}

