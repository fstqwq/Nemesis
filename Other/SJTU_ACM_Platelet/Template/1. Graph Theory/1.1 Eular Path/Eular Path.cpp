int n,m,cnt,ans[maxm],last[maxn],to[maxm],next[maxm];
bool vis[maxm];
void dfs(int x){
	for (R int &i=last[x];i;i=next[i]) if (!vis[i]) {vis[i]=1,dfs(to[i]);}
	ans[++cnt]=x;
}
int main()
{	
	n=FastIn();m=FastIn();R int i,tmp=0,a,b;
	for (i=1;i<=m;i++) a=FastIn(),b=FastIn(),to[i]=b,next[i]=last[a],last[a]=i,tmp^=a^b;
	if(tmp) {puts("-1"); return 0;}
	dfs(1);
	if (cnt!=m+1 || ans[1] != 1) puts("-1");
	else for (printf("%d\n",cnt),i=cnt;i;i--) printf("%d ",ans[i]);
	return 0;
}
