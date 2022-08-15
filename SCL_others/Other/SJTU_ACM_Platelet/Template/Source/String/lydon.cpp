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
                for (; i <= j; i += k - j) {} } 
