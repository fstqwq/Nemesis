vector <point> a; map <point, int> id;
int search (auto f) {
 int l = 0, r = (int) a.size() - 1;
 if (f(a[0], a.back())) {
  while (l + 1 < r) {
   int mid = (l + r) / 2;
   if (f(a[mid], a[l]) && f(a[mid], a[mid - 1])) l = mid;
   else r = mid; } return l;
 } else {
  while (l + 1 < r) {
   int mid = (l + r) / 2;
   if (f(a[mid], a[r]) && f(a[mid], a[mid + 1])) r = mid;
   else l = mid; } return r; } }
vector <point> get_tan(cp u) {
 if (id.count(u)) return {a[(id[u]+n-1)%n], a[(id[u]+1)%n]};
 if (point_on_segment(u, {a[0], a.back()}))
    return {a.back(), a[0]};
 return
 {a[search([&](cp x, cp y){return turn_left(u, y, x);})],
  a[search([&](cp x, cp y){return turn_left(u, x, y);})]};}