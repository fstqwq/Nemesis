bool inPoly(P p,vector<P>poly){
	int cnt=0;
	for(int i=0;i<poly.size();i++){
		P a=poly[i],b=poly[(i+1)%poly.size()];
		if(onSeg(p,L(a,b)))
			return false;
		int x=sgn(det(a,p,b));
		int y=sgn(a.y-p.y);
		int z=sgn(b.y-p.y);
		cnt+=(x>0&&y<=0&&z>0);
		cnt-=(x<0&&z<=0&&y>0);
	}
	return cnt;
}
