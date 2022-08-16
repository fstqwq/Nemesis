struct line{
	point p,v;
};
point Rev(point v){return point(-v.y,v.x);}
point operator*(line A,line B){
	point u=B.p-A.p;
	double t=(B.v*u)/(B.v*A.v);
	return A.p+A.v*t;
}
point get(point a,point b){
	return (a+b)/2;
}
point get(point a,point b,point c){
	if(a==b)return get(a,c);
	if(a==c)return get(a,b);
	if(b==c)return get(a,b);	
	line ABO=(line){(a+b)/2,Rev(a-b)};
	line BCO=(line){(c+b)/2,Rev(b-c)};
	return ABO*BCO;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%lf%lf",&p[i].x,&p[i].y);
	random_shuffle(p+1,p+1+n);
	O=p[1];r=0;
	for(int i=2;i<=n;i++){
		if(dis(p[i],O)<r+1e-6)continue;
		O=get(p[1],p[i]);r=dis(O,p[i]);
		for(int j=1;j<i;j++){
			if(dis(p[j],O)<r+1e-6)continue;
			O=get(p[i],p[j]);r=dis(O,p[i]);
			for(int k=1;k<j;k++){
				if(dis(p[k],O)<r+1e-6)continue;
				O=get(p[i],p[j],p[k]);r=dis(O,p[i]);
			}
		}
	}printf("%.2lf %.2lf %.2lf\n",O.x,O.y,r);
	return 0;
}
