void gs(int x,int f=0){
  sz[x]=1;
  for (int to:e[x]){
    if(to==f)continue;
    gs(to,x); sz[x]+=sz[to];
    if(sz[to]>sz[son[x]])son[x]=to;}}
void edt(int x,int f,int v){
    cc[col[x]]+=v;
    for (int to:e[x])
      if(to!=f&&to!=skip) edt(to,x,v);}
void dfs(int x,int f=0,bool kep=0){
    for(int to:e[x])
        if(to!=f&&to!=son[x]) dfs(to,x);
    if(son[x]) dfs(son[x],x,1),skip=son[x];
    edt(x,f,1); anss[x]=cc[ks[x]]; skip=0;
    if(!kep) edt(x,f,-1);}
