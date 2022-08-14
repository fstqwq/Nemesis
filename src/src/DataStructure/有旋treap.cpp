struct node { int key, size, p; node *ch[2];
	node(int key = 0) : key(key), size(1), p(rand()) {}
	void update(){size = ch[0] -> size + ch[1] -> size + 1;}
} null[maxn], *root = null, *ptr = null;
node *newnode(int x) { *++ptr = node(x);
	ptr -> ch[0] = ptr -> ch[1] = null; return ptr; }
void rot(node *&x, int d) { node *y = x -> ch[d ^ 1];
	x -> ch[d ^ 1] = y -> ch[d]; y -> ch[d] = x;
	x -> update(); (x = y) -> update(); }
void insert(int x, node *&o) {
	if (o == null) { o = newnode(x); return; }
	int d = x > o -> key; insert(x, o -> ch[d]); o->update();
	if (o -> ch[d] -> p < o -> p) rot(o, d ^ 1); }
void erase(int x, node *&o) {
	if (x == o -> key) {
		if (o -> ch[0] != null && o -> ch[1] != null) {
			int d = o -> ch[0] -> p < o -> ch[1] -> p;
			rot(o, d); erase(x, o -> ch[d]); }
		else o = o -> ch[o -> ch[0] == null]; }
	else erase(x, o -> ch[x > o -> key]); 
	if (o != null) o -> update(); }
int rank(int x, node *o) {
	int ans = 1, d; while (o != null) {
		if ((d = x > o->key)) ans += o -> ch[0] -> size + 1;
		o = o -> ch[d]; } return ans; }
node *kth(int x, node *o) {
	int d; while (o != null) {
		if (x == o -> ch[0] -> size + 1) return o;
		if ((d = x > o -> ch[0] -> size))
			x -= o -> ch[0] -> size + 1;
		o = o -> ch[d]; } return o; }
node *pred(int x, node *o) {
	node *y = null; int d; while (o != null) {
		if ((d = x > o -> key)) y = o;
		o = o -> ch[d]; } return y; }
int main() { // null -> ch[0] = null -> ch[1] = null;
	null -> size = 0; return 0; }