// 广义 SAM，离线 BFS
struct Trie{
	int tot,fa[M],tr[M][26],c[M];
	Trie(){tot=1;}
	void insert(char *ch,int slen){
		int now=1;
		for(int i=1;i<=slen;i++){
			int x=ch[i]-'a';
			if(!tr[now][x])tr[now][x]=++tot,c[tot]=x,fa[tot]=now;
			now=tr[now][x];
		}
	}
}trie;
struct SAM{
	int tot,pos[M],fail[MM],maxlen[MM],trans[MM][26];
	queue<int> Q;
	SAM(){tot=1;}
	int insert(int c,int last){
		int p=last,np=++tot;
		maxlen[np]=maxlen[p]+1;
		for(;p && !trans[p][c];p=fail[p])trans[p][c]=np;
		if(!p)fail[np]=1;
		else{
			int q=trans[p][c];
			if(maxlen[q]==maxlen[p]+1)fail[np]=q;
			else{
				int nq=++tot;
				fail[nq]=fail[q];fail[q]=nq;
				maxlen[nq]=maxlen[p]+1;
				memcpy(trans[nq],trans[q],sizeof(trans[q]));
				for(;p && trans[p][c]==q;p=fail[p])trans[p][c]=nq;
				fail[np]=nq;
			}
		}
		return np;
	}
	void build(){
		pos[1]=1;
		for(int i=0;i<26;i++)
			if(trie.tr[1][i])Q.push(trie.tr[1][i]);
		while(!Q.empty()){
			int x=Q.front();Q.pop();
			pos[x]=insert(trie.c[x],pos[trie.fa[x]]);
			for(int i=0;i<26;i++){
				if(trie.tr[x][i])Q.push(trie.tr[x][i]);
			} } } } SAM;
// Lyndon， 22 ECF D. Minimum Suffix
bool work(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	vector<vector<int> > ff;ff.resize(n+1);
	top=0;
	for(int i=1;i<=n;i++){
		if(a[i]==i)sta[++top]=i;
		else{//mer
			while(top && sta[top]!=a[i])top--;
			ff[a[i]].push_back(i);
			if(!top)return 0;
		}
	}
	sta[top+1]=n+1;
	for(int i=top;i>=1;i--){
		if(i==top){
			int x=sta[i],now=x;b[x]=1;
			for(auto y:ff[x]){
				int T=now-x+1;
				for(int j=now+1;j<=y;j++){
					b[j]=b[j-T];
					if(j!=y && a[j]!=a[j-T]+T)return 0;
				}
				b[now=y]++;
			}
		}
		else{
			int x=sta[i],now=x,limit=x;
			b[x]=b[sta[i+1]];prepos[x]=x;
			bool bk=0;
			for(auto y:ff[x]){
				int T=now-x+1;
				for(int j=now+1;j<y;j++){
					b[j]=b[j-T];prepos[j]=prepos[j-T];
					int pos=j-x+sta[i+1];
					if(pos>=sta[i+2] || b[j]>b[pos]){
						bk=1;break;
					} else if(b[j]<b[pos]){
						b[limit]++;bk=1;
						break;
					}
				}
				if(bk)break;
				int pos=y-x+sta[i+1];prepos[y]=y;
				if(pos>=sta[i+2]){bk=1;break;}
				b[now=y]=max(b[y-T]+1,b[pos]);
				if(b[now]>b[pos]){bk=1;break;}
				limit=y;
			}
			if(!bk){
				limit=sta[i+1]-1;bk=1;
				if(sta[i+2]-sta[i+1]>sta[i+1]-sta[i])
					b[limit]++;
			}
			x=sta[i],now=x;
			for(auto y:ff[x]){
				int T=now-x+1;
				for(int j=now+1;j<y;j++){
					b[j]=b[j-T];
					if(a[j]!=a[j-T]+T)return 0;
				}
				now=y;
				if(now>limit)b[now]=b[now-T]+1;
			}
		}
	}
	for(int i=1;i<=n;i++)printf("%d ",b[i]);
	return 1; }