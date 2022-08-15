char S[1 << 20], *T = S;
inline int F()
{
	char ch; int cnt = 0;
	while (ch = *T++, ch < '0' || ch > '9') ;
	cnt = ch - '0';
	while (ch = *T++, ch >= '0' && ch <= '9') cnt = cnt * 10 + ch - '0';
	return cnt;
}
fread(S, 1, 1 << 20, stdin);
