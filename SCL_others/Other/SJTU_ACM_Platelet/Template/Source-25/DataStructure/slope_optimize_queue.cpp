// DP : f[i]=min{f[j]+sqr(sum[i]-sum[j]-l), 0<j<i}
int a[maxn],n,l,q[maxn]; ll sum[maxn],f[maxn];
inline ll sqr(ll x){return x*x;}
#define y(_i) (f[_i] + sqr(sum[_i] + l))
#define x(_i) (2 * sum[_i])
inline db slope(int i,int j){
  return (y(i)-y(j))/(1.0*(x(i)-x(j)));}
int main(){ n=F(); l=F()+1;
  for(int i=1;i<=n;++i)
    {a[i]=F();sum[i]=sum[i-1]+a[i];}
  for(int i=1;i<=n;++i)sum[i]+=i;
  f[0]=0; int h=1,t=1; q[h]=0;
  for(int i=1;i<=n;++i){
    while(h<t&&slope(q[h],q[h+1])<=sum[i])++h;
    f[i]=f[q[h]]+sqr(sum[i]-sum[q[h]]-l);
    while(h<t&&slope(q[t-1],i)<slope(q[t-1],q[t]))
      --t; q[++t] = i;}
  printf("%lld\n",f[n]); return 0; }
