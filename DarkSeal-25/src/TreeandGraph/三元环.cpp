int triple_loop(n,m,X[],Y[]){ //n为点数,m为边数,X[i]-Y[i]为连边 
	fr(i,1,m)du[X[i]]++,du[Y[i]]++;
	fr(i,1,m)if(du[X[i]]<du[Y[i]] || du[X[i]]==du[Y[i]] && X[i]<Y[i]) ins(X[i],Y[i]); else ins(Y[i],X[i]);
	fr(x,1,n){
		tour(i,x)v[la[i]]=x;
		tour(i,x)tour(j,la[i])if(v[la[j]]==x)ans++;
	}return ans;}
