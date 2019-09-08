// 这段代码仅仅处理奇回文，使用时请往字符串中间加入 # 来使用
for(int i = 1, j = 0; i != (n << 1) - 1; ++i){
	int p=i>>1, q = i - p, r = ((j + 1) >> 1) + l[j] - 1;
	l[i] = r < q ? 0 : min(r - q + 1, l[(j << 1) - i]);
	while (p - l[i] != -1 && q + l[i] != n
		&& s[p - l[i]] == s[q + l[i]]) l[i]++;
	if(q + l[i] - 1 > r) j=i;
	a += l[i];
}
