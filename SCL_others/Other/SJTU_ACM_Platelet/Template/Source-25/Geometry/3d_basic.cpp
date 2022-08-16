// operator* det; operator^ dot
// 3D line intersect
P intersect(const P &a0,const P &b0,const P &a1,
            const P &b1){
  double t = ((a0.x-a1.x)*(a1.y-b1.y)-
              (a0.y-a1.y)*(a1.x-b1.x))/
             ((a0.x-b0.x)*(a1.y-b1.y)-
              (a0.y-b0.y)*(a1.x-b1.x));
  return a0+(b0-a0)*t; }
// area-line intersect
P intersect(const P &a,const P &b,const P &c,
            const P &l0,const P &l1){
  P p = (b-a)*(c-a);
  double t = (p^(a-l0))/(p^(l1-l0));
  return l0+(l1-l0)*t; }
