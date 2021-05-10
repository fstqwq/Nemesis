/*GAP 1e4 : p(36)  mu(6)
  GAP 1e5 : p(72)  mu(7)
  GAP 1e6 : p(114) mu(8)
  GAP 1e9 : p(282) mu(12)
PCNT: 168/1e3;1229/1e4;9.5;7.8;6.6;5.7;5.0*/
for (int i = 2; i < n; i++) {
	if (!vis[i]) {
		p[++pcnt] = i;
		mu[i] = 1;
	}
	for (int j = 1, k; (k = i * p[j]) < n; j++) {
		vis[k] = 1;
		if (i % p[j] == 0) {
			mu[k] = 0;
			break;
		} else mu[k] = mu[i];
	}
}
