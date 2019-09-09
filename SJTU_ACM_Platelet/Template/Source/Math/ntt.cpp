const int N = 1e6 + 10;
const int64_t MOD = 998244353, G = 3;
int rev[N];

int64_t powMod(int64_t a, int64_t exp) {
    int64_t ans = 1;
    while (exp) {
        if (exp & 1)
            (ans *= a) %= MOD;
        (a *= a) %= MOD;
        exp >>= 1;
    }
    return ans;
}

void number_theoretic_transform(int64_t *p, int n, int idft) {
    for (int i = 0; i < n; i++)
        if (i < rev[i])
            std::swap(p[i], p[rev[i]]);
    for (int j = 1; j < n; j <<= 1) {
        static int64_t wn1, w, t0, t1;
        wn1 = powMod(G, (MOD - 1) / (j << 1));
        if (idft == -1)
            wn1 = powMod(wn1, MOD - 2);
        for (int i = 0; i < n; i += j << 1) {
            w = 1;
            for (int k = 0; k < j; k++) {
                t0 = p[i + k];
                t1 = w * p[i + j + k] % MOD;
                p[i + k] = (t0 + t1) % MOD;
                p[i + j + k] = (t0 - t1 + MOD) % MOD;
                (w *= wn1) %= MOD;
            }
        }
    }
    if (idft == -1) {
        int nInv = powMod(n, MOD - 2);
        for (int i = 0; i < n; i++)
            (p[i] *= nInv) %= MOD;
    }
}

int64_t *ntt_main(int64_t *a, int64_t *b, int n, int m) {
    static int64_t aa[N], bb[N];
    static int nn, len;
    len = 0;
    for (nn = 1; nn < m + n; nn <<= 1)
        len++;
    for (int i = 0; i < nn; i++) {
        aa[i] = a[i];
        bb[i] = b[i];
    }
    rev[0] = 0;
    for (int i = 1; i < nn; i++)
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (len - 1));
    number_theoretic_transform(aa, nn, 1);
    number_theoretic_transform(bb, nn, 1);
    for (int i = 0; i < nn; i++)
        (aa[i] *= bb[i]) %= MOD;
    number_theoretic_transform(aa, nn, -1);
    return aa;
}
