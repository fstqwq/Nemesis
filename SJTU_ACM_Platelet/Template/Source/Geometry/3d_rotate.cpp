P rotate(const P& s, const P& axis, double w) {
	double x = axis.x, y = axis.y, z = axis.z;
	double s1 = x * x + y * y + z * z, ss1 = msqrt(s1),
	   cosw = cos(w), sinw = sin(w);
	double a[4][4];
	memset(a, 0, sizeof a);
	a[3][3] = 1;
	a[0][0] = ((y * y + z * z) * cosw + x * x) / s1;
	a[0][1] = x * y * (1 - cosw) / s1 + z * sinw / ss1;
	a[0][2] = x * z * (1 - cosw) / s1 - y * sinw / ss1;
	a[1][0] = x * y * (1 - cosw) / s1 - z * sinw / ss1;
	a[1][1] = ((x * x + z * z) * cosw + y * y) / s1;
	a[1][2] = y * z * (1 - cosw) / s1 + x * sinw / ss1;
	a[2][0] = x * z * (1 - cosw) / s1 + y * sinw / ss1;
	a[2][1] = y * z * (1 - cosw) / s1 - x * sinw / ss1;
	a[2][2] = ((x * x + y * y) * cos(w) + z * z) / s1;
	double ans[4] = {0, 0, 0, 0}, c[4] = {s.x, s.y, s.z, 1};
	for (int i = 0; i < 4; ++ i)
		for (int j = 0; j < 4; ++ j)
			ans[i] += a[j][i] * c[j];
	return P(ans[0], ans[1], ans[2]);
}
