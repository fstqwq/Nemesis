bool byY(P a,P b){return a.y<b.y;}
LL solve(P *p,int l,int r){
	LL d=1LL<<62;
	if(l==r)
		return d;
	if(l+1==r)
		return dis2(p[l],p[r]);
	int mid=(l+r)>>1;
	d=min(solve(l,mid),d);
	d=min(solve(mid+1,r),d);
	vector<P>tmp;
	for(int i=l;i<=r;i++)
		if(sqr(p[mid].x-p[i].x)<=d)
			tmp.push_back(p[i]);
	sort(tmp.begin(),tmp.end(),byY);
	for(int i=0;i<tmp.size();i++)
		for(int j=i+1;j<tmp.size()&&j-i<10;j++)
			d=min(d,dis2(tmp[i],tmp[j]));
	return d;
}
