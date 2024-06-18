template <class T,int P = 314159/*,451411,1141109,2119969*/>
struct hashmap {
ULL id[P]; T val[P];
int R[P]; // del: few clears
hashmap() {memset(id, -1, sizeof id);}
T get(const ULL &x) const {
	for (int i = int(x % P), j = 1; ~id[i]; i = (i + j) % P, j = (j + 2) % P /*unroll if needed*/) {
		if (id[i] == x) return val[i]; }
	return 0; }
T& operator [] (const ULL &x) {
	for (int i = int(x % P), j = 1;       ; i = (i + j) % P, j = (j + 2) % P) {
		if (id[i] == x) return val[i];
		else if (id[i] == -1llu) {
			id[i] = x;
			R[++R[0]] = i;  // del: few clears
			return val[i]; } } }
void clear() { // del: few clears
for (int &x = R[0]; x; id[R[x]] = -1, val[R[x]] = 0, --x);
void fullclear() {memset(id, -1, sizeof id); R[0] = 0; } };
