void kmp(string A,int*p){//A 为模式串, p 为失配数组
	int n=A.length(),i=1,j=0;
	for(CL(p);i<n;i++){
		for(;j&&A[j]^A[i];j=p[j-1]);
		if(A[i]==A[j])j++;
		p[i]=j;}
}int gans(string A,string B,int*p){
//B 为标准串, A 为待匹配串, p 为失配数组 
	int n=B.length(),m=A.length(),j=0;
	fr(i,0,m-1){
		for(;j&&B[j]^A[i];j=p[j-1]);
		if(B[j]==A[i])j++;
		if(j==n)an++,j=p[j-1];
	} return an; }
void exkmp(char *s, int *a, int n) {
// 如果想求一个字符串相对另外一个字符串的最长公共前缀, 可以把他们拼接起来从而求得
	a[0] = n; int p = 0, r = 0;
	for (int i = 1; i < n; ++i) {
		a[i] = (r > i) ? min(r - i, a[i - p]) : 0;
		while (i + a[i] < n && s[i + a[i]] == s[a[i]]) ++a[i];
		if (r < i + a[i]) r = i + a[i], p = i; }}
