// Adaptive Simpson's method : double simpson::solve (double (*f) (double), double l, double r, double eps) : integrates f over (l, r) with error eps.
struct simpson {
double area (double (*f) (double), double l, double r) { 
	double m = l + (r - l) / 2;
	return (f (l) + 4 * f (m) + f (r)) * (r - l) / 6;
}
double solve (double (*f) (double), double l, double r, double eps, double a) {
	double m = l + (r - l) / 2;
	double left = area (f, l, m), right = area (f, m, r);
	if (fabs (left + right - a) <= 15 * eps) return left + right + (left + right - a) / 15.0;
	return solve (f, l, m, eps / 2, left) + solve (f, m, r, eps / 2, right);
}
double solve (double (*f) (double), double l, double r, double eps) {
	return solve (f, l, r, eps, area (f, l, r));
}};