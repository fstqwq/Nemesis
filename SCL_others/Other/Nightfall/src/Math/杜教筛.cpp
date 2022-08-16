LL P(LL n){// 求欧拉函数前缀和 
	if(n<M)return phi[n];//M=n^(2/3),phi[n] 为预处理前缀和 
	LL x=1ll*n*(n+1)/2,i=2,la;
	for(;i<=n;i=la+1)la=n/(n/i),x-=P(n/i)*(la-i+1);
	return x;}
LL U(LL n){// 求莫比乌斯函数前缀和 
	if(n<M)return u[n];// 预处理的前缀和 
	LL x=1,i=2,la;
	for(;i<=n;i=la+1)la=n/(n/i),x-=U(n/i)*(la-i+1);
	return x;}