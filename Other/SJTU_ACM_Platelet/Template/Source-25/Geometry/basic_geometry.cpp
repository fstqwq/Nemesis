point intersect(const line &a,const line &b){
  number s1 = det(a.b-a.a,b.a-a.a);
  number s2 = det(a.b-a.a,b.b-a.a);
  return (b.a*s2-b.b*s1)/(s2-s1); }
point projection(const point &p,const line &l){
  return l.a+(l.b-l.a)*dot(p-l.a,l.b-l.a)/
             (l.b-l.a).len2(); }
number dis(const point &p,const line &l){
  return std::abs(det(p-l.a,l.b-l.a))/
         (l.b-l.a).len(); }
bool intersect(const line &l,const circle &a,
               point &p1,point &p2){
  number x = dot(l.a-a.o,l.b-l.a);
  number y = (l.b-l.a).len2();
  number d = x*x-y*((l.a-a.o).len2()-a.r*a.r);
  if(sgn(d)<0) return false;
  point p = l.a-(l.b-l.a)*(x/y);
  point delta = (l.b-l.a)*(_sqrt(d)/y);
  p1 = p+delta,p2 = p-delta;
  return true; }
bool intersect(const circle &a,const circle &b,
               point &p1,point &p2) {
  number x = (a.o-b.o).len2();
  number y = ((a.r*a.r-b.r*b.r)/x+1)/2;
  number d = a.r*a.r/x-y*y;
  if (sgn(d) < 0) return false;
  point p0 = a.o+(b.o-a.o)*y;
  point delta = ((b.o-a.o)*_sqrt(d)).rotate90();
  p1 = p0-delta; p2 = p0+delta;
  return true; }
bool tangent(const point &p0,const circle &c,
             point &p1,point &p2){
  number x = (p0-c.o).len2();
  number d = x-c.r*c.r;
  if(sgn(d)<0) return false;
  if(sgn(d)==0) return /* point_on_line */ false;
  point p = (p0-c.o)*(c.r*c.r/x);
  point delta =
    ((p0-c.o)*(-c.r*_sqrt(d)/x)).rotate90();
  p1 = c.o+p+delta; p2 = c.o+p-delta;
  return true; }
bool ex_tangent(const circle &a,const circle &b,
                line &l1,line &l2){
  if(cmp(std::abs(a.r-b.r),(b.o-a.o).len())==0){
    point p1,p2; intersect(a,b,p1,p2);
    l1 = l2 = line(p1,p1+(a.o-p1).rotate90());
    return true;
  }else if(cmp(a.r,b.r)==0){
    point dir = b.o-a.o;
    dir = (dir*(a.r/dir.len())).rotate90();
    l1 = line(a.o+dir,b.o+dir);
    l2 = line(a.o-dir,b.o-dir);
    return true;
  }else{
    point p = (b.o*a.r-a.o*b.r)/(a.r-b.r);
    point p1,p2,q1,q2;
    if(tangent(p,a,p1,p2)&&tangent(p,b,q1,q2)){
      l1 = line(p1,q1); l2 = line(p2,q2);
      return true;
    }else{ return false; }}}
bool in_tangent(const circle &a,const circle &b,
                line &l1,line &l2){
  if(cmp(a.r+b.r,(b.o-a.o).len())==0){
    point p1,p2; intersect(a,b,p1,p2);
    l1 = l2 = line(p1,p1+(a.o-p1).rotate90());
    return true;
  }else{
    point p = (b.o*a.r+a.o*b.r)/(a.r+b.r);
    point p1,p2,q1,q2;
    if(tangent(p,a,p1,p2)&&tangent(p,b,q1,q2)){
      l1 = line(p1,q1); l2 = line(p2,q2);
      return true;
    }else{ return false; }}}
