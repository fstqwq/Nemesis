template <class T,int P = 314159/*,451411,1141109,2119969*/>
struct hashmap {
ULL id[P]; T val[P]; int rec[P]; // del: no cleas
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
			rec[++rec[0]] = i;  // del: no many clears
			return val[i]; } } }
void clear() { // del
	while(rec[0]) id[rec[rec[0]]] = -1, val[rec[rec[0]]] = 0, --rec[0]; }
void fullclear() {
	memset(id, -1, sizeof id); rec[0] = 0; } };

