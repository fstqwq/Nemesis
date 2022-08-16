bool ir(int x){return c[F[x]][0]!=x&&c[F[x]][1]!=x;}
void rev(int x){swap(c[x][0],c[x][1]);rv[x]^=1;}
void pd(int x){if(rv[x])rev(c[x][0]),rev(c[x][1]),rv[x]=0;}
void R(int x){
	int y=F[x],k=c[y][0]==x;F[c[y][!k]=c[x][k]]=y;
	F[x]=F[y];if(!ir(y))c[F[y]][c[F[y]][1]==y]=x;
	F[c[x][k]=y]=x;ps(y);
}void dw(int x){if(!ir(x))dw(F[x]);pd(x);}
void sy(int x){for(dw(x);!ir(x);R(x))if(!ir(F[x]))
R(c[F[x]][0]==x^c[F[F[x]]][0]==F[x]?x:F[x]);ps(x);}
int fd(int x){for(acs(x),sy(x);c[x][0];x=c[x][0]);return x;}
void acs(int x){for(o=0;x;c[x][1]=o,ps(x),o=x,x=F[x])sy(x);}
void mrt(int x){acs(x);sy(x);rev(x);}
// 无向图 lk, ct, qu
void lk(int x,int y){mrt(x);F[x]=y;}
void ct(int x,int y){mrt(x);acs(y);sy(y);c[y][0]=F[x]=0;}
int qu(int x,int y){mrt(x);acs(y);sy(y);return V[y];}
// 有向图 lk, ct, qu
void lk(int x,int y){acs(x);sy(x);F[x]=y;} 
void ct(int x){acs(x);sy(x);F[c[x][0]]=0;c[x][0]=0;ps(x);}
int qu(int x){acs(x);sy(x);return V[x];}
void add(int x,int y,int z){mrt(x);acs(y);sy(y);ADD(y,z);}
