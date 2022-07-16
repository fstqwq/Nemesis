int C; circle c[MAXN]; double area[MAXN];
struct event {
	point p; double ang; int delta;
	event (point p = point (), double ang = 0, int delta = 0) : p(p), ang(ang), delta(delta) {}
	bool operator < (const event &a) { return ang < a.ang; } };
void addevent(cc a, cc b, vector<event> &evt, int &cnt) {
	double d2 = (a.c - b.c).dis2(), dRatio = ((a.r - b.r) * (a.r + b.r) / d2 + 1) / 2,
		pRatio = sqrt (max (0., -(d2 - sqr(a.r - b.r)) * (d2 - sqr(a.r + b.r)) / (d2 * d2 * 4)));
	point d = b.c - a.c, p = d.rot(PI / 2),
		q0 = a.c + d * dRatio + p * pRatio,
		q1 = a.c + d * dRatio - p * pRatio;
	double ang0 = atan2 ((q0 - a.c).y, (q0 - a.c).x), ang1 = atan2 ((q1 - a.c).y, (q1 - a.c).x);
	evt.emplace_back(q1,ang1,1); evt.emplace_back(q0,ang0,-1);
	cnt += ang1 > ang0; }
bool issame(cc a, cc b) {
	return sgn((a.c-b.c).dis()) == 0 && sgn(a.r-b.r) == 0; }
bool overlap(cc a, cc b) { 
	return sgn(a.r - b.r - (a.c - b.c).dis()) >= 0; }
bool intersect(cc a, cc b) { 
	return sgn((a.c - b.c).dis() - a.r - b.r) < 0; }
void solve() {
	fill (area, area + C + 2, 0);
	for (int i = 0; i < C; ++i) { int cnt = 1;
		vector<event> evt;
		for (int j=0; j<i; ++j) if (issame(c[i],c[j])) ++cnt;
		for (int j = 0; j < C; ++j)
			if (j != i && !issame(c[i], c[j]) && overlap(c[j], c[i])) ++cnt;
		for (int j = 0; j < C; ++j)
			if (j != i && !overlap(c[j], c[i]) && !overlap(c[i], c[j]) && intersect(c[i], c[j]))
				addevent(c[i], c[j], evt, cnt);
		if (evt.empty()) area[cnt] += PI * c[i].r * c[i].r;
		else {
			sort(evt.begin(), evt.end());
			evt.push_back(evt.front());
			for (int j = 0; j + 1 < (int)evt.size(); ++j) {
				cnt += evt[j].delta;
				area[cnt] += det(evt[j].p,evt[j + 1].p) / 2;
				double ang = evt[j + 1].ang - evt[j].ang;
				if (ang < 0) ang += PI * 2;
				area[cnt] += ang * c[i].r * c[i].r / 2 - sin(ang) * c[i].r * c[i].r / 2; } } } }
