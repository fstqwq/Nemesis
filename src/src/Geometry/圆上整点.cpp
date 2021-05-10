vector <LL> solve(LL r) {
	vector <LL> ret; // non-negative Y pos
	ret.push_back(0);
	LL l = 2 * r, s = sqrt(l);
	for (LL d=1; d<=s; d++) if (l%d==0) {
		LL lim=LL(sqrt(l/(2*d)));
		for (LL a = 1; a <= lim; a++) {
			LL b = sqrt(l/d-a*a);
			if (a*a+b*b==l/d && __gcd(a,b)==1 && a!=b)
				ret.push_back(d*a*b); 
		} if (d*d==l) break;
		lim = sqrt(d/2);
		for (LL a=1; a<=lim; a++) {
			LL b = sqrt(d - a * a);
			if (a*a+b*b==d && __gcd(a,b)==1 && a!=b)
				ret.push_back(l/d*a*b);
	} } return ret; } 
