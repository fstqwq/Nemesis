//
//  Title: Functional Segment Tree
//  Date:16.12.2015
//  Complexity:O((n+m)logn)
//  Test:YZOJ-1991
/*
    可以查询任意一个版本的线段树——主席树 
*/
#include<cstdio>
#include<algorithm>
#define maxt 2000010
#define maxn 100010
#define R register
inline int FastIn(){
	R char ch=getchar();R int cnt=0;
	while (ch<'0'||ch>'9') ch=getchar();
	while (ch>='0'&&ch<='9') cnt=cnt*10+ch-'0',ch=getchar();
	return cnt;
}//读入优化 

int ls[maxt],//记录左儿子的节点 
    rs[maxt],//记录右儿子的节点 
	count[maxt],//记录区间内的数量 
	root[maxn],//记录第i个状态的根节点 
	tot;//记录节点的个数 

int num[maxn],rank[maxn],n,m,r[maxn];

bool cmp(const int &i,const int &j){
	return num[i]<num[j];
}

inline void Insert(int last,int left,int right,int pre)
//last是上一个版本的节点，left,right代表左右区间，pre是待插入的数 
{
	count[++tot]=count[last]+1;	
	if (left==right) return;	
	R int mid=(left+right)>>1;//向下取整 
	if (pre>mid){
		ls[tot]=ls[last];//因为左儿子是没有改变的，所以就把新的版本的左儿子连接到旧版本的左儿子上 
		rs[tot]=tot+1;//右儿子是新建的 
		Insert(rs[last],mid+1,right,pre);
	}
	else{
		ls[tot]=tot+1;//同上 
		rs[tot]=rs[last];
		Insert(ls[last],left,mid,pre); 
	}
}

inline int Query(int a,int b,int k)
//查询在[a,b]的节点内[left..right]内第k小的数 
{
	R int l=1,r=n,mid,f1=a,f2=b,cnt,kk=k;
	while (l<r){
		mid=(l+r)>>1;cnt=count[ls[f2]]-count[ls[f1]];
		if (cnt>=kk) f1=ls[f1],f2=ls[f2],r=mid;
		else f1=rs[f1],f2=rs[f2],l=mid+1,kk-=cnt;
	}
	return l;
}

int main()
{
	n=FastIn();m=FastIn();R int i,a,b,k;	
	for (i=1;i<=n;i++) num[i]=FastIn(),rank[i]=i;
	std::sort(rank+1,rank+n+1,cmp);
	std::sort(num+1,num+n+1);
	for (i=1;i<=n;i++) r[rank[i]]=i;
	//离散化 
	for (i=1;i<=n;i++) {
		root[i]=tot+1;
		Insert(root[i-1],1,n,r[i]); 
	}
	//插入  
	for (i=1;i<=m;i++){
		a=FastIn();b=FastIn();k=FastIn();
		printf("%d\n",num[Query(root[a-1],root[b],k)]);
	}
	//查询 
	return 0;
}
