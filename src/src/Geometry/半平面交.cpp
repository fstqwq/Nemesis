int sgn(cp a){return a.y > 0||(a.y == 0 && a.x > 0)?1:0;}
bool turn_left(cl a, cl b, cl c) {
  return turn_left(a.s, a.t, line_inter(b, c)); }
bool is_para(cl a, cl b){return!sgn(det(a.t-a.s,b.t-b.s));}
bool cmp(cl a, cl b) {
  int sign = sgn(a.t - a.s) - sgn(b.t - b.s);
  int dir = sgn(det(a.t - a.s, b.t - b.s));
  if (!dir && !sign) return sgn(det(a.t-a.s, b.t-a.s)) < 0;
  else return sign ? sign > 0 : dir > 0; }
vector <point> hpi(vector <line> h) { // 半平面交
  sort(h.begin(), h.end(), cmp);
  h.resize(unique(h.begin(), h.end(), is_para)-h.begin());
  vector <line> q(h.size()); int l = 0, r = -1;
  for(auto &i : h) {
   while(l<r && !turn_left(i, q[r - 1], q[r]))
     --r;
   while(l<r && !turn_left(i, q[l], q[l + 1]))
     ++l;
   q[++r] = i; }
  while(r-l>1&& !turn_left(q[l], q[r - 1], q[r]))
    --r;
  while(r-l>1&& !turn_left(q[r], q[l], q[l + 1]))
    ++l;
  if(r - l < 2) return {};
  vector <point> ret(r - l + 1);
  for(int i = l; i <= r; i++) 
    ret[i - l] = line_inter(q[i], q[i == r ? l : i + 1]);
  return ret; }
