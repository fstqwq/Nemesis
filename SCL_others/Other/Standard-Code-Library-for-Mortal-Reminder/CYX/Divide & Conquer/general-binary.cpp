void solve(int l,int r,std::vector<int> q) {
	if(l == r || q.empty()) {
		for(int i = 0; i < q.size(); i++) ans[q[i]] = l;
	}
	else {
		int mid = (l + r) >> 1;
		std::vector<int> qL, qR;
		backup.clear();
		for(int i = l; i <= mid; i++) {
			Event e = event[i];
			if(e.l <= e.r) add(e.l, e.v), add(e.r + 1, -e.v);
			else add(1, e.v), add(e.r + 1, -e.v), add(e.l, e.v);
		}
		for(int i = 0; i < q.size(); i++) {
			LL val = 0;
			for(int j = 0; j < vec[q[i]].size(); j++) {
				val += count(vec[q[i]][j]);
				if(val >= p[q[i]]) break;
			}
			if(cnt[q[i]] + val >= p[q[i]]) qL.push_back(q[i]);
			else cnt[q[i]] += val, qR.push_back(q[i]);
		}
		for(int i = 0; i < backup.size(); i++) sum[backup[i]] = 0;
		solve(l, mid, qL), solve(mid + 1, r, qR);
	}
}
