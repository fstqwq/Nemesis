int d[N];bool v[N],g[N];
int get(int&s,int&t){
    CL(d);CL(v);int i,j,k,an,mx;
    for(i=1;i<=n;i++){ k=mx=-1;
        for(j=1;j<=n;j++)if(!g[j]&&!v[j]&&d[j]>mx)k=j,mx=d[j];
        if(k==-1)return an;
        s=t;t=k;an=mx;v[k]=1;
        for(j=1;j<=n;j++)if(!g[j]&&!v[j])d[j]+=w[k][j];
    }return an;}
int mincut(int n,int w[N][N]){
    //n 为点数, w[i][j] 为 i 到 j 的流量, 返回无向图所有点对最小割之和
    int ans=0,i,j,s,t,x,y,z;
    for(i=1;i<=n-1;i++){
        ans=min(ans,get(s,t));
        g[t]=1;if(!ans)break;
        for(j=1;j<=n;j++)if(!g[j])w[s][j]=(w[j][s]+=w[j][t]);
    }return ans;}
// 无向图最小割树
void fz(int l,int r){// 左闭右闭, 分治建图
    if(l==r)return;S=a[l];T=a[r];
    reset();// 将所有边权复原
    flow(S,T);// 做网络流
    dfs(S);// 找割集, v[x]=1 属于 S 集, 否则属于 T 集
    ADD(S,T,fl);// 在最小割树中建边
    L=l,R=r;for(i=l;i<=r;i++) if(v[a[i]])q[L++]=a[i]; else q[R--]=a[i];
    for(i=l;i<=r;i++)a[i]=q[i];fz(l,L-1);fz(R+1,r);}
