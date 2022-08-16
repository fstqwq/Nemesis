LL inv(LL a,LL n){LL x,y;exgcd(a,n,x,y);return(x+n)%n;}
LL bsgs(LL a,LL b,LL n){// 在 (a,n)=1 时求最小的 x 使得 a^x mod n=b 
	LL m=sqrt(n+0.5),e=1,i;map<LL,LL>mp;mp[1]=0;
	for(i=1;i<m;i++)if(!mp.count(e=e*a%n))mp[e]=i;
	e=e*a%n;e=inv(e,n);// e=a^m, 求出其逆元后放到等式右边 
	for(i=0;i<m;b=b*e%n,i++)if(mp.count(b))return i*m+mp[b];
	return -1;// 无解 
}LL exbsgs(LL a,LL b,LL n){// 求最小的 x 使 a^x mod n=b 
	LL V,k=0,d,e=1;
	for(;(d=gcd(a,n))!=1;){
		if(b%d)return b==1?0:-1;// 如果 (a,n)=1, 要么 x=0&b=1, 要么无解 
		k++;n=n/d;b=b/d;e=e*a/d%n;
		if(e==b)return k; }// 特判 
	V=bsgs(a,b*inv(e,n)%n,n);return ~V?V+k:V;}// 有解返回 V+k
