int half(cp a){return a.y > 0||(a.y == 0 && a.x > 0)?1:0;}
bool turn_left(cl a, cl b, cl c) {
  return turn(a.s, a.t, line_inter(b, c)) > 0; }
bool is_para(cl a, cl b){return!sgn(det(a.t-a.s,b.t-b.s));}
bool cmp(cl a, cl b) {
  int sign = half(a.t - a.s) - half(b.t - b.s);
  int dir = sgn(det(a.t - a.s, b.t - b.s));
  if (!dir && !sign) return turn(a.s, a.t, b.t) < 0;
  else return sign ? sign > 0 : dir > 0; }
vector <point> hpi(vector <line> h) { // 半平面交
  sort(h.begin(), h.end(), cmp);
  vector <line> q(h.size()); int l = 0, r = -1;
  for(auto &i : h) {
   while (l < r && !turn_left(i, q[r - 1], q[r])) --r;
   while (l < r && !turn_left(i, q[l], q[l + 1])) ++l;
   if (l <= r && is_para(i, q[r])) continue;
   q[++r] = i; }
  while (r - l > 1 && !turn_left(q[l], q[r - 1], q[r])) --r;
  while (r - l > 1 && !turn_left(q[r], q[l], q[l + 1])) ++l;
  if(r - l < 2) return {};
  vector <point> ret(r - l + 1);
  for(int i = l; i <= r; i++) 
    ret[i - l] = line_inter(q[i], q[i == r ? l : i + 1]);
  return ret; }
// 空集会在队列里留下一个开区域；开区域会被判定为空集。
// 为了保证正确性，一定要加足够大的框，尽可能避免零面积区域。
// 实在需要零面积区域边缘，需要仔细考虑 turn_left 的实现。