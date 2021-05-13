#define DIST(e) (lab[e.u]+lab[e.v]-g[e.u][e.v].w*2)
struct Edge{ int u,v,w; } g[N][N];
int n,m,n_x,lab[N],match[N],slack[N],
st[N],pa[N],fl_from[N][N],S[N],vis[N];
vector<int> fl[N];
deque<int> q;
void update_slack(int u,int x){
	if(!slack[x]||DIST(g[u][x])<DIST(g[slack[x]][x])) slack[x]=u; }
void set_slack(int x){
	slack[x]=0;
	for(int u=1; u<=n; ++u)
		if(g[u][x].w>0&&st[u]!=x&&S[st[u]]==0)update_slack(u,x);
}
void q_push(int x){
	if(x<=n)return q.push_back(x);
	for(int i=0; i<fl[x].size(); i++)q_push(fl[x][i]);
}
void set_st(int x,int b){
	st[x]=b;
	if(x<=n)return;
	for(int i=0; i<fl[x].size(); ++i)set_st(fl[x][i],b);
}
int get_pr(int b,int xr){
	int pr=find(fl[b].begin(),fl[b].end(),xr)-fl[b].begin();
	if(pr%2==1){
		reverse(fl[b].begin()+1,fl[b].end());
		return (int)fl[b].size()-pr;
	}
	else return pr;
}
void set_match(int u,int v){
	match[u]=g[u][v].v;
	if(u<=n)return;
	Edge e=g[u][v];
	int xr=fl_from[u][e.u],pr=get_pr(u,xr);
	for(int i=0; i<pr; ++i)set_match(fl[u][i],fl[u][i^1]);
	set_match(xr,v);
	rotate(fl[u].begin(),fl[u].begin()+pr,fl[u].end());
}
void augment(int u,int v){
	int xnv=st[match[u]];
	set_match(u,v);
	if(!xnv)return;
	set_match(xnv,st[pa[xnv]]);
	augment(st[pa[xnv]],xnv);
}
int get_lca(int u,int v){
	static int t=0;
	for(++t; u||v; swap(u,v)){
		if(u==0)continue;
		if(vis[u]==t)return u;
		vis[u]=t;
		u=st[match[u]];
		if(u)u=st[pa[u]];
	}
	return 0;
}
void add_blossom(int u,int lca,int v){
	int b=n+1;
	while(b<=n_x&&st[b])++b;
	if(b>n_x)++n_x;
	lab[b]=0,S[b]=0;
	match[b]=match[lca];
	fl[b].clear();
	fl[b].push_back(lca);
	for(int x=u,y; x!=lca; x=st[pa[y]])
		fl[b].push_back(x),
		fl[b].push_back(y=st[match[x]]),q_push(y);
	reverse(fl[b].begin()+1,fl[b].end());
	for(int x=v,y; x!=lca; x=st[pa[y]])
		fl[b].push_back(x),
		fl[b].push_back(y=st[match[x]]),q_push(y);
	set_st(b,b);
	for(int x=1; x<=n_x; ++x)g[b][x].w=g[x][b].w=0;
	for(int x=1; x<=n; ++x)fl_from[b][x]=0;
	for(int i=0; i<fl[b].size(); ++i){
		int xs=fl[b][i];
		for(int x=1; x<=n_x; ++x)
			if(g[b][x].w==0||DIST(g[xs][x])<DIST(g[b][x]))
				g[b][x]=g[xs][x],g[x][b]=g[x][xs];
		for(int x=1; x<=n; ++x)
			if(fl_from[xs][x])fl_from[b][x]=xs;
	}
	set_slack(b);
}
void expand_blossom(int b){
	for(int i=0; i<fl[b].size(); ++i)
		set_st(fl[b][i],fl[b][i]);
	int xr=fl_from[b][g[b][pa[b]].u],pr=get_pr(b,xr);
	for(int i=0; i<pr; i+=2){
		int xs=fl[b][i],xns=fl[b][i+1];
		pa[xs]=g[xns][xs].u;
		S[xs]=1,S[xns]=0;
		slack[xs]=0,set_slack(xns);
		q_push(xns);
	}
	S[xr]=1,pa[xr]=pa[b];
	for(int i=pr+1; i<fl[b].size(); ++i){
		int xs=fl[b][i];
		S[xs]=-1,set_slack(xs);
	}
	st[b]=0;
}
bool on_found_Edge(const Edge &e){
	int u=st[e.u],v=st[e.v];
	if(S[v]==-1){
		pa[v]=e.u,S[v]=1;
		int nu=st[match[v]];
		slack[v]=slack[nu]=0;
		S[nu]=0,q_push(nu);
	}
	else if(S[v]==0){
		int lca=get_lca(u,v);
		if(!lca)return augment(u,v),augment(v,u),1;
		else add_blossom(u,lca,v);
	}
	return 0;
}
bool matching(){
	fill(S,S+n_x+1,-1),fill(slack,slack+n_x+1,0);
	q.clear();
	for(int x=1; x<=n_x; ++x)
		if(st[x]==x&&!match[x])pa[x]=0,S[x]=0,q_push(x);
	if(q.empty())return 0;
	for(;;){
		while(q.size()){
			int u=q.front();
			q.pop_front();
			if(S[st[u]]==1)continue;
			for(int v=1; v<=n; ++v)
				if(g[u][v].w>0&&st[u]!=st[v]){
					if(DIST(g[u][v])==0){
						if(on_found_Edge(g[u][v]))return 1;
					}
					else update_slack(u,st[v]);
				}
		}
		int d=INF;
		for(int b=n+1; b<=n_x; ++b)
			if(st[b]==b&&S[b]==1)d=min(d,lab[b]/2);
		for(int x=1; x<=n_x; ++x)
			if(st[x]==x&&slack[x]){
				if(S[x]==-1)d=min(d,DIST(g[slack[x]][x]));
				else if(S[x]==0)d=min(d,DIST(g[slack[x]][x])/2);
			}
		for(int u=1; u<=n; ++u){
			if(S[st[u]]==0){
				if(lab[u]<=d)return 0;
				lab[u]-=d;
			}
			else if(S[st[u]]==1)lab[u]+=d;
		}
		for(int b=n+1; b<=n_x; ++b)
			if(st[b]==b){
				if(S[st[b]]==0)lab[b]+=d*2;
				else if(S[st[b]]==1)lab[b]-=d*2;
			}
		q.clear();
		for(int x=1; x<=n_x; ++x)
			if(st[x]==x&&slack[x]&&st[slack[x]]!=x&&DIST(g[slack[x]][x])==0)
				if(on_found_Edge(g[slack[x]][x]))return 1;
		for(int b=n+1; b<=n_x; ++b)
			if(st[b]==b&&S[b]==1&&lab[b]==0)expand_blossom(b); }
	return 0; }
pair<ll,int> weight_blossom(){
	fill(match,match+n+1,0);
	n_x=n;
	int n_matches=0;
	ll tot_weight=0;
	for(int u=0; u<=n; ++u)st[u]=u,fl[u].clear();
	int w_max=0;
	for(int u=1; u<=n; ++u)
		for(int v=1; v<=n; ++v){
			fl_from[u][v]=(u==v?u:0);
			w_max=max(w_max,g[u][v].w); }
	for(int u=1; u<=n; ++u)lab[u]=w_max;
	while(matching())++n_matches;
	for(int u=1; u<=n; ++u)
		if(match[u]&&match[u]<u)
			tot_weight+=g[u][match[u]].w;
	return make_pair(tot_weight,n_matches); }
int main(){
	cin>>n>>m;
	for(int u=1; u<=n; ++u)
		for(int v=1; v<=n; ++v)
			g[u][v]=Edge {u,v,0};
	for(int i=0,u,v,w; i<m; ++i){
		cin>>u>>v>>w;
		g[u][v].w=g[v][u].w=w; }
	cout<<weight_blossom().first<<'\n';
	for(int u=1; u<=n; ++u)cout<<match[u]<<' '; }
