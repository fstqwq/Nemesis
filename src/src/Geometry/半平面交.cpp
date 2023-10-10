int sgn(cp a){return a.y > 0||(a.y == 0 && a.x > 0)?1:-1;}
bool turn_left(cl l, cp p){return turn_left(l.s, l.t, p);}
vector <point> hpi(vector <line> h) {
  sort(h.begin(), h.end(), [](cl a, cl b) {
    int dir = sgn(a.t - a.s) - sgn(b.t -  b.s);
    if (dir) return dir < 0;
    dir = sgn(det(a.t - a.s, b.t - b.s));
    if (dir) return dir > 0;
    return sgn(det(a.t - a.s, b.t - a.s)) < 0; });
  h.resize(unique(h.begin(), h.end(), [](cl a, cl b) {
    return !sgn(det(a.t - a.s, b.t - b.s));})-h.begin());
  vector <line> q; int l = 0, r = -1;
  for(auto &i : h) {
   while(l<r && !turn_left(i, line_inter(q[r - 1], q[r])))
     --r, q.pop_back();
   while(l<r && !turn_left(i, line_inter(q[l], q[l + 1])))
     ++l;
   ++r; q.push_back(i); }
  while(r-l>1&& !turn_left(q[l],line_inter(q[r - 1],q[r])))
    --r, q.pop_back();
  while(r-l>1&& !turn_left(q[r],line_inter(q[l],q[l + 1])))
    ++l;
  if(r - l < 2) return {};
  vector <point> ret(r - l + 1);
  for(int i = l; i <= r; i++) 
    ret[i - l] = line_inter(q[i], q[i == r ? l : i + 1]);
  return ret; }
