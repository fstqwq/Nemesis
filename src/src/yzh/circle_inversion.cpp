circle inv_c2c(point O, LD R, circle A) {
	LD OA = dis(A.c, O);
	LD RB = 0.5 * R * R * (1 / (OA - A.r) - 1 / (OA + A.r));
	LD OB = OA * RB / A.r;
	point B = O + (A.c - O) * (OB / OA);
	return {B, RB};
}  // 点 O 在圆 A 外，求圆 A 的反演圆 B，R 是反演半径
circle inv_l2c(point O, LD R, line l) {
	point P = proj_to_line(O, l);
	LD d = dis(O, P);
	LD RB = R * R / (2 * d);
	point VB = (P - O) / d * RB;
	return {O + VB, RB};
}  // 不过 O 点的直线反演为过 O 点的圆，R 是反演半径
line inv_c2l (point O, LD R, circle A) {
	LD t = R * R / (2 * A.r);
	point p = O + (A.c - O).unit() * t;
	return {p, p + (O - p).rot90()};
}  // 过 O 点的圆反演为不过 O 点的直线，R 是反演半径