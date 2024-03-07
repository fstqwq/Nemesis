// Adaptive Simpson's method : LD simpson::solve (LD (*f) (LD), LD l, LD r, LD eps) : integrates f over (l, r) with error eps.
struct simpson {
LD area (LD (*f) (LD), LD l, LD r) { 
	LD m = l + (r - l) / 2;
	return (f (l) + 4 * f (m) + f (r)) * (r - l) / 6;
}
LD solve (LD (*f) (LD), LD l, LD r, LD eps, LD a) {
	LD m = l + (r - l) / 2;
	LD left = area (f, l, m), right = area (f, m, r);
	if (abs (left + right - a) <= 15 * eps) // TLE: || eps < EPS ** 2
		return left + right + (left + right - a) / 15.0;
	return solve (f, l, m, eps / 2, left) + solve (f, m, r, eps / 2, right);
}
LD solve (LD (*f) (LD), LD l, LD r, LD eps) {
	return solve (f, l, r, eps, area (f, l, r));
}};