vector<int> berlekamp_massey(const vector<int> &a) {
	vector<int> v, last; // v is the answer, 0-based
	int k = -1, delta = 0;
	for (int i = 0; i < (int)a.size(); i++) { int tmp = 0;
		for (int j = 0; j < (int)v.size(); j++)
			tmp = (tmp + (LL)a[i - j - 1] * v[j]) % p;
		if (a[i] == tmp) continue;
		if (k < 0) { k = i; delta = (a[i] - tmp + p) % p;
			v = vector<int>(i + 1); continue; }
		vector<int> u = v;
		int val = (LL)(a[i] - tmp + p) *
			qpow(delta, p - 2) % p;
		if (v.size() < last.size() + i - k)
			v.resize(last.size() + i - k);
		(v[i - k - 1] += val) %= p;
		for (int j = 0; j < (int)last.size(); j++) {
			v[i - k + j] = (v[i - k + j] -
				(LL)val * last[j]) % p;
			if (v[i - k + j] < 0) v[i - k + j] += p; }
		if ((int)u.size() - i < (int)last.size() - k) {
			last = u; k = i; delta = a[i] - tmp;
			if (delta < 0) delta += p; } }
	for (auto &x : v) x = (p - x) % p;
	v.insert(v.begin(), 1); //一般是需要最小递推式的, 处理一下
	return v; } // $\forall i, \sum_{j = 0} ^ m a_{i - j} v_j = 0$
