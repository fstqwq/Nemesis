int mark[N][N], cnt;
D mix(const Point & a, const Point & b, const Point & c) { return a.dot(b.cross(c)); }
double volume(int a, int b, int c, int d) { return mix(info[b] - info[a], info[c] - info[a], info[d] - info[a]); }
typedef array<int, 3> Face; vector<Face> face;
inline void insert(int a, int b, int c) { face.push_back({a, b, c}); }
void add(int v) {
	vector<Face> tmp; int a, b, c; cnt++;
	for(auto f : face)
		if(sign(volume(v, f[0], f[1], f[2])) < 0)
			for(int i : f) for(int j : f) mark[i][j] = cnt;
		else tmp.push_back(f);
	face = tmp;
	for(int i(0); i < (int)tmp.size(); i++) {
		a = face[i][0]; b = face[i][1]; c = face[i][2];
		if(mark[a][b] == cnt) insert(b, a, v);
		if(mark[b][c] == cnt) insert(c, b, v);
		if(mark[c][a] == cnt) insert(a, c, v); } }
int Find(int n) {
	for(int i(2); i < n; i++) {
		Point ndir=(info[0]-info[i]).cross(info[1]-info[i]);
		if(ndir==Point(0,0,0))continue;swap(info[i],info[2]);
		for(int j = i + 1; j < n; j++) if(sign(volume(0, 1, 2, j)) != 0) {
			swap(info[j], info[3]); insert(0, 1, 2), insert(0, 2, 1); return 1; } } }
int main() {
	int n; scanf("%d", &n);
	for(int i(0); i < n; i++) info[i].scan();
	random_shuffle(info, info + n);
	Find(n);
	for(int i = 3; i < n; i++) add(i); }