void dfs(int x,int fa){
  for(int i=1;i<=20;++i){
  if((1<<i)>dep[x])break;
    Fa[x][i]=Fa[Fa[x][i-1]][i-1];}
  for(int to : e[x])if(to!=fa){
    Fa[to][0]=x;dep[to]=dep[x]+1;dfs(to,x);
    if (depmax[to]>depmax[son[x]])son[x]=to;}
  depmax[x]=depmax[son[x]]+1;}
std::vector<int> v[maxn];
void dfs2(int x,int fa) { dfn[x]=++timer;
  pos[timer]=x;top[x]=son[fa]==x?top[fa]:x;
  if (top[x]==x){int now=fa; v[x].push_back(x);
    for(int i=1;now&&i<=depmax[x]+1;++i){
      v[x].push_back(now); now=Fa[now][0];}}
  if(son[x])dfs2(son[x],x);
  for (int to : e[x])if(to!=fa&&to!=son[x])
    dfs2(to,x);}
int jump(int x,int k){if(!k)return x;
  int l=Log[k];x=Fa[x][l];k-=1<<l;
  if (k){if(dep[x]-dep[top[x]]>=k)x=pos[dfn[x]-k];
    else k-=dep[x]-dep[top[x]]; x=v[top[x]][k];}
  return x;}
int main(){
  Log[0]=-1;for(int i=1;i<=n;++i)Log[i]=Log[i>>1]+1;
  dep[1]=1; dfs(1,0); dfs2(1,0);}
