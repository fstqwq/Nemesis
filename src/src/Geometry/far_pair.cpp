LD diameter(vector <point> p) { // 最远点对
	p = convex_hull(p);
	int n = (int) p.size(); LD ret = 0;
	for (int i = 0, j, k = 1; i < n; i++) {
		j = (i + 1) % n;
		if (k == j) ++k %= n;
		while (k != i) {
			int l = (k + 1) % n;
			if (sgn(det(p[j]-p[i], p[l]-p[k])) > 0) k = l;
			else break; }
		ret = max(ret, dis(p[i], p[k])); 
		ret = max(ret, dis(p[j], p[k])); } return ret; }
