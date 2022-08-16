char str[maxn];
int p1[maxn], p2[maxn], n;
void manacher1()
{
	int mx = 0, id;
	for(int i = 1; i <= n; ++i)
	{
		if (mx >= i) p1[i] = dmin(mx - i, p1[(id << 1) - i]);
		else p1[i] = 1;
		for (; str[i + p1[i]] == str[i - p1[i]]; ++p1[i]) ;
		if (p1[i] + i - 1 > mx) id = i, mx = p1[i] + i - 1;
	}
}
void manacher2()
{
	int mx = 0, id;
	for(int i = 1; i <= n; i++)
	{
		if (mx >= i) p2[i] = dmin(mx - i, p2[(id << 1) - i]) ;
		else p2[i] = 0;
		for (; str[i + p2[i] + 1] == str[i - p2[i]]; ++p2[i]);
		if (p2[i] + i > mx) id = i, mx = p2[i] + i;
	}
}
int main()
{
	scanf("%s", str + 1);
	n = strlen(str + 1);
	str[0] = '#';
	str[n + 1] = '$';
	manacher1();
	manacher2();
	return 0;
}
