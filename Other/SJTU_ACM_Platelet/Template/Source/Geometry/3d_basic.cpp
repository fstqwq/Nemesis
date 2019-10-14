struct P {
	double x, y, z;
	P(){}
	P(double _x,double _y,double _z):x(_x),y(_y),z(_z){}
	double len2(){
		return (x*x+y*y+z*z);
	}
	double len(){
		return sqrt(x*x+y*y+z*z);
	}
};
bool operator==(P a,P b){
	return sgn(a.x-b.x)==0 && sgn(a.y-b.y)==0 && sgn(a.z-b.z)==0 ;
}
bool operator<(P a,P b){
	return sgn(a.x-b.x) ? a.x<b.x :(sgn(a.y-b.y)?a.y<b.y :a.z<b.z);
}
P operator+(P a,P b){
	return P(a.x+b.x,a.y+b.y,a.z+b.z);
}
P operator-(P a,P b){
	return P(a.x-b.x,a.y-b.y,a.z-b.z);
}
P operator*(P a,double b){
	return P(a.x*b,a.y*b,a.z*b);
}
P operator/(P a,double b){
	return P(a.x/b,a.y/b,a.z/b);
}
P operator*(const P &a, const P &b) {
	return P(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}
double operator^(const P &a, const P &b) {
	return a.x*b.x+a.y*b.y+a.z*b.z;
}

double dis(P a,P b){return (b-a).len();}
double dis2(P a,P b){return (b-a).len2();}

// 3D line intersect
P intersect(const P &a0, const P &b0, const P &a1, const P &b1) {
    double t = ((a0.x - a1.x) * (a1.y - b1.y) - (a0.y - a1.y) * (a1.x - b1.x)) / ((a0.x - b0.x) * (a1.y - b1.y) - (a0.y - b0.y) * (a1.x - b1.x));
	return a0 + (b0 - a0) * t;
}
// area-line intersect
P intersect(const P &a, const P &b, const P &c, const P &l0, const P &l1) {

	P p = (b-a)*(c-a); // 平面法向量
	double t = (p^(a-l0)) / (p^(l1-l0));
	return l0 + (l1 - l0) * t;
}
