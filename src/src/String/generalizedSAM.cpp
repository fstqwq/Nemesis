struct SAM{
int tot,fail[MM],len[MM],t[MM][26];
SAM(){tot=1;}
int insert(int c,int last){
	if(t[last][c]){
		int p=last,q=t[p][c];
		if(len[p]+1==len[q])return q;
		else { int nq=++tot;
			fail[nq]=fail[q];fail[q]=nq;
			len[nq]=len[p]+1;memcpy(t[nq],t[q],sizeof(t[q]));
			for(;p && t[p][c]==q;p=fail[p])t[p][c]=nq;
			//可以直接复制下面的代码。
			return nq; } }
	int p=last,np=++tot;
	len[np]=len[p]+1;
	for(;p && !t[p][c];p=fail[p])t[p][c]=np;
	if(!p)fail[np]=1;
	else {
		int q=t[p][c];
		if(len[q]==len[p]+1)fail[np]=q;
		else { int nq=++tot;
			fail[nq]=fail[q];fail[q]=nq;
			len[nq]=len[p]+1;memcpy(t[nq],t[q],sizeof(t[q]));
			for(;p && t[p][c]==q;p=fail[p])t[p][c]=nq;
			fail[np]=nq; } }
	return np; } }sam;
// scanf("%s",st+1);int slen=strlen(st+1);
// int last=1;
// for(int j=1;j<=slen;j++)last=sam.insert(st[j]-'a',last);