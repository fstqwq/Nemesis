LL mul(LL x,LL y,LL p){
  LL t =(x*y-(LL)((LD)x/p*y+1e-3)*p)%p;
  return t<0?t+p:t;}
