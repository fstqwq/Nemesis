ll ans; ull E[64];
#define bit(i) (1ULL << (i))
void dfs(ull P, ull X, ull R) { // 不需要方案时可去掉R相关语句
    if (!P && !X) { ++ans; sol.pb(R); return; }
    ull Q = P & ~E[__builtin_ctzll(P | X)];
    for (int i; i = __builtin_ctzll(Q), Q; Q &= ~bit(i)) {
        dfs(P & E[i], X & E[i], R | bit(i));
        P &= ~bit(i), X |= bit(i); }}
        ans = 0; dfs(n == 64 ? ~0ULL : bit(n) - 1, 0, 0);
