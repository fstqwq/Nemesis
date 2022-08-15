int64_t ex_bsgs(int64_t a, int64_t b, int64_t p) {
    if (b == 1)
        return 0;
    int64_t t, d = 1, k = 0;
    while ((t = std::__gcd(a, p)) != 1) {
        if (b % t) return -1;
        k++, b /= t, p /= t, d = d * (a / t) % p;
        if (b == d) return k;
    }
    map.clear();
    int64_t m = std::ceil(std::sqrt((long double) p));
    int64_t a_m = pow_mod(a, m, p);
    int64_t mul = b;
    for (int j = 1; j <= m; j++) {
        (mul *= a) %= p;
        map[mul] = j;
    }
    for (int i = 1; i <= m; i++) {
        (d *= a_m) %= p;
        if (map.count(d))
            return i * m - map[d] + k;
    }
    return -1;
}

int main() {
    int64_t a, b, p;
    while (scanf("%lld%lld%lld", &a, &b, &p) != EOF)
        printf("%lld\n", ex_bsgs(a, b, p));
    return 0;
}
