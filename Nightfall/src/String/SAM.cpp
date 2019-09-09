struct SAM{
int np,id,st[N],F[N],c[N][26],b[N],bl[N],cnt[N],pos[N];
void in(){CLEARALL;np=id=1;}//必须调用 
void add(int x,int z){
	int p=np,q,nq;np=c[p][x];
	if(np&&st[np]==st[p]+1)return;
	st[np=++id]=st[p]+1;pos[np]=z;
	for(;p&&!c[p][x];p=F[p])c[p][x]=np;
	if(!p)F[np]=1;else if(st[p]+1==st[q=c[p][x]])F[np]=q;else{
		if(st[np]==st[p]+1)
			nq=np,st[nq]=st[p]+1,F[nq]=F[q],F[q]=nq;
		else st[nq=++id]=st[p]+1,pos[nq]=pos[q], F[nq]=F[q],F[q]=F[np]=nq;
		for(memcpy(c[nq],c[q],sizeof c[q]);p&&c[p][x]==q;p=F[p])c[p][x]=nq;
	}}
void work(){//计数，这里的cnt[]为出现次数，可以视情况更改 
	int i;LL an=0;
	for(i=1;i<=id;i++)b[st[i]]++;
	for(i=1;i<=id;i++)b[i]+=b[i-1];
	for(i=1;i<=id;i++)bl[b[st[i]]--]=i;
	for(i=id;i;i--)cnt[F[bl[i]]]+=cnt[bl[i]];}
void get(string S){//在后缀自动机上走，L为当前长度，p为当前位置 
	for(int p=1,L=0,i=0;i<S.length();i++){
		if(c[p][x=S[i]-'a'])p=c[p][x],L++;else{
			for(;!c[p][x]&&p;p=F[p]);
			if(!p)p=1,L=0;else L=st[p]+1,p=c[p][x];
		}
	}}}A;
