/* Delaunay Triangulation 随机增量算法 :
节点数至少为点数的 6 倍, 空间消耗较大注意计算内存使用
建图的过程在 build 中, 注意初始化内存池和初始三角形 (LOTS)
Triangulation::find 返回包含某点的三角形
Triangulation::add_point 将某点加入三角剖分
某个 Tri 在三角剖分中当且仅当它的 has_ch 为 0
如果要找到三角形 u 的邻域, 则枚举它的所有 u.edge[i].tri, 该条边的两个点为 u.p[(i+1)%3], u.p[(i+2)%3] */
const int N = 100000 + 5, MAX_TRIS = N * 6;
bool in_circum(cp p1, cp p2, cp p3, cp p4) {
 LD u11 = p1.x-p4.x, u21 = p2.x-p4.x, u31 = p3.x-p4.x;
 LD u12 = p1.y-p4.y, u22 = p2.y-p4.y, u32 = p3.y-p4.y;
 LD u13 = sqr(p1.x)-sqr(p4.x) + sqr(p1.y) - sqr(p4.y);
 LD u23 = sqr(p2.x)-sqr(p4.x) + sqr(p2.y) - sqr(p4.y);
 LD u33 = sqr(p3.x)-sqr(p4.x) + sqr(p3.y) - sqr(p4.y);
 LD det = -u13*u22*u31 + u12*u23*u31 + u13*u21*u32 - u11*u23*u32 - u12*u21*u33 + u11*u22*u33;
 return det > eps; }
LD dir(cp a, cp b, cp p) { return det(b-a,p-a);}
typedef int SideRef; struct Tri; typedef Tri* TriRef;
struct Edge {
	TriRef tri; SideRef side; Edge() : tri(0), side(0) {}
	Edge(TriRef tri, SideRef side) : tri(tri), side(side) {} };
struct Tri { // Triangle
	point p[3];Edge edge[3];TriRef ch[3]; Tri(){}
	Tri(cp p0,cp p1,cp p2){
		p[0] = p0; p[1] = p1; p[2] = p2;
				ch[0] = ch[1] = ch[2] = 0; }
	bool has_ch() const { return ch[0] != 0; }
	int num_ch() const {
		return ch[0] == 0 ? 0
			: ch[1] == 0 ? 1
			: ch[2] == 0 ? 2 : 3; }
	bool contains(cp q) const {
		LD a=dir(p[0],p[1],q), b=dir(p[1],p[2],q), c=dir(p[2],p[0],q);
		return sgn(a) >= 0 && sgn(b) >= 0 && sgn(c) >= 0; }
} triange_pool[MAX_TRIS], *tot_tri;
void set_edge(Edge a, Edge b) {
	if (a.tri) a.tri->edge[a.side] = b;
	if (b.tri) b.tri->edge[b.side] = a; }
class Triangulation {
	public:
		Triangulation() {
			const LD LOTS = 1e6; // NOTE: below base triangle
			the_root = new(tot_tri++) Tri (point(-LOTS,-LOTS), point(+LOTS,-LOTS), point(0,+LOTS)); }
		TriRef find(point p) const { return find(the_root,p); }
		void add_point(cp p) { add_point(find(the_root,p),p); }
	private:
		TriRef the_root;
		static TriRef find(TriRef root,cp p){
			for( ; ; ) {
				if (!root->has_ch()) return root;
				else for (int i = 0; i < 3 && root->ch[i] ; ++i)
						if (root->ch[i]->contains(p))
							{root = root->ch[i]; break;} } }
		void add_point(TriRef root, cp p) {
			TriRef tab,tbc,tca;
			tab = new(tot_tri++) Tri(root->p[0], root->p[1], p);
			tbc = new(tot_tri++) Tri(root->p[1], root->p[2], p);
			tca = new(tot_tri++) Tri(root->p[2], root->p[0], p);
			set_edge(Edge(tab,0),Edge(tbc,1));
			set_edge(Edge(tbc,0),Edge(tca,1));
			set_edge(Edge(tca,0),Edge(tab,1));
			set_edge(Edge(tab,2),root->edge[2]);
			set_edge(Edge(tbc,2),root->edge[0]);
			set_edge(Edge(tca,2),root->edge[1]);
			root->ch[0]=tab;root->ch[1]=tbc;root->ch[2]=tca;
			flip(tab,2); flip(tbc,2); flip(tca,2); }
		void flip(TriRef tri, SideRef pi) {
			TriRef trj = tri->edge[pi].tri; int pj = tri->edge[pi].side;
			if(!trj || !in_circum(tri->p[0],tri->p[1],tri->p[2],trj->p[pj])) return;
			TriRef trk = new(tot_tri++) Tri(tri->p[(pi+1)%3], trj->p[pj], tri->p[pi]);
			TriRef trl = new(tot_tri++) Tri(trj->p[(pj+1)%3], tri->p[pi], trj->p[pj]);
			set_edge(Edge(trk,0), Edge(trl,0));
			set_edge(Edge(trk,1), tri->edge[(pi+2)%3]);
			set_edge(Edge(trk,2), trj->edge[(pj+1)%3]);
			set_edge(Edge(trl,1), trj->edge[(pj+2)%3]);
			set_edge(Edge(trl,2), tri->edge[(pi+1)%3]);
			tri->ch[0]=trk; tri->ch[1]=trl; tri->ch[2]=0;
			trj->ch[0]=trk; trj->ch[1]=trl; trj->ch[2]=0;
			flip(trk,1); flip(trk,2); flip(trl,1); flip(trl,2); }
};
int n; point ps[N];
void build(){
	tot_tri = triange_pool; cin >> n;
	for(int i = 0; i < n; ++ i) scanf("%lf%lf",&ps[i].x,&ps[i].y);
	random_shuffle(ps, ps + n); Triangulation tri;
	for(int i = 0; i < n; ++ i) tri.add_point(ps[i]); }
//The Euclidean minimum spanning tree of a set of points is a subset of the Delaunay triangulation of the same points.
//Connecting the centers of the circumcircles produces the Voronoi diagram.
//No point in P is inside the circumcircle of any triangle.
//Maximize the minimum angle of all the angles of the triangles.
