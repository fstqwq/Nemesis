int C; circle c[MAXN]; LD area[MAXN];
struct event { // 如果需要边界而非面积，那么仔细考虑事件顺序
 point p; LD ang; int delta;
 bool operator <(const event &a){return ang < a.ang;}};
void addevent(cc a, cc b, vector<event> &e, int &cnt) {
 LD d2=dis2(a.c, b.c),dw=((a.r-b.r)*(a.r+b.r)/d2+1)/2,pw=
sqrt(max(0.,-(d2-sqr(a.r-b.r)*(d2-sqr(a.r+b.r))/sqr(2*d2));
 point d = b.c - a.c, p = d.rot(PI / 2),
  q0 = a.c + d * dw + p * pw,
  q1 = a.c + d * dw - p * pw;
 LD ang0 = atan2((q0 - a.c).y, (q0 - a.c).x),
    ang1 = atan2((q1 - a.c).y, (q1 - a.c).x);
 e.push_back({q1,ang1,1}); e.push_back({q0,ang0,-1});
 cnt += ang1 > ang0; }
bool issame(cc a, cc b) {
 return sgn(dis(a.c,b.c)) == 0 && sgn(a.r-b.r) == 0; }
bool overlap(cc a, cc b) { 
 return sgn(a.r - b.r - dis(a.c, b.c)) >= 0; }
bool intersect(cc a, cc b) { 
 return sgn(dis(a.c, b.c) - a.r - b.r) < 0; }
void solve() {
 fill(area, area + C + 2, 0);
 for(int i = 0; i < C; ++i) { int cnt = 1;
  vector<event> e;
  for(int j=0; j<i; ++j) if(issame(c[i],c[j])) ++cnt;
  for(int j = 0; j < C; ++j)
   if(j != i && !issame(c[i], c[j]) && overlap(c[j], c[i])) ++cnt;
  for(int j = 0; j < C; ++j)
   if(j != i && !overlap(c[j], c[i]) && !overlap(c[i], c[j]) && intersect(c[i], c[j]))
    addevent(c[i], c[j], e, cnt);
  if(e.empty()) area[cnt] += PI * c[i].r * c[i].r;
  else {
   sort(e.begin(), e.end());
   e.push_back(e.front());
   for(int j = 0; j + 1 <(int)e.size(); ++j) {
    cnt += e[j].delta;
    area[cnt] += det(e[j].p,e[j + 1].p) / 2;
    LD ang = e[j + 1].ang - e[j].ang;
    if(ang < 0) ang += PI * 2;
    area[cnt] += ang * c[i].r * c[i].r / 2 - sin(ang) * c[i].r * c[i].r / 2; } } } }
