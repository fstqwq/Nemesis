struct Node{
	Node *ch[2]; int key,val,size;
	void pushup() size=ch[0]->size+ch[1]->size+1 }
	Node(int k){ key=k;val=rand();size=1; ch[0]=ch[1]=null; }
}*null=new Node(0),*root[N],*root1[N];
void init(){
	null->ch[0]=null->ch[1]=null;
	null->key=null->val=null->size=0;
	for(int i=0;i<=::n;i++)root[i]=root1[i]=null; }
int getrank(Node *now,int x){
	int ans=0;
	while(now!=null){
		if(now->key<x)ans+=now->ch[0]->size+1,now=now->ch[1];
		else now=now->ch[0]; }
	return ans; }
void rotate(Node *&x,int d){
	Node *y=x->ch[d];
	x->ch[d]=y->ch[d^1]; y->ch[d^1]=x;
	x->pushup();y->pushup(); x=y; }
void insert(Node *&rt,int x){
	if(rt==null)rt=new Node(x);
	else {
		int d=x>rt->key;
		insert(rt->ch[d],x);
		if(rt->ch[d]->val<rt->val)rotate(rt,d); }
	rt->pushup(); }
void dfs(Node *rt){
	if(rt==null)return;
	dfs(rt->ch[0]); dfs(rt->ch[1]);
	delete rt; }
