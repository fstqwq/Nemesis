const int HA = 2;
const int PP[] = {318255569, 66604919, 19260817},
	 	  QQ[] = {1010451419, 1011111133, 1033111117};
int pw[HA][N];
struct hashInit { hashInit () {
	for (int h = 0; h < HA; h++) {
		pw[h][0] = 1;
		for (int i = 1; i < N; i++)
			pw[h][i] = (LL)pw[h][i - 1] * PP[h] % QQ[h];
	}
} } __init_hash;
struct Hash {
	int v[HA], len;
	Hash () {memset(v, 0, sizeof v); len = 0;}
	Hash (int x) { for (int h = 0; h < HA; h++) v[h] = x; len = 1; }
	friend Hash operator + (const Hash &a, const Hash &b) {
		Hash ret; ret.len = a.len + b.len;
		for (int h = 0; h < HA; h++) 
			ret.v[h] = ((LL)a.v[h] * pw[h][b.len] + b.v[h]) % QQ[h];
		return ret;
	}
	friend Hash operator + (const Hash &a, const int &b) {
		Hash ret; ret.len = a.len + 1;
		for (int h = 0; h < HA; h++) 
			ret.v[h] = ((LL)a.v[h] * PP[h] + b) % QQ[h];
		return ret;
	}
	friend Hash operator + (const int &a, const Hash &b) {
		Hash ret; ret.len = b.len + 1;
		for (int h = 0; h < HA; h++) 
			ret.v[h] = ((LL)a * pw[h][b.len] + b.v[h]) % QQ[h];
		return ret;
	}
	friend Hash operator - (const Hash &a, const Hash &b) {
		Hash ret; ret.len = a.len - b.len;
		for (int h = 0; h < HA; h++) {
			ret.v[h] = (a.v[h] - (LL)pw[h][b.len] * b.v[h]) % QQ[h];
			if (ret.v[h] < 0) ret.v[h] += QQ[h];
		}
		return ret;
	}
	friend bool operator == (const Hash &a, const Hash &b) {
		for (int h = 0; h < HA; h++) 
			if (a.v[h] != b.v[h]) return false;
		return a.len == b.len;
	}
};
