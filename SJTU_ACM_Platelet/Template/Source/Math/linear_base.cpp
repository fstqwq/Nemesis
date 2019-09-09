int main()
{
	for (int i = 1; i <= n; ++i)
	{
		ull x = F();
		cmax(m, 63 - __builtin_clzll(x));
		for ( ; x; )
		{
			tmp = __builtin_ctzll(x);
			if (!b[tmp])
			{
				b[tmp] = x;
				break;
			}
			x ^= b[tmp];
		}
	}
}
