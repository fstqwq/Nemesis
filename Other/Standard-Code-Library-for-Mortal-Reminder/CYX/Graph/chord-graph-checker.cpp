int n, m, first[1001], l, next[2000001], where[2000001],f[1001], a[1001], c[1001], L[1001], R[1001],
v[1001], idx[1001], pos[1001];
bool b[1001][1001];

inline void makelist(int x, int y){
    where[++l] = y;
    next[l] = first[x];
    first[x] = l;
}

bool cmp(const int &x, const int &y){
    return(idx[x] < idx[y]);
}

int main(){
    for (;;)
    {
        n = read(); m = read();
        if (!n && !m) return 0;
        memset(first, 0, sizeof(first)); l = 0;
        memset(b, false, sizeof(b));
        for (int i = 1; i <= m; i++) 
        {
            int x = read(), y = read();
            if (x != y && !b[x][y])
            {
               b[x][y] = true; b[y][x] = true;
               makelist(x, y); makelist(y, x);
            }
        }
        memset(f, 0, sizeof(f));
        memset(L, 0, sizeof(L));
        memset(R, 255, sizeof(R));
        L[0] = 1; R[0] = n;
        for (int i = 1; i <= n; i++) c[i] = i, pos[i] = i;
        memset(idx, 0, sizeof(idx));
        memset(v, 0, sizeof(v));
        for (int i = n; i; --i)
        {
            int now = c[i];
            R[f[now]]--;
            if (R[f[now]] < L[f[now]]) R[f[now]] = -1;
            idx[now] = i; v[i] = now;
            for (int x = first[now]; x; x = next[x])
                if (!idx[where[x]]) 
                {
                   swap(c[pos[where[x]]], c[R[f[where[x]]]]);
                   pos[c[pos[where[x]]]] = pos[where[x]];
                   pos[where[x]] = R[f[where[x]]];
                   L[f[where[x]] + 1] = R[f[where[x]]]--;
                   if (R[f[where[x]]] < L[f[where[x]]]) R[f[where[x]]] = -1;
                   if (R[f[where[x]] + 1] == -1)
                       R[f[where[x]] + 1] = L[f[where[x]] + 1];
                   ++f[where[x]];
                }
        }
        bool ok = true;
        //v是完美消除序列.
        for (int i = 1; i <= n && ok; i++)
        {
            int cnt = 0;
            for (int x = first[v[i]]; x; x = next[x]) 
                if (idx[where[x]] > i) c[++cnt] = where[x];
            sort(c + 1, c + cnt + 1, cmp);
            bool can = true;
            for (int j = 2; j <= cnt; j++)
                if (!b[c[1]][c[j]])
                {
                    ok = false;
                    break;
                }
        }
        if (ok) printf("Perfect\n");
        else printf("Imperfect\n");
        printf("\n");
    }
}
