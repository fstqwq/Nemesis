int x,y,t,tot,fir[N],d1[N],d2[N],q[M],la[M],ne[M],va[M];bool v[M];
void ins(int x,int y,int z){/*ADDEDGE*/d1[x]++;d2[y]++;}
void dfs(int x){
    for(int i=fir[x];i;i=fir[x]){
        for(;i&&v[abs(va[i])];i=ne[i]);fir[x]=i; // 将已经走过的边删去
        if(i)v[abs(va[i])]=1,dfs(la[i]),q[++t]=va[i];}// 走第一个未走过的边
}
void Eular(p,n,m){
    //p=1 是无向图, p=2 是有向图 n 是点数, m 是边数
    fr(i,1,m)if(rd(x,y),ins(x,y,i),p==1)ins(y,x,-i);
    fr(i,1,n)if(p==1&&d1[i]%2||p==2&&d1[i]^d2[i])
        return puts("NO"),0;// 不合法情况
    dfs(la[1]); // 从一条边开始找
    if(t<m)return puts("NO"),0; // 没有欧拉回路
    for(puts("YES");t;printf("%d ",q[t--]));} // 输出方案, 正数是正向边, 负数是反向边
