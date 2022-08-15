/* Delaunay Triangulation 随机增量算法 :
节点数至少为点数的 6 倍, 空间消耗较大注意计算内存使用
建图的过程在 build 中, 注意初始化内存池和初始三角形的坐标范围 (Triangulation::LOTS)
Triangulation::find 返回包含某点的三角形
Triangulation::add_point 将某点加入三角剖分
某个 Triangle 在三角剖分中当且仅当它的 has_child 为 0
如果要找到三角形 u 的邻域, 则枚举它的所有 u.edge[i].tri, 该条边的两个点为 u.p[(i+1)%3], u.p[(i+2)%3] */
const int N = 100000 + 5, MAX_TRIS = N * 6;
const double EPSILON = 1e-6, PI = acos(-1.0);
struct Point {
  double x,y; Point():x(0),y(0){}
    Point(double x, double y):x(x),y(y){}
  bool operator ==(Point const& that)const {return x==that.x&&y==that.y;} };
inline double sqr(double x) { return x*x; }
double dist_sqr(Point const& a, Point const& b){return sqr(a.x-b.x)+sqr(a.y-b.y);}
bool in_circumcircle(Point const& p1, Point const& p2, Point const& p3, Point const& p4) {
  double u11 = p1.x-p4.x, u21 = p2.x-p4.x, u31 = p3.x-p4.x;
  double u12 = p1.y-p4.y, u22 = p2.y-p4.y, u32 = p3.y-p4.y;
  double u13 = sqr(p1.x)-sqr(p4.x) + sqr(p1.y) - sqr(p4.y);
  double u23 = sqr(p2.x)-sqr(p4.x) + sqr(p2.y) - sqr(p4.y);
  double u33 = sqr(p3.x)-sqr(p4.x) + sqr(p3.y) - sqr(p4.y);
  double det = -u13*u22*u31 + u12*u23*u31 + u13*u21*u32 - u11*u23*u32 - u12*u21*u33 + u11*u22*u33;
  return det > EPSILON; }
double side(Point const& a, Point const& b, Point const& p) { return (b.x-a.x)*(p.y-a.y) - (b.y-a.y)*(p.x-a.x);}
typedef int SideRef; struct Triangle; typedef Triangle* TriangleRef;
struct Edge {
  TriangleRef tri; SideRef side; Edge() : tri(0), side(0) {}
  Edge(TriangleRef tri, SideRef side) : tri(tri), side(side) {} };
struct Triangle {
  Point p[3];Edge edge[3];TriangleRef child[3]; Triangle(){}
  Triangle(Point const& p0,Point const& p1,Point const& p2){
    p[0] = p0; p[1] = p1; p[2] = p2;
        child[0] = child[1] = child[2] = 0; }
  bool has_child() const { return child[0] != 0; }
  int num_child() const {
    return child[0] == 0 ? 0
      : child[1] == 0 ? 1
      : child[2] == 0 ? 2 : 3; }
  bool contains(Point const& q) const {
    double a=side(p[0],p[1],q), b=side(p[1],p[2],q), c=side(p[2],p[0],q);
    return a >= -EPSILON && b >= -EPSILON && c >= -EPSILON; }
} triange_pool[MAX_TRIS], *tot_triangles;
void set_edge(Edge a, Edge b) {
  if (a.tri) a.tri->edge[a.side] = b;
  if (b.tri) b.tri->edge[b.side] = a; }
class Triangulation {
  public:
    Triangulation() {
      const double LOTS = 1e6;
      the_root = new(tot_triangles++) Triangle (Point(-LOTS,-LOTS), Point(+LOTS,-LOTS), Point(0,+LOTS)); }
    TriangleRef find(Point p) const { return find(the_root,p); }
    void add_point(Point const& p) { add_point(find(the_root,p),p); }
  private:
    TriangleRef the_root;
    static TriangleRef find(TriangleRef root,Point const& p){
      for( ; ; ) {
        if (!root->has_child()) return root;
        else for (int i = 0; i < 3 && root->child[i] ; ++i)
            if (root->child[i]->contains(p))
              {root = root->child[i]; break;} } }
    void add_point(TriangleRef root, Point const& p) {
      TriangleRef tab,tbc,tca;
      tab = new(tot_triangles++) Triangle(root->p[0], root->p[1], p);
      tbc = new(tot_triangles++) Triangle(root->p[1], root->p[2], p);
      tca = new(tot_triangles++) Triangle(root->p[2], root->p[0], p);
      set_edge(Edge(tab,0),Edge(tbc,1)); set_edge(Edge(tbc,0),Edge(tca,1));
      set_edge(Edge(tca,0),Edge(tab,1)); set_edge(Edge(tab,2),root->edge[2]);
      set_edge(Edge(tbc,2),root->edge[0]); set_edge(Edge(tca,2),root->edge[1]);
      root->child[0]=tab;root->child[1]=tbc;root->child[2]=tca;
      flip(tab,2); flip(tbc,2); flip(tca,2); }
    void flip(TriangleRef tri, SideRef pi) {
      TriangleRef trj = tri->edge[pi].tri; int pj = tri->edge[pi].side;
      if(!trj || !in_circumcircle(tri->p[0],tri->p[1],tri->p[2],trj->p[pj])) return;
      TriangleRef trk = new(tot_triangles++) Triangle(tri->p[(pi+1)%3], trj->p[pj], tri->p[pi]);
      TriangleRef trl = new(tot_triangles++) Triangle(trj->p[(pj+1)%3], tri->p[pi], trj->p[pj]);
      set_edge(Edge(trk,0), Edge(trl,0));
      set_edge(Edge(trk,1), tri->edge[(pi+2)%3]); set_edge(Edge(trk,2), trj->edge[(pj+1)%3]);
      set_edge(Edge(trl,1), trj->edge[(pj+2)%3]); set_edge(Edge(trl,2), tri->edge[(pi+1)%3]);
      tri->child[0]=trk; tri->child[1]=trl; tri->child[2]=0;
      trj->child[0]=trk; trj->child[1]=trl; trj->child[2]=0;
      flip(trk,1); flip(trk,2); flip(trl,1); flip(trl,2); } };
int n; Point ps[N];
void build(){
  tot_triangles = triange_pool; cin >> n;
  for(int i = 0; i < n; ++ i) scanf("%lf%lf",&ps[i].x,&ps[i].y);
  random_shuffle(ps, ps + n); Triangulation tri;
  for(int i = 0; i < n; ++ i) tri.add_point(ps[i]); }
//The Euclidean minimum spanning tree of a set of points is a subset of the Delaunay triangulation of the same points.
//Connecting the centers of the circumcircles produces the Voronoi diagram.
//No point in P is inside the circumcircle of any triangle.
//Maximize the minimum angle of all the angles of the triangles.