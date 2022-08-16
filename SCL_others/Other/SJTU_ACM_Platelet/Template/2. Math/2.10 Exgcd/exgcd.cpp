void exgcd(ll a, ll b, ll &x, ll &y)
{
	if (b == 0){
		x = 1;
		y = 0;
		return ;
	}
	exgcd(b, a % b);
	ll tmp = x;
	x = y;
	y = tmp - a / b * y;
	return ;
}
