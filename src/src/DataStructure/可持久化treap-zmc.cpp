/* 不可持久化：把 copy(a, b) 换成 a = b, 并且去除新建结点 */
const int MX = (2e5 + 233) * 18 * 8;
int vcnt;
struct node {
  int sz, ch[2], pri;
  int rev; LL sum; int val;
} tr[MX];
int newnode(int v) {
  static mt19937 rng(114514);
  int x = ++vcnt;
  tr[x].sz = 1;
  lch = rch = 0;
  tr[x].pri = rng();
  tr[x].sum = tr[x].val = v;
  tr[x].rev = false;
  return x; }
void copy(int x, int y) { tr[x] = tr[y]; }
int merge(int x, int y) {
  if (!x || !y) return x + y;
  int z = ++vcnt;
  if (tr[x].pri < tr[y].pri) {
    pushdown(x); copy(z, x);
    tr[z].ch[1] = merge(tr[z].ch[1], y);
  } else {
    pushdown(y); copy(z, y);
    tr[z].ch[0] = merge(x, tr[z].ch[0]); }
  pushup(z); return z; }
void split(int x, int dsz, int &r1, int &r2) {
  if (!x) {
    r1 = r2 = 0;
  } else {
    pushdown(x);
    if (tr[lch].sz + 1 <= dsz) {
      r1 = ++vcnt; copy(r1, x);
      split(tr[r1].ch[1], dsz - 1 - tr[lch].sz
        , tr[r1].ch[1], r2);
      pushup(r1);
    } else {
      r2 = ++vcnt; copy(r2, x);
      split(tr[r2].ch[0], dsz, r1, tr[r2].ch[0]);
      pushup(r2); } } }