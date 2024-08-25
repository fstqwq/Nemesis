struct Runs{
    int l,r,p;
};vector<Runs> run;
bool operator==(Runs x,Runs y){return x.l==y.l && x.r==y.r;}
int gl(int x,int y); // 求 $S[1,x],S[1,y]$ 的最长公共后缀
int gr(int x,int y); // 求 $S[x,n],S[y,n]$ 的最长公共前缀
//上面两个可以用 二分 + Hash 或者后缀数组实现。
bool getcmp(int x,int y){//S[x,n]<S[y,n]
	int len=gr(x,y);
	return st[x+len]<st[y+len];}
int ly[N];
void lyndon(bool type){//后缀排序法求 Lyndon
	stack<PII> stk;stk.push({n,n});ly[n]=n;
	for(int i=n-1;i>=1;i--){
		int now=i;
		while(!stk.empty() && getcmp(i,stk.top().first)!=type)
			now=stk.top().second,stk.pop();
		ly[i]=now;
		stk.push({i,now});
	} }
void getrun(){
	for(int l=1;l<=n;l++){
		int r=ly[l],ll=l,rr=r;
		if(l!=1)ll-=gl(l-1,r);
		if(r!=n)rr+=gr(l,r+1);
		if(rr-ll+1>=2*(r-l+1))run.push_back({ll,rr,r-l+1}); } }
void solve(){
	st[n + 1] = '\0'; run.clear();
	init();//Hash 或者 SA 的启动
	for(int op=0;op<=1;op++){//0正常字典序,1反序
		lyndon(op); getrun(); }
	sort(run.begin(),run.end(),[](Runs x, Runs y){
        return x == y ? x.p < y.p : (x.l != y.l ? x.l < y.l : x.r < y.r);});
	run.erase(unique(run.begin(),run.end()),run.end()); }