//
//  Title : ACMachine
//  Date : 20.01.2016
//  Complexity : ?
//  Test : HDU-2222
/*
	AC自动机——用来处理多个字符串的匹配
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <queue>

#ifdef WIN32
	#define LL "%I64d"
#else
	#define LL "%lld"
#endif

#ifdef CT
	#define debug(...) printf(__VA_ARGS__)
#else
	#define debug(...)
#endif

#define R register
#define getc() (S==T&&(T=(S=B)+fread(B,1,1<<15,stdin),S==T)?EOF:*S++)
#define gmax(_a, _b) ((_a) > (_b) ? (_a) : (_b))
#define gmin(_a, _b) ((_a) < (_b) ? (_a) : (_b))
#define cmax(_a, _b) (_a < (_b) ? _a = (_b) : 0)
#define cmin(_a, _b) (_a > (_b) ? _a = (_b) : 0)
char B[1<<15],*S=B,*T=B;
inline int FastIn()
{
	R char ch;R int cnt=0;R bool minus=0;
	while (ch=getc(),(ch < '0' || ch > '9') && ch != '-') ;
	ch == '-' ?minus=1:cnt=ch-'0';
	while (ch=getc(),ch >= '0' && ch <= '9') cnt = cnt * 10 + ch - '0';
	return minus?-cnt:cnt;
}
#define maxncnt 500010
#define maxlen 1000010
char model[maxlen],s[maxlen];
int ncnt;
int trie[maxncnt][26];
int fail[maxncnt];
int end[maxncnt];
inline void Insert(){
	R int i,j=0;
	for (i=0;s[i];i++){
		!trie[j][s[i]-'a']?trie[j][s[i]-'a']=++ncnt:0;
		j=trie[j][s[i]-'a'];
	}
	end[j]++;
}
inline void Build(){
	std::queue<int> q;
	fail[0]=0;
	for (R int i=0;i<26;i++)
		if (trie[0][i])q.push(trie[0][i]);
	while (!q.empty()){
		R int now=q.front();
		q.pop();
		for (R int i=0;i<26;i++)
			if (!trie[now][i])
				trie[now][i]=trie[fail[now]][i];
			else{
				fail[trie[now][i]]=trie[fail[now]][i];
				q.push(trie[now][i]);
			}
	}
}
inline void Query(){
	R int now=0,res=0;
	for (R int i=0;model[i];i++){
		now=trie[now][model[i]-'a'];
		R int temp=now;
		while (temp){
			res+=end[temp];
			end[temp]=0;
			temp=fail[temp];
		}
	}
	printf("%d\n",res );
}
inline void Clear(){
	for (R int i=0;i<=ncnt;i++){
		end[i]=fail[i]=0;
		for (R int j=0;j<26;j++)
			trie[i][j]=0;
	}
	ncnt=0;
}
int main()
{
	R int t,n;
	scanf("%d\n",&t);
	for (;t--;){
		scanf("%d\n",&n);
		for (R int i = 0; i < n; i++) 
			gets(s),Insert();
		Build();
		gets(model);
		Query();
		Clear();
	}
	return 0;
}
