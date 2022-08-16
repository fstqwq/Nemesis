inline int cmp(const lhy &a,const lhy &b)
{
	return a.d[D]<b.d[D];
}

inline void updata(int x)
{
	if(p[x].l)
	{
		for(int i=0;i<2;i++)
			p[x].min[i]=min(p[x].min[i],p[p[x].l].min[i]),
			p[x].max[i]=max(p[x].max[i],p[p[x].l].max[i]);
	}
	if(p[x].r)
	{
		for(int i=0;i<2;i++)
			p[x].min[i]=min(p[x].min[i],p[p[x].r].min[i]),
			p[x].max[i]=max(p[x].max[i],p[p[x].r].max[i]);
	}
}

int build(int l,int r,int d)
{
	D=d;
	int mid=(l+r)>>1;
	nth_element(p+l,p+mid,p+r+1,cmp);
	for(int i=0;i<2;i++)
		p[mid].max[i]=p[mid].min[i]=p[mid].d[i];
	if(l<mid)p[mid].l=build(l,mid-1,d^1);
	if(mid<r)p[mid].r=build(mid+1,r,d^1);
	updata(mid);
	return mid;
}

void insert(int now,int D)
{
	if(p[now].d[D]>=p[n].d[D])
	{
		if(p[now].l)insert(p[now].l,D^1);
		else p[now].l=n;
		updata(now);
	}
	else
	{
		if(p[now].r)insert(p[now].r,D^1);
		else p[now].r=n;
		updata(now);
	}
}

int dist(lhy &P,int X,int Y)
{
	int nowans=0;
	if(X>=P.max[0])nowans+=X-P.max[0];
	if(X<=P.min[0])nowans+=P.min[0]-X;
	if(Y>=P.max[1])nowans+=Y-P.max[1];
	if(Y<=P.min[1])nowans+=P.min[1]-Y;
	return nowans;
}

void ask1(int now)
{
	int pl,pr;
	ans=min(ans,abs(x-p[now].d[0])+abs(y-p[now].d[1]));
	if(p[now].l)pl=dist(p[p[now].l],x,y);
	else pl=0x3f3f3f3f;
	if(p[now].r)pr=dist(p[p[now].r],x,y);
	else pr=0x3f3f3f3f;
	if(pl<pr)
	{
		if(pl<ans)ask(p[now].l);
		if(pr<ans)ask(p[now].r);
	}
	else
	{
		if(pr<ans)ask(p[now].r);
		if(pl<ans)ask(p[now].l);
	}
}

void ask2(int now)
{
	if(x1<=p[now].min[0]&&x2>=p[now].max[0]&&y1<=p[now].min[1]&&y2>=p[now].max[1])
	{
		ans+=p[now].sum;
		return;
	}
	if(x1>p[now].max[0]||x2<p[now].min[0]||y1>p[now].max[1]||y2<p[now].min[1])return;
	if(x1<=p[now].d[0]&&x2>=p[now].d[0]&&y1<=p[now].d[1]&&y2>=p[now].d[1])ans+=p[now].val;
	if(p[now].l)ask(p[now].l);
	if(p[now].r)ask(p[now].r);
}
