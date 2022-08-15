bool equal(const double & x, const double & y) {
	return x + eps > y and y + eps > x;
}
double operator % (const Point & a, const Point & b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}
Point operator * (const Point & a, const Point & b) {
	return Point(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}
struct Circle {
	double r; Point o;
};
struct Plane {
	Point nor;
	double m;
	Plane(const Point & nor, const Point & a) : nor(nor){
		m = nor % a;
	}
};
Point intersect(const Plane & a, const Plane & b, const Plane & c) {
	Point c1(a.nor.x, b.nor.x, c.nor.x), c2(a.nor.y, b.nor.y, c.nor.y), c3(a.nor.z, b.nor.z, c.nor.z), c4(a.m, b.m, c.m);
	return 1 / ((c1 * c2) % c3) * Point((c4 * c2) % c3, (c1 * c4) % c3, (c1 * c2) % c4);
}
bool in(const Point & a, const Circle & b) {
	return sign((a - b.o).len() - b.r) <= 0; 
}	
bool operator < (const Point & a, const Point & b) {
	if(!equal(a.x, b.x)) {
		return a.x < b.x;
	}
	if(!equal(a.y, b.y)) {
		return a.y < b.y;
	}
	if(!equal(a.z, b.z)) {
		return a.z < b.z;
	}
	return false;
}
bool operator == (const Point & a, const Point & b) {
	return equal(a.x, b.x) and equal(a.y, b.y) and equal(a.z, b.z);
}
vector<Point> vec;
Circle calc() {
	if(vec.empty()) {
		return Circle(Point(0, 0, 0), 0);
	}else if(1 == (int)vec.size()) {
		return Circle(vec[0], 0);
	}else if(2 == (int)vec.size()) {
		return Circle(0.5 * (vec[0] + vec[1]), 0.5 * (vec[0] - vec[1]).len());
	}else if(3 == (int)vec.size()) {
		double r((vec[0] - vec[1]).len() * (vec[1] - vec[2]).len() * (vec[2] - vec[0]).len() / 2 / fabs(((vec[0] - vec[2]) * (vec[1] - vec[2])).len()));
		return Circle(intersect(Plane(vec[1] - vec[0], 0.5 * (vec[1] + vec[0])),
				       	Plane(vec[2] - vec[1], 0.5 * (vec[2] + vec[1])),
					Plane((vec[1] - vec[0]) * (vec[2] - vec[0]), vec[0])), r);
	}else {
		Point o(intersect(Plane(vec[1] - vec[0], 0.5 * (vec[1] + vec[0])),
				  Plane(vec[2] - vec[0], 0.5 * (vec[2] + vec[0])),
				  Plane(vec[3] - vec[0], 0.5 * (vec[3] + vec[0]))));
		return Circle(o, (o - vec[0]).len());
	}
}
Circle miniBall(int n) {
	Circle res(calc());
	for(int i(0); i < n; i++) {
		if(!in(a[i], res)) {
			vec.push_back(a[i]);
			res = miniBall(i);
			vec.pop_back();
			if(i) {
				Point tmp(a[i]);
				memmove(a + 1, a, sizeof(Point) * i);
				a[0] = tmp;
			}
		}
	}
	return res;
}
int main() {
	int n;
	sort(a, a + n);
	n = unique(a, a + n) - a;
	vec.clear();
	printf("%.10f\n", miniBall(n).r);
}
