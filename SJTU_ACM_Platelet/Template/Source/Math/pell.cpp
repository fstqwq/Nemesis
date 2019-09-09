std::pair<int64_t, int64_t> pell(int64_t n) {
    static int64_t p[N], q[N], g[N], h[N], a[N];
    p[1] = q[0] = h[1] = 1;
    p[0] = q[1] = g[1] = 0;
    a[2] = std::sqrt(n) + 1e-7L;
    for (int i = 2; true; i++) {
        g[i] = -g[i - 1] + a[i] * h[i - 1];
        h[i] = (n - g[i] * g[i]) / h[i - 1];
        a[i + 1] = (g[i] + a[2]) / h[i];
        p[i] = a[i] * p[i - 1] + p[i - 2];
        q[i] = a[i] * q[i - 1] + q[i - 2];
        if (p[i] * p[i] - n * q[i] * q[i] == 1)
            return std::make_pair(p[i], q[i]);
    }
}
