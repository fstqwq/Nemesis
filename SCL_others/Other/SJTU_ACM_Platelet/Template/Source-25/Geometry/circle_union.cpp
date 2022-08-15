double ans[2001];
struct Point {
  double x,y;
  Point(){}
  Point(const double &x,const double &y): x(x),y(y){}
  void scan(){scanf("%lf%lf",&x,&y);}
  double sqrlen(){return sqr(x)+sqr(y);}
  double len(){return sqrt(sqrlen());}
  Point rev(){return Point(y,-x);}
  void print(){printf("%f %f\n",x,y);}
  Point zoom(const double &d){
    double lambda = d/len();
    return Point(lambda*x,lambda*y); }
} dvd,a[2001];
Point centre[2001];
double atan2(const Point &x){ return atan2(x.y,x.x); }
// operator* det; operator% dot
circle cir[2001];
struct arc {
  double theta; int delta; Point p;
  arc(){};
  arc(const double &theta,const Point &p,int d)
    : theta(theta),p(p),delta(d){}
} vec[4444];
int nV, cnt;
bool operator<(const arc &a,const arc &b){
  return a.theta+eps<b.theta; }
void psh(const double t1,const Point p1,
                const double t2,const Point p2){
  if(t2+eps<t1) cnt++;
  vec[nV++]=arc(t1,p1,1); vec[nV++]=arc(t2,p2,-1); }
double cub(const double &x){return x*x*x;}
void combine(int d,const double &area,const Point &o){
  if(sign(area)==0) return;
  centre[d]=1/(ans[d]+area)*(ans[d]*centre[d]+area*o);
  ans[d] += area; }
bool f[2001];
void solve(){
  for(int i(0);i<n;i++){//这一段在去重圆 删掉不会错
    f[i] = true;
    for(int j(0);j<n;j++) if(i!=j){
      if(equal(cir[i],cir[j])and
         i<j or!equal(cir[i],cir[j])and
         cir[i].r<cir[j].r+eps and
         (cir[i].o-cir[j].o).sqrlen()<
         sqr(cir[i].r-cir[j].r)+eps){
        f[i] = false;
        break; }}}
  int n1(0);
  for(int i(0);i<n;i++) if(f[i]) cir[n1++] = cir[i];
  n = n1;//去重圆结束
  fill(ans,ans+n+1,0);
  fill(centre,centre+n+1,Point(0,0));
  //ans[i]被覆盖>=i次的面积 centre[i]为ans[i]的重心
  for(int i(0);i<m;i++)
    combine(0,a[i]*a[(i+1)%m]*0.5,
            1./3*(a[i]+a[(i+1)%m]));
  for(int i(0);i<n;i++){
    dvd = cir[i].o-Point(cir[i].r,0); nV = 0;
    vec[nV++] = arc(-pi,dvd,1); cnt = 0;
    for(int j(0);j<n;j++) if(j!=i){
      double d = (cir[j].o-cir[i].o).sqrlen();
      if(d<sqr(cir[j].r-cir[i].r)+eps){
        if(cir[i].r+i*eps<cir[j].r+j*eps)
          psh(-pi,dvd,pi,dvd);
      }else if(d+eps<sqr(cir[j].r+cir[i].r)){
        double lambda = 0.5*(1+(sqr(cir[i].r)-
            	sqr(cir[j].r))/d);
        Point cp(cir[i].o+
            	lambda*(cir[j].o-cir[i].o));
        Point nor((cir[j].o-cir[i].o).rev()
                  .zoom(sqrt(sqr(cir[i].r)-
	              (cp-cir[i].o).sqrlen())));
        Point frm(cp+nor); Point to(cp-nor);
        psh(atan2(frm-cir[i].o),frm,
            atan2(to-cir[i].o),to); }}
    sort(vec+1,vec+nV); vec[nV++] = arc(pi,dvd,-1);
    for(int j = 0;j+1<nV;j++){
      cnt += vec[j].delta;
      //if(cnt==1){只算ans[1]和centre[1], 加if加速。
      double theta(vec[j+1].theta-vec[j].theta);
      double area(sqr(cir[i].r)*theta*0.5);
      combine(cnt,area,cir[i].o+1./area/3
              *cub(cir[i].r)*Point(
              sin(vec[j+1].theta)-sin(vec[j].theta),
              cos(vec[j].theta)-cos(vec[j+1].theta)));
      combine(cnt,-sqr(cir[i].r)*sin(theta)*0.5,
       1./3*(cir[i].o+vec[j].p+vec[j+1].p));
      combine(cnt,vec[j].p*vec[j+1].p*0.5,
              1./3*(vec[j].p+vec[j+1].p));
      /* } */}}
  combine(0,-ans[1],centre[1]);
  for(int i = 0;i<m;i++){
    if(i!=index)
      (a[index]-Point(
        (a[i]-a[index])*(centre[0]-a[index]),
        (a[i]-a[index])%(centre[0]-a[index]))
        .zoom((a[i]-a[index]).len())).print();
    else a[i].print(); }}
