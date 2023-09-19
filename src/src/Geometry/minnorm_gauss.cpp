typedef vector <LD> vec; /* sum a[i][0..d] = 0 */
pair<vec,vector<vec>> gauss(vector<vec> &a, int n, int d) {
	vector <int> pivot(d, -1);
	for (int i = 0, o = 0; i < d; i++) {
		int j = o; while (j < n && abs(a[j][i]) < eps) j++;
		if (j == n) continue;
		swap(a[j], a[o]); LD w = a[o][i];
		for (int k = 0; k <= d; k++) a[o][k] /= w;
		for (int x = 0; x < n; x++)
			if (x != o && abs(a[x][i]) > eps) {
				w = a[x][i];
				for (int k = 0; k <= d; k++)
					a[x][k] -= a[o][k] * w;   }
		pivot[i] = o++;
	} vec x0(d); vector <vec> t; int free = 0;
	for (int i = 0; i < d; i++) 
		if (pivot[i] != -1) x0[i] = -a[pivot[i]][d];
		else free ++;
	for (int i = 0; i < d; i++) if (pivot[i] == -1) {
		vec x(d); x[i] = -1;
		for (int j = 0; j < d; j++) 
			if (pivot[j] != -1) x[j] = a[pivot[j]][i];
		t.push_back(x);
	} if (t.size()) {
		vector <vec> f;
		for (int u = 0; u < free; u++) {
			vec x(free + 1);
			for (int i = 0; i < free; i++)
				for (int j = 0; j < d; j++)
					x[i] += t[u][j] * t[i][j];
			for (int j = 0; j < d; j++)
				x[free] += t[u][j] * x0[j];
			f.push_back(x);
		}
		auto [k, tt] = gauss(f, free, free);
		assert (tt.size() == 0);
		for (int x = 0; x < free; x++)
			for (int i = 0; i < d; i++)
				x0[i] += k[x] * t[x][i];
	} return {x0, t}; }
