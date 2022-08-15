const int N = 100000 + 5, MAX_TRIS = N * 6;
const double eps = 1e-6, PI = acos(-1.0);
struct P {
	double x,y; P():x(0),y(0){}
    P(double x, double y):x(x),y(y){}
	bool operator ==(P const& that)const {return x==that.x&&y==that.y;}
};
inline double sqr(double x) { return x*x; }
double dist_sqr(P const& a, P const& b){return sqr(a.x-b.x)+sqr(a.y-b.y);}
bool in_circumcircle(P const& p1, P const& p2, P const& p3, P const& p4) {//p4 in C(p1,p2,p3)
	double u11 = p1.x - p4.x, u21 = p2.x - p4.x, u31 = p3.x - p4.x;
	double u12 = p1.y - p4.y, u22 = p2.y - p4.y, u32 = p3.y - p4.y;
	double u13 = sqr(p1.x) - sqr(p4.x) + sqr(p1.y) - sqr(p4.y);
	double u23 = sqr(p2.x) - sqr(p4.x) + sqr(p2.y) - sqr(p4.y);
	double u33 = sqr(p3.x) - sqr(p4.x) + sqr(p3.y) - sqr(p4.y);
	double det = -u13*u22*u31 + u12*u23*u31 + u13*u21*u32 - u11*u23*u32 - u12*u21*u33 + u11*u22*u33;
	return det > eps;
}
double side(P const& a, P const& b, P const& p) { return (b.x-a.x)*(p.y-a.y) - (b.y-a.y)*(p.x-a.x);}
typedef int SideRef; struct Triangle; typedef Triangle* TriangleRef;
struct Edge {
	TriangleRef tri; SideRef side; Edge() : tri(0), side(0) {}
	Edge(TriangleRef tri, SideRef side) : tri(tri), side(side) {}
};
struct Triangle {
	P p[3]; Edge edge[3]; TriangleRef children[3]; Triangle() {}
	Triangle(P const& p0, P const& p1, P const& p2) {
		p[0] = p0; p[1] = p1; p[2] = p2;
        children[0] = children[1] = children[2] = 0;
	}
	bool has_children() const { return children[0] != 0; }
	int num_children() const {
		return children[0] == 0 ? 0
			: children[1] == 0 ? 1
			: children[2] == 0 ? 2 : 3;
	}
	bool contains(P const& q) const {
		double a=side(p[0],p[1],q), b=side(p[1],p[2],q), c=side(p[2],p[0],q);
		return a >= -eps && b >= -eps && c >= -eps;
	}
} triange_pool[MAX_TRIS], *tot_triangles;
void set_edge(Edge a, Edge b) {
	if (a.tri) a.tri->edge[a.side] = b;
	if (b.tri) b.tri->edge[b.side] = a;
}
class Triangulation {
	public:
		Triangulation() {
			const double LOTS = 1e6;//初始为极大三角形
			the_root = new(tot_triangles++) Triangle(P(-LOTS,-LOTS),P(+LOTS,-LOTS),P(0,+LOTS));
		}
		TriangleRef find(P p) const { return find(the_root,p); }
		void add_point(P const& p) { add_point(find(the_root,p),p); }
	private:
		TriangleRef the_root;
		static TriangleRef find(TriangleRef root, P const& p) {
			for( ; ; ) {
				if (!root->has_children()) return root;
				else for (int i = 0; i < 3 && root->children[i] ; ++i)
						if (root->children[i]->contains(p))
							{root = root->children[i]; break;}
			}
		}
		void add_point(TriangleRef root, P const& p) {
			TriangleRef tab,tbc,tca;
			tab = new(tot_triangles++) Triangle(root->p[0], root->p[1], p);
			tbc = new(tot_triangles++) Triangle(root->p[1], root->p[2], p);
			tca = new(tot_triangles++) Triangle(root->p[2], root->p[0], p);
			set_edge(Edge(tab,0),Edge(tbc,1)); set_edge(Edge(tbc,0),Edge(tca,1));
			set_edge(Edge(tca,0),Edge(tab,1)); set_edge(Edge(tab,2),root->edge[2]);
			set_edge(Edge(tbc,2),root->edge[0]); set_edge(Edge(tca,2),root->edge[1]);
			root->children[0]=tab; root->children[1]=tbc; root->children[2]=tca;
			flip(tab,2); flip(tbc,2); flip(tca,2);
		}
		void flip(TriangleRef tri, SideRef pi) {
			TriangleRef trj = tri->edge[pi].tri; int pj = tri->edge[pi].side;
			if(!trj || !in_circumcircle(tri->p[0],tri->p[1],tri->p[2],trj->p[pj])) return;
			TriangleRef trk = new(tot_triangles++) Triangle(tri->p[(pi+1)%3], trj->p[pj], tri->p[pi]);
			TriangleRef trl = new(tot_triangles++) Triangle(trj->p[(pj+1)%3], tri->p[pi], trj->p[pj]);
			set_edge(Edge(trk,0), Edge(trl,0));
			set_edge(Edge(trk,1), tri->edge[(pi+2)%3]); set_edge(Edge(trk,2), trj->edge[(pj+1)%3]);
			set_edge(Edge(trl,1), trj->edge[(pj+2)%3]); set_edge(Edge(trl,2), tri->edge[(pi+1)%3]);
			tri->children[0]=trk; tri->children[1]=trl; tri->children[2]=0;
			trj->children[0]=trk; trj->children[1]=trl; trj->children[2]=0;
			flip(trk,1); flip(trk,2); flip(trl,1); flip(trl,2);
		}
};
int n; P ps[N];
void build(){
	tot_triangles = triange_pool; cin >> n;
	for(int i = 0; i < n; ++ i) scanf("%lf%lf",&ps[i].x,&ps[i].y);
	random_shuffle(ps, ps + n); Triangulation tri;
	for(int i = 0; i < n; ++ i) tri.add_point(ps[i]);
}
