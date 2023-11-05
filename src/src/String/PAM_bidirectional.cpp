int t[N][26],fail[N],len[N];
int tot,lastl,lastr;
int ss[NN],L,R;
// slen 表示前端能够插入的最多字符数量
void init(int slen){
	L=slen+1;R=slen;
	tot=lastl=lastr=1;
    len[1]=-1;fail[0]=1; }
int Lfail(int pos,int x) {
	while(pos+len[x]+1>R || ss[pos+len[x]+1]!=ss[pos])x=fail[x];
	return x; }
int Rfail(int pos,int x) {
	while(pos-len[x]-1<L || ss[pos-len[x]-1]!=ss[pos])x=fail[x];
	return x; }
void add(int c,int type) {
	int x,pos;
	if(!type)ss[pos=--L]=c,x=Lfail(pos,lastl);
	else ss[pos=++R]=c,x=Rfail(pos,lastr);
	if(!t[x][c]){
		tot++;
		len[tot]=len[x]+2;
		if(!type)fail[tot]=t[Lfail(pos,fail[x])][c];
		else fail[tot]=t[Rfail(pos,fail[x])][c];
		t[x][c]=tot;
	}
	if(!type){
		lastl=t[x][c];
		if(len[lastl]==R-L+1)lastr=lastl;
	} else {
		lastr=t[x][c];
		if(len[lastr]==R-L+1)lastl=lastr; } }