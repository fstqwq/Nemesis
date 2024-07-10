vector <point> add (vector <point> a, vector <point> b) {
// size > 0, rotate(begin, min, end), 无重, 小于号 (y, x)
	if (a.size() == 1 || b.size() == 1) { 
		vector <point> ret;
		for (auto i : a) for (auto j : b) ret.push_back(i+j);
		return ret; }
	vector <point> x, y;
	for (int i = 0; i < a.size(); i++)
		x.push_back(a[(i + 1) % a.size()] - a[i]);
	for (int i = 0; i < b.size(); i++)
		y.push_back(b[(i + 1) % b.size()] - b[i]);
	vector <point> ret (x.size() + y.size());
	merge(x.begin(), x.end(), y.begin(), y.end(),
		  ret.begin(), [](cp u, cp v) {
		return half(u)-half(v) ? half(u) : det(u, v) > 0;});
	point cur = a[0] + b[0];
	for (auto &i : ret) swap(i, cur), cur = cur + i;
	return ret; } // ret 可能共线，但没有重点