//满足s的最小后缀等于s本身的串s称为Lyndon串.
//等价于: s是它自己的所有循环移位中唯一最小的一个.
//任意字符串s可以分解为$s=s_1s_2…s_k$,其中$s_i$是Lyndon串, $s_i \geq s_{i+1}$.且这种分解方法是唯一的.
//后缀排序后，排名的所有前缀最小值构成了 Ly 分解的左端点。
void mnsuf(char *s, int *mn, int n){ // 每个前缀的最小后缀
	//1 - base ，求 Lyndon 分解去掉 mn 即可
    for(int i = 1; i <= n;)
        int j = i + 1, k = i; mn[i] = i;
        for(; j <= n && s[k] <= s[j]; j++){
            if(s[k] < s[j]) k = mn[j] = i;
                else mn[j] = mn[k] + j - k, k++;
        for(; i <= k; i += j - k) {} } } //lyn+=s[i..i+k-j-1]
void mxsuf(char *s, int *mx, int n){ // 每个前缀的最大后缀
    fill(mx + 1, mx + n + 1, 0); // 1 - base
    for(int i = 1; i <= n;){
        int j = i + 1, k = i; !mx[i] ? mx[i] = i : 0;
        for(; j <= n && s[k] >= s[j]; j++){
            !mx[j] ? mx[j] = i : 0;
            s[k] > s[j] ? k = i : k++; }
        for(; i <= k; i += j - k) {} } }