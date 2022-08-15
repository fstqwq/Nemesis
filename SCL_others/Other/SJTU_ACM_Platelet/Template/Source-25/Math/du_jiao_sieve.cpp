int phi[maxn],pr[maxn/10],prcnt;ll sph[maxn];
bool vis[maxn];
const int moha = 3333331;
struct Hash {
  Hash *next;int ps;ll ans;
} *last1[moha],mem[moha],*tot = mem;
inline ll S1(int n){
  if(n<maxn)return sph[n];
  for(Hash *it=last1[n%moha];it;it=it->next)
    if(it->ps==n)return it->ans;
  ll ret=1ll*n*(n+1ll)/2;
  for(ll i=2,j;i<=n;i=j+1){
    j=n/(n/i);res-=S1(n/i)*(j-i+1);
  }
  *++tot=(Hash){last1[n%moha],n,ret};
  last1[n%moha]=tot;return ret;
}
