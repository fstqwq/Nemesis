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
			bool good = !turn_left_strict(ii, jj, kk);
			for (auto x : {u - (jj - u), jj + (jj - u)})
				good &= !(   turn_left_strict(ii, jj, x)
				          && turn_left_strict(jj, kk, x));
			if (!good) far = min(far, dis(u, jj));
		} } return far; }
bool in_polygon (cp u, cp v) {
	// assert : u, v in polygon, respectively
	for (int i = 0; i < n; i++) {
		int j = (i + 1) % n, k = (i + 2) % n;
		cp ii = p[i], jj = p[j], kk = p[k];
		if (inter_judge_strict({u, v}, {ii, jj})) return 0;
		if (point_on_segment (jj, {u, v})) {
			bool good = true, left = turn_left(ii, jj, kk);
			for (auto x : {u, v})
				if (left)
					good &=    turn_left(ii, jj, x)
					        && turn_left(jj, kk, x);
				else
					good &= !(   turn_left_strict(jj, x, kk)
					          && turn_left_strict(jj, ii, x));
			if (!good) return 0;
		} } return 1; }
void work() {
    for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) if (i != j) {
			if (!in_polygon(p[i], p[j])) continue;
			LD ret = get_far(i,j)+get_far(j,i)-dis(p[i],p[j]);
			ans = max(ans, ret); } }