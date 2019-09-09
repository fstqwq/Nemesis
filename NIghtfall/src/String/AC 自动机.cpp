for(i=0;i<26;i++)c[0][i]=1;//root为1 
for(q[t=1]=1;h<t;)for(x=q[++h],i=0;i<26;i++){
	y=c[x][i];if(!y){c[x][i]=c[F[x]][i];continue;}
	for(k=F[x];!c[k][i];k=F[k]);
	F[y]=c[k][i];dg[y]|=dg[F[y]];q[++t]=y;}