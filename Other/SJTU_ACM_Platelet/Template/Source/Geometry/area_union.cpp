double form(double x){
	while(x>=2*pi)x-=2*pi;
	while(x<0)x+=2*pi;
	return x;
}
double calcCir(C cir){
	vector<double>ang;
	ang.push_back(0);
	ang.push_back(pi);
	double ans=0;
	for(int i=1;i<=n;i++){
		if(cir==c[i])continue;
		P p1,p2;
		if(intersect(cir,c[i],p1,p2)){
			ang.push_back(form(cir.ang(p1)));
			ang.push_back(form(cir.ang(p2)));
		}
	}	

	for(int i=1;i<=m;i++){
		vector<P>tmp;
		tmp=intersect(poly[i],cir);
		for(int j=0;j<tmp.size();j++){
			ang.push_back(form(cir.ang(tmp[j])));
		}
	}
	sort(ang.begin(),ang.end());
	for(int i=0;i<ang.size();i++){
		double t1=ang[i],t2=(i+1==ang.size()?ang[0]+2*pi:ang[i+1]);
		P p=cir.at((t1+t2)/2);
		int ok=1;
		for(int j=1;j<=n;j++){
			if(cir==c[j])continue;
			if(inC(p,c[j],true)){
				ok=0;
				break;
			}
		}
		for(int j=1;j<=m&&ok;j++){
			if(inPoly(p,poly[j],true)){
				ok=0;
				break;
			}
		}
		if(ok){
			double r=cir.r,x0=cir.o.x,y0=cir.o.y;
			ans+=(r*r*(t2-t1)+r*x0*(sin(t2)-sin(t1))-r*y0*(cos(t2)-cos(t1)))/2;	

		}
	}
	return ans;
}
P st;
bool bySt(P a,P b){
	return dis(a,st)<dis(b,st);
}
double calcSeg(L l){
	double ans=0;
	vector<P>pt;
	pt.push_back(l.a);
	pt.push_back(l.b);
	for(int i=1;i<=n;i++){
		P p1,p2;
		if(intersect(c[i],l,p1,p2)){
			if(onSeg(p1,l))
				pt.push_back(p1);
			if(onSeg(p2,l))
				pt.push_back(p2);
		}
	}
	st=l.a;
	sort(pt.begin(),pt.end(),bySt);
	for(int i=0;i+1<pt.size();i++){
		P p1=pt[i],p2=pt[i+1];
		P p=(p1+p2)/2;
		int ok=1;
		for(int j=1;j<=n;j++){
			if(sgn(dis(p,c[j].o),c[j].r)<0){
				ok=0;
				break;
			}
		}
		if(ok){
			double x1=p1.x,y1=p1.y,x2=p2.x,y2=p2.y;    
			double res=(x1*y2-x2*y1)/2;
			ans+=res;
		}
	}
	return ans;
}
