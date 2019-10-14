struct poly { LL a[2]; poly() {} int size() const {return 2;}
    poly(LL x, LL y) {a[0] = x; a[1] = y;} };
poly operator * (poly a, int p) {
    return poly(a.a[0], a.a[1] * p);
}
poly operator - (const poly &a, const poly &b){
    return poly(a.a[0]-b.a[0], a.a[1]-b.a[1]);
}
poly sum_fp(LL l, LL r) { // f(p) = 1 + p
    return poly(r-l+1, (l+r) * (r-l+1) / 2);
}
LL fpk(LL p, LL k) { // f(p^k) = sum{i in 0..k | p^i}
    LL res = 0, q = 1;
    for (int i = 0; i <= k; ++ i) { res += q; q *= p; }
    return res;
}
LL Value(poly p) { return p.a[0] + p.a[1]; }
LL n; int m; vector<poly> A, B; vector<int> P;
//need w = ⌊n/k⌋, about O(w^0.7)
LL calc(LL w, int id, LL f) {
    LL T = w>m ? Value(B[n/w]) : Value(A[w]);
    if (id) T -= Value(A[P[id - 1]]); LL ret = T * f;
    for (int i = id; i < P.size(); ++ i) {
        int p = P[i], e = 1; LL q = (LL) p*p; if (q>w) break;
        ret += calc(w/p, i+1, f * fpk(p, 1));
        while (1) {
            ++ e; LL f2 = f * fpk(p, e); ret+=f2; LL qq = q*p;
            if (qq <= w) {
                ret += calc(w/q, i+1, f2); q = qq;
            } else break; } }
    return ret;
}
void prepare(LL N) { // about O(n^0.67)
    n = N; m = (int) sqrt(n + .5L);
    A.resize(m + 1); B.resize(m + 1);
    P.clear(); vector<int> isp; isp.resize(m + 1, 1);
    for (int i = 1; i <= m; ++ i) {
        A[i] = sum_fp(2, i); B[i] = sum_fp(2, n / i); }
    for (int p = 2; p <= m; ++ p) {
        if (isp[p]) P.push_back(p);
        for (int j : P) { if (j * p > m) break;
            isp[j * p] = 0; if (j % p == 0) break; }
        if (!isp[p]) continue;
        poly d = A[p - 1]; LL p2 = (LL) p * p;
        int to = (int) min(n / p2, (LL) m);
        for (int i = 1; i <= m / p; ++ i)
            B[i] = B[i] - (B[i * p] - d) * p;
        for (int i = m / p + 1; i <= to; ++ i)
            B[i] = B[i] - (A[n / p / i] - d) * p;
        for (int i = m; i >= p2; -- i)
            A[i] = A[i] - (A[i / p] - d) * p; }
}
main() : prepare(n); LL ans = calc(n, 0, 1);
