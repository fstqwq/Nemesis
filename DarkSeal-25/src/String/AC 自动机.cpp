void build() {
    int he = 0, ta = 1; q[he] = 1; fail[0] = 1;
    while (he < ta) {
        int x = q[he++];
        for (int i = 0; i < A; i++) {
            int to = t[x][i], j = fail[x];
            if (!to) t[x][i] = t[fail[x]][i];
            else { while (!t[j][i]) j = fail[j];
                fail[to] = t[j][i];
                q[ta++] = to; }}}}
