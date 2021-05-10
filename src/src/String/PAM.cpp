char s[N];int id,cnt[N],F[N],num[N],L[N],c[N][26], f[N],_f[N],pre[N],df[N],sk[N]; 
void add(int z,int n){ //注意这里的n是目前添加的字符数 
	for(;s[n-L[p]-1]!=s[n];)p=F[p]; //失配后找一个尽量最长的 
	if(!c[p][z]){ //这个回文串没有出现过, 出现了新的本质不同的回文串
		int q=++id,k=F[p]; //新建节点 
		for(L[q]=L[p]+1;s[n-L[k]-1]!=s[n];k=F[k]);//失败指针 
		F[q]=c[k][z];c[p][z]=q;num[q]=num[F[q]]+1;
		df[q]=L[q]-L[F[q]];
		sk[q]=(df[q]==df[F[q]]?sk[F[q]]:F[q]);
	}p=c[p][z];cnt[p]++; //统计该类回文出现次数, 这里的p即为last 
}void init(){
	id=1;F[0]=F[1]=1;L[1]=-1; //一开始两个节点, 0表示偶数长度串的根, 1表示奇数长度串的根 
	scanf("%s",s+1);n=strlen(s+1);_f[0]=1;
	for(int i=1;i<=n;i++){
		add(s[i]-'a',i);f[i]=1e9;
		for(int x=p;x;x=sk[x]){ //这里是求最小回文分割次数 
			_f[x]=i-L[sk[x]]-df[x]; //先更新_f[x], 再用_f[x]更新f[x] 
			if(df[F[x]]==df[x]&&f[_f[x]]>f[_f[F[x]]])
				_f[x]=_f[F[x]];
			if(f[i]>f[_f[x]]+1)
				f[i]=f[_f[x]]+1,pre[i]=_f[x];
		}}for(i=id;i;i--)cnt[F[i]]+=cnt[i]; }
