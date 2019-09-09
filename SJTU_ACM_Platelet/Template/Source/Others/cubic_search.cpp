inline db cubic_search()
{
	double l = -1e4, r = 1e4;
	for (int i = 1; i <= 100; ++i)
	{
		double ll = (l + r) * 0.5;
		double rr = (ll + r) * 0.5;
		if (check(ll) < check(rr)) r = rr;
		else l = ll;
	}
	return (l + r) * 0.5;
}
