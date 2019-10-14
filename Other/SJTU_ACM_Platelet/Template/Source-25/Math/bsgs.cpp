const int mod = 19260817;
struct Hash{Hash *next;int key,val;
} *last[mod],mem[100000],*tot = mem;
inline void insert(int x,int v){
  *++tot = (Hash){last[x%mod],x,v};
  last[x%mod] = tot;}
inline int query(int x){
  for(Hash *iter=last[x%mod];iter;iter=iter->next)
    if(iter->key==x) return iter->val;return -1;}
inline void del(int x){last[x%mod]=0;}
int main(){
  for(;T;--T){
    int y,z,p; scanf("%d%d%d",&y,&z,&p);
    int m = (int)sqrt(p*1.0);
    y %= p; z %= p;
    if(!y&&!z){puts("0");continue; }
    if(!y){puts("NoSol");continue; }
    int pw = 1, ans = -1;
    for(int i = 0;i<m;++i,pw = 1ll*pw*y%p)
      insert(1ll*z*pw%p,i);
    for(int i = 1,t,pw2 = pw;i<=p/m+1;
        ++i,pw2 = 1ll*pw2*pw%p)
      if((t = query(pw2))!=-1){
        ans = i*m-t; break; }
    if(ans==-1) puts("NoSol");
    else printf("%d\n",ans);tot = mem; pw = 1;
    for(int i = 0;i<m;++i,pw = 1ll*pw*y%p)
      del(1ll*z*pw%p); }return 0;}
