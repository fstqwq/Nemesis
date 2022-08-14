int min_pos(vector<int> a) {
	int n = a.size(), i = 0, j = 1, k = 0;
	while (i < n && j < n && k < n) {
		auto u = a[(i + k) % n]; auto v = a[(j + k) % n];
		int t = u > v ? 1 : (u < v ? -1 : 0);
		if (t == 0) k++; else {
			if (t > 0) i += k + 1; else j += k + 1;
			if (i == j) j++;
			k = 0; } } return min(i, j); }