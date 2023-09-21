int r;
void go(int i, int j, int x, int y, int z,int x0, int y0, int L, int W, int H) {
if (z==0) { int R = x*x+y*y; if (R<r) r=R;}
else {
if(i>=0&&i<2)go(i+1,j, x0+L+z, y, x0+L-x, x0+L, y0, H,W,L);
if(j>=0&&j<2)go(i,j+1, x, y0+W+z, y0+W-y, x0, y0+W, L,H,W);
if(i<=0&&i>-2)go(i-1, j, x0-z, y, x-x0, x0-H, y0, H, W, L);
if(j<=0&&j>-2)go(i, j-1, x, y0-z, y-y0, x0, y0-H, L, H, W);
} } int main(){
int L, H, W, x1, y1, z1, x2, y2, z2;
cin >> L >> W >> H >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
if (z1!=0 && z1!=H) if (y1==0 || y1==W)
	swap(y1,z1), swap(y2,z2), swap(W,H);
else swap(x1,z1), swap(x2,z2), swap(L,H);
if (z1==H) z1=0, z2=H-z2;
r=0x3fffffff; 
go(0,0,x2-x1,y2-y1,z2,-x1,-y1,L,W,H);
cout<<r<<endl; }
