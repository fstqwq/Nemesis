int l,a[33],p[33],P[33];
//求n! mod pk^tk,返回值U{不包含pk的值,pk出现的次数}
U fac(int k,LL n){
  if(!n)return U{1,0};
  LL x = n/p[k],y = n/P[k],ans = 1; int i;
  if(y){// 求出循环节的答案
    for(i=2;i<P[k];i++) if(i%p[k]) ans = ans*i%P[k];
    ans = Pw(ans,y,P[k]); }
  for(i = y*P[k];i<=n;i++) if(i%p[k]) ans = ans*i%M;
  U z = fac(k,x); return U{ans*z.x%M,x+z.z}; }
LL get(int k,LL n,LL m){// 求 C(n,m) mod pk^tk
  U a = fac(k,n),b = fac(k,m), c = fac(k,n-m);
  return Pw(p[k],a.z-b.z-c.z,P[k])*a.x%P[k]*
         inv(b.x,P[k])%P[k]*inv(c.x,P[k])%P[k]; }
LL CRT(){// CRT 合并答案
  LL d,w,y,x,ans = 0;
  for(int i=1;i<=l;i++)
  w = M/P[i],exgcd(w,P[i],x,y),ans =
    (ans+w*x%M*a[i])%M;
  return (ans+M)%M;}
LL C(LL n,LL m){// 求 C(n,m)
  for(int i=1;i<=l;i++) a[i] = get(i,n,m);
  return CRT();}
LL exLucas(LL n,LL m,int M){
  int jj = M,i;
  // 求 C(n,m)mod M,M=prod(pi^ki), 时间O(pi^kilg^2n)
  for(i = 2;i*i<=jj;i++) if(jj%i==0)
    for(p[++l] = i,P[l] = 1;jj%i==0;P[l] *= p[l])
        jj /= i;
  if(jj>1)l++,p[l] = P[l] = jj; return C(n,m); }
