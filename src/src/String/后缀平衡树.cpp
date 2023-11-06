// 后缀平衡树每次在字符串开头添加或删除字符, 考虑在当前字符串 S 前插入一个字符 c, 那么相当于在后缀平衡树中插入一个新的后缀 cS, 简单的话可以使用预处理哈希二分 LCP 判断两个后缀的大小作 cmp, 直接写 set, 时间复杂度 O(nlg^2n). 为了方便可以把字符反过来做
// 例题 : 加一个字符或删一个字符, 同时询问不同子串个数
struct cmp{
	bool operator()(int a,int b){
		int p=lcp(a,b);//注意这里是后面加，lcp是反过来的 
		if(a==p)return 0;if(b==p)return 1;
		return s[a-p]<s[b-p];}
};set<int,cmp>S;set<int,cmp>::iterator il,ir;
void del(){S.erase(L--);}//在后面删字符 
void add(char ch){//在后面加字符 
	s[++L]=ch;mx=0;il=ir=S.lower_bound(L);
	if(il!=S.begin())mx=max(mx,lcp(L,*--il));
	if(ir!=S.end())mx=max(mx,lcp(L,*ir));
	an[L]=an[L-1]+L-mx;S.insert(L); }
LL getan(){printf("%lld\n",an[L]);}//询问不同子串个数 
