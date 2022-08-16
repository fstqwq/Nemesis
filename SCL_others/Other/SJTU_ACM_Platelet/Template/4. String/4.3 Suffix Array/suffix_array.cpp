/* suffix_array */
/*
 * Set $N to be at least ${n+1}.
 * Set $m to be the maximal character ASCII ID.
 * Store the string into c 1-based.
 * Call suffix(), then the rank of suffix starting from $i,
 *     the starting index of $i-th smallest suffix,
 *     and the length of the common prefix of
 *     ${i-1}-th and $i-th smallest suffix
 *     will be stored in ${rank[i]}, ${sa[i]}, ${height[i]} respectively.
 */
#include <cstring>
#include <algorithm>
#include <utility>
const int N = 1e5 + 10;
char c[N];
int tax[N], tp[N], sa[N], rank[N], height[N], n, m = 127;
inline void rsort() {
    for (int i = 1; i <= m; i++)
        tax[i] = 0;
    for (int i = 1; i <= n; i++)
        tax[rank[tp[i]]]++;
    for (int i = 1; i <= m; i++)
        tax[i] += tax[i - 1];
    for (int i = n; i; i--)
        sa[tax[rank[tp[i]]]--] = tp[i];
}
inline bool cmp(int *f, int x, int y, int w) {
    return f[x] == f[y] && f[x + w] == f[y + w];
}
inline void suffix() {
    for (int i = 1; i <= n; i++) {
        rank[i] = c[i];
        tp[i] = i;
    }
    rsort();
    for (int w = 1, p; p < n; w <<= 1) {
        p = 0;
        for (int i = n - w + 1; i <= n; i++)
            tp[++p] = i;
        for (int i = 1; i <= n; i++)
            if (sa[i] > w)
                tp[++p] = sa[i] - w;
        rsort();
        std::swap(rank, tp);
        rank[sa[1]] = p = 1;
        for (int i = 2; i <= n; i++)
            rank[sa[i]] = cmp(tp, sa[i], sa[i - 1], w) ? p : ++p;
        m = p;
    }
    for (int i = 1; i <= n; i++) {
        static int j, p;
        j = std::max(height[rank[i - 1]] - 1, 0);
        p = sa[rank[i] - 1];
        for (; c[i + j] == c[p + j]; j++)
            continue;
        height[rank[i]] = j;
    }
}

// Test "loj111" passed
// Test "uoj35" passed
#include <cstdio>
int main() {
    scanf("%s", c + 1);
    n = strlen(c + 1);
    suffix();
    printf("%d", sa[1]);
    for (int i = 2; i <= n; i++)
        printf(" %d", sa[i]);
    putchar('\n');
    if (n >= 2)
        printf("%d", height[2]);
    for (int i = 3; i <= n; i++)
        printf(" %d", height[i]);
    putchar('\n');
    return 0;
}
