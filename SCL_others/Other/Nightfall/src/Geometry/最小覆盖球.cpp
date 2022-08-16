vector<point3D> vec;
Circle calc() {
	if(vec.empty()) { return Circle(point3D(0, 0, 0), 0);
	}else if(1 == (int)vec.size()) {return Circle(vec[0], 0);
	}else if(2 == (int)vec.size()) {
		return Circle(0.5 * (vec[0] + vec[1]), 0.5 * (vec[0] - vec[1]).len());
	}else if(3 == (int)vec.size()) {
		double r = (vec[0] - vec[1]).len() * (vec[1] - vec[2]).len() * (vec[2] - vec[0]).len() / 2 / fabs(cross(vec[0] - vec[2], vec[1] - vec[2]).len());
		Plane ppp1 = Plane(vec[1] - vec[0], 0.5 * (vec[1] + vec[0]));
		return Circle(intersect(Plane(vec[1] - vec[0], 0.5 * (vec[1] + vec[0])), Plane(vec[2] - vec[1], 0.5 * (vec[2] + vec[1])), Plane(cross(vec[1] - vec[0], vec[2] - vec[0]), vec[0])), r);
	}else {
		point3D o(intersect(Plane(vec[1] - vec[0], 0.5 * (vec[1] + vec[0])), Plane(vec[2] - vec[0], 0.5 * (vec[2] + vec[0])), Plane(vec[3] - vec[0], 0.5 * (vec[3] + vec[0]))));
		return Circle(o, (o - vec[0]).len()); } }
Circle miniBall(int n) {
	Circle res(calc());
	for(int i(0); i < n; i++) {
		if(!in_circle(a[i], res)) { vec.push_back(a[i]);
			res = miniBall(i); vec.pop_back();
			if(i) { point3D tmp(a[i]);
				memmove(a + 1, a, sizeof(point3D) * i);
				a[0] = tmp; } } }
	return res; }
int main() {
	int n; scanf("%d", &n);
	for(int i(0); i < n; i++) a[i].scan();
	sort(a, a + n); n = unique(a, a + n) - a;
	vec.clear(); random_shuffle(a, a + n);
	printf("%.10f\n", miniBall(n).r); }
