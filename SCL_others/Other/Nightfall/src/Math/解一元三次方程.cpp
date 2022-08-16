double a(p[3]), b(p[2]), c(p[1]), d(p[0]);
double k(b / a), m(c / a), n(d / a);
double p(-k * k / 3. + m);
double q(2. * k * k * k / 27 - k * m / 3. + n);
Complex omega[3] = {Complex(1, 0), Complex(-0.5, 0.5 * sqrt(3)), Complex(-0.5, -0.5 * sqrt(3))};
Complex r1, r2; double delta(q * q / 4 + p * p * p / 27);
if (delta > 0) {
	r1 = cubrt(-q / 2. + sqrt(delta));
	r2 = cubrt(-q / 2. - sqrt(delta));
} else {
	r1 = pow(-q / 2. + pow(Complex(delta), 0.5), 1. / 3);
	r2 = pow(-q / 2. - pow(Complex(delta), 0.5), 1. / 3); }
for(int _(0); _ < 3; _++) {
	Complex x = -k/3. + r1*omega[_] + r2*omega[_* 2 % 3]; }
