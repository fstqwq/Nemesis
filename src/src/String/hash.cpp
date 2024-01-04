const int H = 2;
const int P[] = {318255569, 19873577, 18611951},
          Q[] = {1010451419, 1011111133, 1033111117};
int pw[H][N];
struct hashInit { hashInit () {
  for (int h = 0; h < H; h++) {
    pw[h][0] = 1;
    for (int i = 1; i < N; i++)
      pw[h][i] = (LL)pw[h][i - 1] * P[h] % Q[h];
  } } } __init_hash;
struct Hash {
int v[H], len;
Hash () {memset(v, 0, sizeof v); len = 0;}
Hash (int x) {len = 1;for (int h = 0; h < H; h++) v[h] = x;}
};Hash operator + (const Hash &a, const int &b) {
  Hash ret; ret.len = a.len + 1;
  for (int h = 0; h < H; h++) 
    ret.v[h] = ((LL)a.v[h] * P[h] + b) % Q[h];
  return ret; }
Hash operator - (const Hash &a, const Hash &b) {
  Hash ret; ret.len = a.len - b.len;
  for (int h = 0; h < H; h++) {
    ret.v[h] = (a.v[h] - (LL)pw[h][ret.len]*b.v[h]) % Q[h];
    if (ret.v[h] < 0) ret.v[h] += Q[h];
  } return ret; }
bool operator == (const Hash &a, const Hash &b) {
  for (int h = 0; h < H; h++) 
    if (a.v[h] != b.v[h]) return false;
  return a.len == b.len; }
Hash operator + (const Hash &a, const Hash &b) {
  Hash ret; ret.len = a.len + b.len;
  for (int h = 0; h < H; h++) 
    ret.v[h] = ((LL)a.v[h] * pw[h][b.len] + b.v[h]) % Q[h];
  return ret; }