int n; vector <point> a; // 可以封装成一个 struct
bool inside (cp u) { // 点在凸包内
	int l = 1, r = n - 2;
	while (l < r) {
		int mid = (l + r + 1) / 2;
		if (turn(a[0], a[mid], u) >= 0) l = mid;
		else r = mid - 1; }
	return turn (a[0], a[l], u) >= 0
	    && turn (a[l], a[l + 1], u) >= 0
	    && turn (a[l + 1], a[0], u) >= 0; }
int search (auto f) { // 凸包求极值，需要 C++17
	int l = 0, r = n - 1;
	int d = f(a[r], a[l]) ? (swap(l, r), -1) : 1;
	while (d * (r - l) > 1) {
		int mid = (l + r) / 2;
		if (f(a[mid], a[l]) && f(a[mid], a[mid - d])) l = mid;
		else r = mid; } return l; }
pair<int, int> get_tan(cp u) { // 求切线
 return // 严格在凸包外；需要边界上时，特判 a[n-1] -> a[0]
 {search([&](cp x, cp y){return turn(u, y, x) > 0;}),
  search([&](cp x, cp y){return turn(u, x, y) > 0;})};}
point at (int i) { return a[i % n]; } 
int inter (cp u, cp v, int l, int r) {
	int sl = turn(u, v, at(l));
	while (l + 1 < r) {
		int m = (l + r) / 2;
		if (sl == turn(u, v, at(m))) l = m;
		else r = m;	} return l % n; }
bool get_inter(cp u, cp v, int &i, int &j) { // 求直线交点
	int p0 = search([&](cp x, cp y){
	 return det(v - u, x - u) < det(v - u, y - u);}),
	p1 = search([&](cp x, cp y) {
	 return det(v - u, x - u) > det(v - u, y - u);});
	if (turn(u, v, a[p0]) * turn(u, v, a[p1]) < 0) {
		if (p0 > p1) swap(p0, p1);
		i = inter (u, v, p0, p1);
		j = inter (u, v, p1, p0 + n);
		return true; } else return false; }
LD near (cp u, int l, int r) {
	if (l > r) r += n;
	int sl = sgn (dot(u - at(l), at(l + 1) - at(l)));
	LD ret = p2s (u, {at(l), at(l + 1)});
	while (l + 1 < r) {
		int m = (l + r) / 2;
		if (sl == sgn (dot(u - at(m), at(m + 1) - at(m))))
			l = m; else r = m; }
   return min(ret, p2s(u, {at(l), at(l + 1)})); }
LD get_near (cp u) { // 求凸包外点到凸包最近点
	if (inside(u)) return 0;
	auto [x, y] = get_tan(u);
	return min(near(u, x, y), near(u, y, x)); }