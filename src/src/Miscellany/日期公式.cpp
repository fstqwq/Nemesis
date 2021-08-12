// weekday=(id+1)%7;{Sun=0,Mon=1,...}   getId(1, 1, 1) = 0
int getId(int y, int m, int d) {
	if (m < 3) { y --; m += 12; }
	return 365 * y + y / 4 - y / 100 + y / 400 + (153 * (m - 3) + 2) / 5 + d - 307; }
//  y<0: 统一加400的倍数年
auto date(int id) {
	int x=id+1789995, n, i, j, y, m, d;
	n = 4 * x / 146097; x -= (146097 * n + 3) / 4;
	i = (4000 * (x + 1)) / 1461001; x -= 1461 * i / 4 - 31;
	j = 80 * x / 2447; d = x - 2447 * j / 80; x = j / 11;
	m = j + 2 - 12 * x; y = 100 * (n - 49) + i + x;
	return make_tuple(y, m, d); }
