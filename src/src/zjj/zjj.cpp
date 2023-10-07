// PAM + log dp
char st[N],ss[N];
namespace PAM{
	int trans[N][26],len[N],fail[N];
	int dif[N],slink[N];
	int tot,last;
	int getfail(int pos,int x){
		while(pos-len[x]-1<1 || st[pos-len[x]-1]!=st[pos])x=fail[x];
		return x;
	}
	void init(){
		tot=last=1;len[1]=-1;fail[0]=1;
	}
	void add(int pos){
		int x=getfail(pos,last),c=st[pos]-'a';
		if(!trans[x][c]){
			 tot++;
			 len[tot]=len[x]+2;
			 fail[tot]=trans[getfail(pos,fail[x])][c];
			 trans[x][c]=tot;
			 dif[tot]=len[tot]-len[fail[tot]];
			 if(dif[tot]==dif[fail[tot]])slink[tot]=slink[fail[tot]];
			 else slink[tot]=fail[tot];
		}
		last=trans[x][c];
	}
	LL g[N];
}
using PAM::dif;
using PAM::slink;
using PAM::g;
using PAM::len;
using PAM::fail;
int n;LL dp[N];
int main(){
	scanf("%s",ss+1);n=strlen(ss+1);
	for(int i=1;i<=n/2;i++)st[i*2-1]=ss[i],st[i*2]=ss[n-i+1];
	dp[0]=1;PAM::init();
	for(int i=1;i<=n;i++){
		PAM::add(i);
		for(int x=PAM::last;x>1;x=slink[x]){
			g[x]=dp[i-len[slink[x]]-dif[x]];
			if(dif[x]==dif[fail[x]])g[x]=(g[x]+g[fail[x]])%mod;
			if(i%2==0)dp[i]=(dp[i]+g[x])%mod;
		}
	}
	printf("%lld\n",dp[n]);
	return 0;
}
// exkmp
//(s1,n,val),(s2,m,exkmp)
int now=0,p=0;exkmp[1]=m;
for(int i=2;i<=m;i++){
	if(i<=p)exkmp[i]=min(p-i+1,exkmp[i-now+1]);
	if(exkmp[i]+i-1>=p){
		while(i+exkmp[i]<=m && s2[i+exkmp[i]]==s2[exkmp[i]+1])exkmp[i]++;
		now=i;p=i+exkmp[i]-1;
	}
}
now=p=0;
for(int i=1;i<=n;i++){
	if(i<=p)val[i]=min(p-i+1,exkmp[i-now+1]);
	if(val[i]+i-1>=p){
		while(i+val[i]<=n && val[i]+1<=m && s2[val[i]+1]==s1[i+val[i]])val[i]++;
		now=i;p=i+val[i]-1;
	}
}
// ACAM
namespace ACAM{
	/*如果题目给的是多个字符串而不是一个现成的Trie。
	那么last树的深度至多根号。*/
	int tr[N][26],last[N],fail[N],tot;bool v[N];
	int ins(char *st,int len){
		int now=0;
		for(int i=1;i<=len;i++){
			int x=st[i]-'a';
			if(!tr[now][x])tr[now][x]=++tot;
			now=tr[now][x];
		}
		v[now]=1;
		return now;
	}
	//lis还可以作为ACAM中任意一棵树的拓扑序。
	//不过这个拓扑序里面没有0号点，也就是根。
	int lis[N],head,tail;
	void bfs(){
		head=1;
		for(int i=0;i<26;i++){
			if(tr[0][i])lis[++tail]=tr[0][i];
		}
		while(head<=tail){
			int x=lis[head++];
			if(!v[fail[x]])last[x]=last[fail[x]];
			else last[x]=fail[x];
			for(int i=0;i<26;i++){
				int y=tr[x][i];
				if(!y)tr[x][i]=tr[fail[x]][i];
				else fail[y]=tr[fail[x]][i],lis[++tail]=y;
			}
		}
	}
}
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
		for(int i=0;i<26;i++){
			if(trie.tr[1][i])Q.push(trie.tr[1][i]);
		}
		while(!Q.empty()){
			int x=Q.front();Q.pop();
			pos[x]=insert(trie.c[x],pos[trie.fa[x]]);
			for(int i=0;i<26;i++){
				if(trie.tr[x][i])Q.push(trie.tr[x][i]);
			}
		}
	}
}SAM;