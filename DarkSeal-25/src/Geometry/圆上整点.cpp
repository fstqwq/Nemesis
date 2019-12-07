void solve(LL r) {
	LL rr = 2 * r, sr = LL(sqrt(rr));
	for (LL d = 1; d <= sr; d++)if (rr % d == 0){
		LL lim = sqrt(rr / (2*d));
		for (LL a = 1; a <= lim; a++){
			LL b = sqrt(rr/d - a * a);
			if (a*a + b*b == rr/d && chk(a,b)) {
				LL Y = d * a * b, X = sqrt(r * r -  Y * Y);
			} }// $X ^ 2 + Y ^ 2 = r ^ 2$ 
		if (d*d != rr){
			lim = sqrt(d/2);
			for (LL a = 1; a <= lim; a++){
				LL b = sqrtl(d - a*a);
				if (a*a + b*b == d && chk(a,b)) {
					LL Y = rr / d * a * b, X = sqrt(r * r -  Y * Y);
				} }// $X ^ 2 + Y ^ 2 = r ^ 2$ 
			} } }// $0 ^ 2 + R ^ 2 = R ^ 2$
