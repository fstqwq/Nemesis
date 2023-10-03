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
