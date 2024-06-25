vector <p3> p;
int mark[N][N], stp;
typedef array <int, 3> Face;
vector <Face> face;
LD volume (int a, int b, int c, int d) {
	return mix (p[b] - p[a], p[c] - p[a], p[d] - p[a]); }
void ins(int a, int b, int c) {face.push_back({a, b, c});}
void add(int v) {
	vector <Face> tmp; int a, b, c; stp++;
	for (auto f : face) {
		if (sgn(volume(v, f[0], f[1], f[2])) < 0) {
			for (auto i : f) for (auto j : f)
				mark[i][j] = stp; }
		else {
			tmp.push_back(f);}
	} face = tmp;
	for (int i = 0; i < (int) tmp.size(); i++) {
		a = tmp[i][0], b = tmp[i][1], c = tmp[i][2];
		if (mark[a][b] == stp) ins(b, a, v);
		if (mark[b][c] == stp) ins(c, b, v);
		if (mark[c][a] == stp) ins(a, c, v); } }
bool Find(int n) {
	for (int i = 2; i < n; i++) {
		p3 ndir = cross (p[0] - p[i], p[1] - p[i]);
		if (ndir == p3(0,0,0)) continue;
		swap(p[i], p[2]);
		for (int j = i + 1; j < n; j++) {
			if (sgn(volume(0, 1, 2, j)) != 0) {
				swap(p[j], p[3]);
				ins(0, 1, 2);
				ins(0, 2, 1);
				return 1;
	} } } return 0; }
mt19937 rng;
bool solve() {
	face.clear();
	int n = (int) p.size();
	shuffle(p.begin(), p.end(), rng);
	if (!Find(n)) return 0;
	for (int i = 3; i < n; i++) add(i);
	return 1; }
