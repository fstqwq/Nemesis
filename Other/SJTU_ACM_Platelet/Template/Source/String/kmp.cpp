int main()
{
	for (int i = 2, j = 0; i <= n; ++i)
	{
		for ( ; j && s[j + 1] != s[i]; j = fail[j]) ;
		s[i] == s[j + 1] ? ++j : 0;
		fail[i] = j;
	}
	return 0;
}
