#include <cstdio>
#include <map>

#define R register
#define maxn 2000010
typedef long long ll;
int phi[maxn], miu[maxn], pr[maxn / 10], prcnt;
ll sph[maxn], smi[maxn];
bool vis[maxn];
const int moha = 3333331;
struct Hash {
    Hash *next;
    int ps; ll ans;
} *last1[moha], *last2[moha], mem[moha], *tot = mem;
inline ll S1(R int n)
{
    if (n < maxn) return sph[n];
    for (R Hash *iter = last1[n % moha]; iter; iter = iter -> next)
        if (iter -> ps == n) return iter -> ans;

    R ll ret = 1ll * n * (n + 1ll) / 2;
    for (R ll i = 2, j; i <= n; i = j + 1)
    {
        j = n / (n / i);
        ret -= S1(n / i) * (j - i + 1);
    }
    *++tot = (Hash) {last1[n % moha], n, ret}; last1[n % moha] = tot;
    return ret;
}
inline ll S2(R int n)
{
    if (n < maxn) return smi[n];
    for (R Hash *iter = last2[n % moha]; iter; iter = iter -> next)
        if (iter -> ps == n) return iter -> ans;

    R ll ret = 1;
    for (R ll i = 2, j; i <= n; i = j + 1)
    {
        j = n / (n / i);
        ret -= (j - i + 1) * S2(n / i);
    }
    *++tot = (Hash) {last2[n % moha], n, ret}; last2[n % moha] = tot;
    return ret;
}
int main()
{
    R int T; scanf("%d", &T);
    phi[1] = sph[1] = 1;
    miu[1] = smi[1] = 1;
    for (R int i = 2; i < maxn; ++i)
    {
        if (!vis[i]) pr[++prcnt] = i, phi[i] = i - 1, miu[i] = -1;
        sph[i] = sph[i - 1] + phi[i];
        smi[i] = smi[i - 1] + miu[i];
        for (R int j = 1; j <= prcnt && 1ll * i * pr[j] < maxn; ++j)
        {
            vis[i * pr[j]] = 1;
            if (i % pr[j])
            {
                phi[i * pr[j]] = phi[i] * (pr[j] - 1);
                miu[i * pr[j]] = -miu[i];
            }
            else
            {
                phi[i * pr[j]] = phi[i] * pr[j];
                miu[i * pr[j]] = 0;
                break;
            }
        }
    }
    for (; T; --T)
    {
        R int N; scanf("%d", &N);
        printf("%lld %lld\n", S1(N), S2(N));
    }
    return 0;
}
