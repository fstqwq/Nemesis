const int MX = (2e5 + 233) * 18 * 8;
int sz[MX], ch[MX][2], pri[MX], vcnt, rt[MX], rev[MX], val[MX];
LL sum[MX];
#define lch(x) ch[x][0]
#define rch(x) ch[x][1]
/* 不可持久化：把 copy(a, b) 换成 a = b, 并且去除新建结点 */
int newnode(int v) {
  static mt19937 rng(114514);
  int x = ++vcnt;
  sz[x] = 1;
  lch(x) = rch(x) = 0;
  pri[x] = rng();
  sum[x] = val[x] = v;
  rev[x] = false;
  return x; }
void copy(int x, int y) {
  sz[x] = sz[y];
  lch(x) = lch(y); rch(x) = rch(y);
  pri[x] = pri[y]; val[x] = val[y];
  sum[x] = sum[y]; rev[x] = rev[y]; }
void dorev(int &x) {
  int y = ++vcnt;
  copy(y, x); rev[y] ^= 1; x = y; }
void pushdown(int x) {
  if (rev[x]) {
    if (lch(x)) dorev(lch(x));
    if (rch(x)) dorev(rch(x));
    swap(lch(x), rch(x)); rev[x] = 0; } }
void pushup(int x) {
  sz[x] = sz[lch(x)] + sz[rch(x)] + 1;
  sum[x] = sum[lch(x)] + sum[rch(x)] + val[x]; }
int merge(int x, int y) {
  if (!x || !y) return x + y;
  int z = ++vcnt;
  if (pri[x] < pri[y]) {
    pushdown(x);
    copy(z, x);
    ch[z][1] = merge(ch[z][1], y);
  } else {
    pushdown(y);
    copy(z, y);
    ch[z][0] = merge(x, ch[z][0]); }
  pushup(z); return z; }
void split(int x, int dsz, int &r1, int &r2) {
  if (!x) {
    r1 = r2 = 0;
  } else {
    pushdown(x);
    if (sz[lch(x)] + 1 <= dsz) {
      r1 = ++vcnt;
      copy(r1, x);
      split(ch[r1][1], dsz - 1 - sz[lch(x)], ch[r1][1], r2);
      pushup(r1);
    } else {
      r2 = ++vcnt;
      copy(r2, x);
      split(ch[r2][0], dsz, r1, ch[r2][0]);
      pushup(r2); } } }