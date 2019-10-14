int mark[1005][1005],n, cnt;;
double mix(const P &a, const P &b, const P &c) { 
	return a^(b*c); 
}
double area(int a, int b, int c) { 
	return ((info[b] - info[a])*(info[c] - info[a])).len();
}
double volume(int a, int b, int c, int d) { 
	return mix(info[b] - info[a], info[c] - info[a], info[d] - info[a]); 
}
struct Face {
	int a, b, c; Face() {}
	Face(int a, int b, int c): a(a), b(b), c(c) {}
	int &operator [](int k) { 
		if (k == 0) return a; if (k == 1) return b; return c;
	}
};
vector <Face> face;
inline void insert(int a, int b, int c) { 
	face.push_back(Face(a, b, c)); 
}
void add(int v) {
	vector <Face> tmp; int a, b, c; cnt++;
	for (int i = 0; i < SIZE(face); i++) {
		a = face[i][0]; b = face[i][1]; c = face[i][2];
		if (sgn(volume(v, a, b, c)) < 0)
		mark[a][b] = mark[b][a] = mark[b][c] = mark[c][b] = mark[c][a] = mark[a][c] = cnt;
		else tmp.push_back(face[i]);
	} face = tmp;
	for (int i = 0; i < SIZE(tmp); i++) {
		a = face[i][0]; b = face[i][1]; c = face[i][2];
		if (mark[a][b] == cnt) insert(b, a, v);
		if (mark[b][c] == cnt) insert(c, b, v);
		if (mark[c][a] == cnt) insert(a, c, v);
	}
}
int Find() {
	for (int i = 2; i < n; i++) {
		P ndir = (info[0] - info[i])*(info[1] - info[i]);
		if (ndir == P()) continue; swap(info[i], info[2]);
		for (int j = i + 1; j < n; j++) if (sgn(volume(0, 1, 2, j)) != 0) {
			swap(info[j], info[3]); insert(0, 1, 2); insert(0, 2, 1); return 1;
		} 
	} 
	return 0; 
}
//find the weight center
double calcDist(const P &p, int a, int b, int c) { 
	return fabs(mix(info[a] - p, info[b] - p, info[c] - p) / area(a, b, c));
}
//compute the minimal distance of center of any faces
P findCenter() { //compute center of mass
	double totalWeight = 0; 
	P center(.0, .0, .0);
	P first = info[face[0][0]];
	for (int i = 0; i < SIZE(face); ++i) {
		P p = (info[face[i][0]]+info[face[i][1]]+info[face[i][2]]+first)*.25;
		double weight = mix(info[face[i][0]] - first, info[face[i][1]] - first, info[face[i][2]] - first); 
		totalWeight += weight; center = center + p * weight;
	} 
	center = center / totalWeight;
    return center; 
}
double minDis(P p) { 
	double res = 1e100; //compute distance 
	for (int i = 0; i < SIZE(face); ++i)
		res = min(res, calcDist(p, face[i][0], face[i][1], face[i][2]));
    return res; 
}

void findConvex(P *info,int n) {
	sort(info, info + n); n = unique(info, info + n) - info;
	face.clear(); random_shuffle(info, info + n);
	if(!Find())return abort();	
	memset(mark, 0, sizeof(mark)); cnt = 0;
	for (int i = 3; i < n; i++) add(i); 
}
