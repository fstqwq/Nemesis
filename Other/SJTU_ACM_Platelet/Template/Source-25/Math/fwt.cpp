void fwt(int n,int *x,bool inv=false){
  for(int i=0;i<n;i++)for(int j=0;j<(1<<n);j++)
	if((j>>i)&1){int p=x[j^(1<<i)],q=x[j];
	   if(!inv){
	     x[j^(1<<i)]=p-q;x[j]=p+q;//xor
	     x[j^(1<<i)]=p;x[j]=p+q;//or
	     x[j^(1<<i)]=p+q;x[j]=q;//and
	   }else{
	     x[j^(1<<i)]=(p+q)>>1;x[j]=(q-p)>>1;//xor
	     x[j^(1<<i)]=p;x[j]=q-p;//or
	     x[j^(1<<i)]=p-q;x[j]=q;//and
	   }}}
void solve(int n,int *a,int *b,int *c){
  fwt(n,a);fwt(n,b);
  for(int i=0;i<(1<<n);i++)c[i]=a[i]*b[i];
  fwt(n,c,1);}
