int64_t calc(int64_t d, int64_t m, int64_t l, int64_t r) {
    if (l == 0) return 0;
    if (d == 0) return -1;
    if (d * 2 > m) return calc(m - d, m, m - r, m - l);
    if ((l - 1) / d < r / d) return (l - 1) / d + 1;
    int64_t k = calc((-m % d + d) % d, d, l % d, r % d);
    if (k == -1) return -1;
    return (k * m + l - 1) / d + 1;
}
