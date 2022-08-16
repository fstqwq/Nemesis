//满足s的最小后缀等于s本身的串s称为Lyndon串.
//等价于: s是它自己的所有循环移位中唯一最小的一个.
//任意字符串s可以分解为$s=s_1s_2…s_k$,其中$s_i$是Lyndon串, $s_i \geq s_{i+1}$.且这种分解方法是唯一的.
void mnsuf(char *s, int *mn, int n) { // 每个前缀的最小后缀
	for (int i = 0; i < n; ) {
		int j = i, k = i + 1; mn[i] = i;
		for (; k < n && s[j] <= s[k]; ++ k)
			if (s[j] == s[k]) mn[k] = mn[j] + k - j, ++j;
				else mn[k] = j = i;
		for (; i <= j; i += k - j) {} } } // lyn+=s[i..i+k-j-1]
void mxsuf(char *s, int *mx, int n) { // 每个前缀的最大后缀
	fill(mx, mx + n, -1);
	for (int i = 0; i < n; ) {
		int j = i, k = i + 1; if (mx[i] == -1) mx[i] = i;
		for (; k < n && s[j] >= s[k]; ++k) {
			j = s[j] == s[k] ? j + 1 : i;
			if (mx[k] == -1) mx[k] = i; }
		for (; i <= j; i += k - j) {} } }