#include<bits/stdc++.h>

typedef long long ll;

ll pow(ll a, ll x, ll p)
{
	ll ret = 1;
	for (; x; x >>= 1)
	{
		if (x & 1)
			ret = ret * a % p;
		a = a * a % p;
	}
	return ret;
}
ll inv(ll a, ll p)
{
	return pow(a, p - 2, p);
}

std::map<ll, ll> mp;
//min solution
ll bsgs(ll a, ll b, ll p, ll sign)
{
	ll m = ll(sqrt(p) + 1);
	ll inva = inv(a, p);
	ll am = 1;
	mp.clear();
	for (int i = 0; i < m; i++, am = am * inva % p)
		if (!mp.count(am * b % p))
			mp[am * b % p] = i;
	am = inv(am, p);
	ll t = 1;
	for (int i = 0; i < m; i++, t = t * am % p)
		if (mp.count(t))
			return i * m + mp[t];
	return p;
}
