LD solve(point p[], int l, int r) { // solve(p, 0, n)
	if(l + 1 >= r) return INF;
	int m = (l + r) / 2; LD mx = p[m].x;
	LD ret = min(solve(p, l, m), solve(p, m, r));
 	vector <point> v;
	for(int i = l; i < r; i ++)
		if(sqr(p[i].x - mx) < ret) v.push_back(p[i]);
	sort(v.begin(), v.end(), by_y);
	for(int i = 0; i < v.size(); i ++)
		for(int j = i + 1; j < v.size(); j ++) {
			if(sqr(v[i].y - v[j].y) > ret) break;
			ret = min(ret, dis2(v[i], v[j])); }
	return ret; } // 需先对p[]按x进行排序
