vector<p3> b; Circle calc() {
 if(b.empty()) { return Circle(p3(0, 0, 0), 0);
 }else if(1 == b.size()) {return Circle(b[0], 0);
 }else if(2 == b.size()) {
  return Circle((b[0] + b[1]) / 2, (b[0] - b[1]).len() / 2);
 }else if(3 == b.size()) {
  LD r = dis(b[0], b[1]) * dis(b[1], b[2]) * dis(b[2], b[0]) / 2 / cross(b[0] - b[2], b[1] - b[2]).len();
  return Circle(intersect({b[1] - b[0], (b[1] + b[0]) / 2}, {b[2] - b[1], (b[2] + b[1]) / 2}, {cross(b[1] - b[0], b[2] - b[0]), b[0]}), r);
 }else { p3 o(intersect({b[1] - b[0], (b[1] + b[0]) / 2}, {b[2] - b[0], (b[2] + b[0]) / 2}, {b[3] - b[0], (b[3] + b[0]) / 2})); return Circle(o, (o - b[0]).len()); } }
Circle miniBall(int n) {
 Circle res(calc());
 for(int i = 0; i < n; i++) if(!in_circle(a[i], res)) {
  b.push_back(a[i]); res = miniBall(i); b.pop_back();
  if (i) { p3 tmp = a[i]; memmove(a + 1, a, sizeof(p3) * i); a[0] = tmp; } }
 return res; }