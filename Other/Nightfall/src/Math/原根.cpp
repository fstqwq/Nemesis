bool ok(LL g,LL p){// 验证 g 是否是 p 的原根 
	for(int i=1;i<=t;i++)if(Pw(g,(p-1)/q[i],p)==1)return 0;
	return 1;
}LL primitive_root(LL p){// 求 p 的原根 
	LL i,n=p-1,g=1;t=0;
	for(i=2;i*i<=n;i++)if(n%i==0)for(q[++t]=i;n%i==0;n/=i);
	if(n!=1)q[++t]=n;
	for(;;g++)if(ok(g,p))return g;}
//当$gcd(a,m)=1$时, 使$a^x\equiv 1(mod m)$成立最小正整数$x$称为$a$对于模$m$的阶, 记$ord_m(a)$.
//阶的性质: $a^n\equiv 1(mod\ m)$充要条件是$ord_m(a)|n$, 可推出$ord_m(a)|\psi(m)$.
//当$ord_m(g)=\psi(m)$时, 则称$g$是模$m$的一个原根, 则$g^0,g^1,...,g^{\psi(m)-1}$覆盖了$m$以内所有与$m$互质的数.
//并不是所有数都存在原根, 模意义下存在原根充要条件: $m=2,4,p^k,2p^k$. 其中为$p$奇素数, $k$为正整数.