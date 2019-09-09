struct P{
	int quad() const { return sgn(y) == 1 || (sgn(y) == 0 && sgn(x) >= 0);}
};
struct L{
	bool onLeft(const P &p) const { return sgn((b - a)*( p - a)) > 0; }
	L push() const{ // push out eps
		const double eps = 1e-10;
		P delta = (b - a).turn90().norm() * eps;
		return L(a - delta, b - delta);
	}	
};
bool sameDir(const L &l0, const L &l1) { 
	return parallel(l0, l1) && sgn((l0.b - l0.a)^(l1.b - l1.a)) == 1; 
}
bool operator < (const P &a, const P &b) {
	if (a.quad() != b.quad())
		return a.quad() < b.quad();
	else 
		return sgn((a*b)) > 0;
}
bool operator < (const L &l0, const L &l1) {
	if (sameDir(l0, l1))
		return l1.onLeft(l0.a);
	else
		return (l0.b - l0.a) < (l1.b - l1.a);
}
bool check(const L &u, const L &v, const L &w) { 
	return w.onLeft(intersect(u, v)); 
}
vector<P> intersection(vector<L> &l) {
	sort(l.begin(), l.end());
	deque<L> q;
	for (int i = 0; i < (int)l.size(); ++i) {
		if (i && sameDir(l[i], l[i - 1])) {
			continue;
		}
		while (q.size() > 1 
			&& !check(q[q.size() - 2], q[q.size() - 1], l[i])) 
				q.pop_back();
		while (q.size() > 1 
			&& !check(q[1], q[0], l[i])) 
				q.pop_front();
		q.push_back(l[i]);
	}
	while (q.size() > 2 
		&& !check(q[q.size() - 2], q[q.size() - 1], q[0]))
			q.pop_back();
	while (q.size() > 2 
		&& !check(q[1], q[0], q[q.size() - 1])) 
			q.pop_front();
	vector<P> ret;
	for (int i = 0; i < (int)q.size(); ++i) 
	ret.push_back(intersect(q[i], q[(i + 1) % q.size()]));
	return ret;
}
