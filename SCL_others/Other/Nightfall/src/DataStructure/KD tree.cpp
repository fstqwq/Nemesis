//P-节点类  d[2]-坐标 mi[2]-最小坐标 mx[2]-最大坐标 l,r-左右儿子 s-和  v-值 lz-懒惰标记 sz-子树大小 
int rt,X0,X1,Y0,Y1,X,Y,O,an;
struct P{int d[2],mi[2],mx[2],l,r,s,v,lz,sz;}T[111111];
bool cmp(P a,P b) {
	return a.d[O]<b.d[O]||a.d[O]==b.d[O]&&a.d[O^1]<b.d[O^1];}
void ADD(int k,int z) {
	if(!k)return;T[k].v+=z;T[k].s+=T[k].sz*z;T[k].lz+=z;}
void pd(int k) { if(T[k].lz)
	ADD(T[k].l,T[k].lz),ADD(T[k].r,T[k].lz),T[k].lz=0;}
int bd(int l,int r,int o){//将[l,r]建树, 维度是o, 返回[l,r]的根
	O=o;int k=l+r>>1,i;nth_element(T+l+1,T+k+1,T+r+1,cmp);
	for(i=0;i<2;i++)T[k].mi[i]=T[k].mx[i]=T[k].d[i];
	T[k].lz=T[k].v=T[k].s=0;
	if(l<k)for(O=T[k].l=bd(l,k-1,o^1),i=0;i<2;i++)
		Min(T[k].mi[i],T[O].mi[i]), Max(T[k].mx[i],T[O].mx[i]);
	if(k<r)for(O=T[k].r=bd(k+1,r,o^1),i=0;i<2;i++)
		Min(T[k].mi[i],T[O].mi[i]), Max(T[k].mx[i],T[O].mx[i]);
	T[k].sz=T[T[k].l].sz+T[T[k].r].sz+1;return k;
}void add(int k,int z){//范围+z, 范围为[X0,X1][Y0,Y1] 
	if(X0>T[k].mx[0] || X1<T[k].mi[0] || Y0>T[k].mx[1] || Y1<T[k].mi[1]) return;
	if(X0<=T[k].mi[0] && X1>=T[k].mx[0] && Y0<=T[k].mi[1] && Y1>=T[k].mx[1]) {ADD(k,z);return;}
	if(X0<=T[k].d[0] && T[k].d[0]<=X1 && Y0<=T[k].d[1] && T[k].d[1]<=Y1) T[k].v+=z;
	pd(k);add(T[k].l,z);add(T[k].r,z);
	T[k].s=T[k].v+T[T[k].l].s+T[T[k].r].s;
}int qu(int k){//询问范围和 
	if(X0>T[k].mx[0] || X1<T[k].mi[0] || Y0>T[k].mx[1] || Y1<T[k].mi[1]) return 0;
	if(X0<=T[k].mi[0] && X1>=T[k].mx[0] && Y0<=T[k].mi[1] && Y1>=T[k].mx[1]) return T[k].s;
	int an=0;
	if(X0<=T[k].d[0] && T[k].d[0]<=X1 && Y0<=T[k].d[1] && T[k].d[1]<=Y1) an=T[k].v;
	pd(k); return an+qu(T[k].l)+qu(T[k].r);
}//外部将坐标存入T[i].d[2]后调用rt=bd(1,n,0)
int dis(P a){return max(a.mi[0]-X,0) + max(X-a.mx[0],0) + max(a.mi[1]-Y,0) + max(Y-a.mx[1],0);}
void fdmin(int k,int o){//找离当前点(X,Y)最近的点
	int d=abs(T[k].d[0]-X)+abs(T[k].d[1]-Y),dl=inf,dr=inf;
	an=min(an,d);
	if(T[k].l)dl=dis(T[T[k].l]);
	if(T[k].r)dr=dis(T[T[k].r]);
	if(dl<dr){if(dl<an)fdmin(T[k].l,o^1); if(dr<an)fdmin(T[k].r,o^1);
	}else{if(dr<an)fdmin(T[k].r,o^1); if(dl<an)fdmin(T[k].l,o^1);}}