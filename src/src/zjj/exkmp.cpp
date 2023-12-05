void exkmp(){
	for(int i=2,now=0,p=0;i<=n;i++){
		if(i>p)fail[i]=0;
		else fail[i]=min(p-i+1,fail[i-now+1]);
		if(i+fail[i]-1>=p){
			while(fail[i]+i<=n && s1[fail[i]+1]==s1[fail[i]+i]) fail[i]++;
			now=i;p=i+fail[i]-1;
		} }
	for(int i=1,now=0,p=0;i<=n;i++){
		if(i>p)ex[i]=0;
		else ex[i]=min(p-i+1,fail[i-now+1]);
		if(i+ex[i]-1>=p){
			while(i+ex[i]<=n && s1[ex[i]+1]==s2[i+ex[i]]) ex[i]++;
			now=i;p=i+ex[i]-1; } } }