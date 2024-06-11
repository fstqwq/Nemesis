bool in_polygon (cp u, cp v) {
	// u, v in polygon; p contain those u, v on border
	for (int i = 0; i < n; i++) {
		int j = (i + 1) % n, k = (i + 2) % n;
		cp ii = p[i], jj = p[j], kk = p[k];
		if (inter_judge_strict({u, v}, {ii, jj})) return 0;
		if (point_on_segment (jj, {u, v})) {
			bool good = true, left = turn (ii, jj, kk) >= 0;
			for (auto x : {u, v})
				if (left)
					good &=    turn(ii, jj, x) >= 0
					        && turn(jj, kk, x) >= 0;
				else
					good &= !(   turn(jj, x, kk) > 0
					          && turn(jj, ii, x) > 0);
			if (!good) return 0;
		} } return 1; }
LD get_far (int uid, int vid) {
	// u -> v in polygon, check the ray u -> polygon
	cp u = p[uid], v = p[vid];
	LD far = 1e9;
	for (int i = 0; i < n; i++) {
		int j = (i + 1) % n, k = (i + 2) % n;
		cp ii = p[i], jj = p[j], kk = p[k];
		if (two_side (ii, jj, {u, v})) {
			LD s1 = det(jj - ii, u - ii);
			LD s2 = det(jj - ii, v - ii);
			if (sgn(s1 - s2) && sgn(s1) != sgn(s2 - s1))
				far = min(far,
				          dis(u, line_inter({ii,jj},{u,v})));}
		if (j != uid && point_on_ray (jj, {u, v})) {
			bool good = turn(ii, jj, kk) <= 0;
			for (auto x : {u - (jj - u), jj + (jj - u)})
				good &= !(   turn(ii, jj, x) > 0
				          && turn(jj, kk, x) > 0);
			if (!good) far = min(far, dis(u, jj));
		} } return far; }
void work() {
    for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) if (i != j) {
			if (!in_polygon(p[i], p[j])) continue;
			LD ret = get_far(i,j)+get_far(j,i)-dis(p[i],p[j]);
			ans = max(ans, ret); } }