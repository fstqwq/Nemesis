struct Perm{
	vector<int> P; Perm() {} Perm(int n) { P.resize(n); }
	Perm inv() const{ Perm ret(P.size());
		for(int i = 0; i < int(P.size()); ++i) ret.P[P[i]]=i;
		return ret; }
	int &operator [](const int &dn){ return P[dn]; }
	void resize(const size_t &sz){ P.resize(sz); }
	size_t size()const{ return P.size(); }
	const int &operator[](const int &dn)const{return P[dn];}};
Perm operator *(const Perm &a, const Perm &b){
	Perm ret(a.size());
	for(int i = 0; i < (int)a.size(); ++i) ret[i] = b[a[i]];
	return ret; }
typedef vector<Perm> Bucket; typedef vector<int> Table;
typedef pair<int,int> PII; int n, m;
vector<Bucket> buckets, bucketsInv;vector<Table> lookupTable;
int fastFilter(const Perm &g, bool addToGroup = true) {
	int n = buckets.size(); Perm p(g);
	for(int i = 0; i < n; ++i){
		int res = lookupTable[i][p[i]];
		if(res == -1) {
			if(addToGroup) { buckets[i].push_back(p);
				bucketsInv[i].push_back(p.inv());
				lookupTable[i][p[i]]=(int)buckets[i].size()-1; }
			return i; }
		p = p * bucketsInv[i][res]; }
	return -1; }
long long calcTotalSize() { long long ret = 1;
	for(int i = 0; i < n; ++i) ret *= buckets[i].size();
	return ret; }
bool inGroup(const Perm &g){return fastFilter(g,false)==-1;}
void solve(const Bucket &gen,int _n) {// m perm[0..n - 1]s
	n = _n, m = gen.size(); { //clear all
		vector<Bucket> _b(n); swap(buckets, _b);
		vector<Bucket> _I(n); swap(bucketsInv, _I);
		vector<Table> _T(n); swap(lookupTable, _T); }
	for(int i = 0; i < n; ++i){
		lookupTable[i].resize(n);
		fill(lookupTable[i].begin(),lookupTable[i].end(),-1);}
	Perm id(n); for(int i = 0; i < n; ++i) id[i] = i;
	for(int i = 0; i < n; ++i){
		buckets[i].push_back(id);bucketsInv[i].push_back(id);
		lookupTable[i][i] = 0; }
	for(int i = 0; i < m; ++i) fastFilter(gen[i]);
	queue<pair<PII,PII> > toUpdate;
	for(int i = 0; i < n; ++i)
		for(int j = i; j < n; ++j)
			for(int k = 0; k < (int) buckets[i].size(); ++k)
				for(int l = 0; l < (int) buckets[j].size(); ++l)
					toUpdate.push(make_pair(PII(i,k), PII(j,l)));
	while(!toUpdate.empty()){
		PII a=toUpdate.front().first;
        PII b=toUpdate.front().second; toUpdate.pop();
		int res = fastFilter(buckets[a.first][a.second] * buckets[b.first][b.second]);
		if(res==-1) continue;
		PII newPair(res, (int)buckets[res].size() - 1);
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < (int)buckets[i].size(); ++j){
				if(i <= res)
					toUpdate.push(make_pair(PII(i, j), newPair));
				if(res <= i)
					toUpdate.push(make_pair(newPair,PII(i,j)));}}}