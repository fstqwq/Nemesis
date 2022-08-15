#include <cstdio>

#define R register
typedef long long ll;
int pw0[10], pw2[10], pw5[10];
int counter;
inline int qpow(R int base, R ll power, R int mod)
{
    R int ret = 1;
    for (; power; power >>= 1, base = 1ll * base * base % mod)
        power & 1 ? ret = 1ll * ret * base % mod : 0;
    return ret;
}
int mod, k;
void exgcd(R int a, R int b, R int &x, R int &y)
{
    if (!b) {x = 1, y = 0; return ;}
    exgcd(b, a % b, y, x);
    y -= a / b * x;
}
inline int inv(R int a, R int p)
{
    R int x, y;
    exgcd(a, p, x, y);
    return (x % p + p) % p;
}
int f2[10][1024], f5[10][1953125];
inline int fac(R ll n, R int fact, R int p, R int pk, R int *fk)
{
    if (!n) return 1;
    R ll y = n / pk;
    R int ret = 1ll * qpow(fact, y, pk) * fk[n % pk] % pk;
    return 1ll * fac(n / p, fact, p, pk, fk) * ret % pk;
}
int ft2[10], ft5[10];
inline int Lucas(R ll n, R ll m, R int p, R int pk, R bool div)
{
    R ll num = 0;
    for (R ll tmp = p; tmp <= n; tmp *= p) num += n / tmp;
    for (R ll tmp = p; tmp <= m; tmp *= p) num -= m / tmp;
    for (R ll tmp = p; tmp <= n - m; tmp *= p) num -= (n - m) / tmp;
    
    R int fact = p == 2 ? ft2[k] : ft5[k],
          *fk  = p == 2 ? f2[k]  : f5[k],
          fa = 1, fb, fc;
    if (div)
    {
        if (p == 2) --num;
        else fa = inv(2, pk);
    }
    if (num >= k) return 0;

    fa = 1ll * fa * fac(n, fact, p, pk, fk) % pk;
    fb = fac(m, fact, p, pk, fk);
    fc = fac(n - m, fact, p, pk, fk);
    fb = inv(fb, pk); fc = inv(fc, pk);
    

    return 1ll * fa * fb % pk * fc % pk * qpow(p, num, pk) % pk;
}
inline int C(R ll n, R ll m, R bool div = 0)
{
    if (m > n) return 0;
//    printf("C(%lld, %lld) %d\n", n, m, div);
    R int C2 = Lucas(n, m, 2, pw2[k], div);
    R int C5 = Lucas(n, m, 5, pw5[k], div);
//    printf("%d %d\n", C2, C5);
    R int t2 = inv(pw5[k], pw2[k]);
    R int t5 = inv(pw2[k], pw5[k]);
    R int ans = (1ll * C2 * pw5[k] % mod * t2 + 1ll * C5 * pw2[k] % mod * t5) % mod;
//    printf("%d\n", ans);
    return ans;
}
int main()
{
    R ll a, b;
    pw0[0] = pw2[0] = pw5[0] = 1;
    for (R int i = 1; i < 10; ++i)
        pw0[i] = pw0[i - 1] * 10,
        pw2[i] = pw2[i - 1] * 2,
        pw5[i] = pw5[i - 1] * 5;

    for (R int i = 1; i < 10; ++i)
    {
        f2[i][0] = 1;
        for (R int j = 1; j < pw2[i]; ++j)
            f2[i][j] = 1ll * f2[i][j - 1] * (j % 2 ? j : 1) % pw2[i];
        ft2[i] = f2[i][pw2[i] - 1];
    }
    for (R int i = 1; i < 10; ++i)
    {
        f5[i][0] = 1;
        for (R int j = 1; j < pw5[i]; ++j)
            f5[i][j] = 1ll * f5[i][j - 1] * (j % 5 ? j : 1) % pw5[i];
        ft5[i] = f5[i][pw5[i] - 1];
    }

    while (scanf("%lld%lld%d", &a, &b, &k) != EOF)
    {
        char str[10];
        R int ans = 0;
        mod = pw0[k];
        ans = qpow(2, a + b - 1, mod);
        if (a == b) (ans += mod - C(a + a, a, 1)) %= mod;
        else
        {
            if (((a + b) & 1) == 0) (ans += C(a + b, (a + b) / 2, 1)) %= mod;
            for (R ll j = (a + b) / 2 + 1; j < a; ++j)
                (ans += C(a + b, j)) %= mod;
        }
        sprintf(str, "%%0%dd\n", k);
        printf(str, ans);
    }
    return 0;
}
