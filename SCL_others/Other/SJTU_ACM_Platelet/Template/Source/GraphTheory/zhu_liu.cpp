using Val = long long;
#define nil mem
struct Node { Node *l,*r; int dist;int x,y;Val val,laz; }
mem[M] = {{nil, nil, -1}}; int sz = 0;
#define NEW(arg...) (new(mem + ++ sz)Node{nil,nil,0,arg})
void add(Node *x, Val o) {if(x!=nil){x->val+=o, x->laz+=o;}}
void down(Node *x){add(x->l,x->laz);add(x->r,x->laz);x->laz=0;}
Node *merge(Node *x, Node *y) {
    if (x == nil) return y; if (y == nil) return x;
    if (y->val < x->val) swap(x, y); //smalltop heap
    down(x); x->r = merge(x->r, y);
    if (x->l->dist < x->r->dist) swap(x->l, x->r);
    x->dist = x->r->dist + 1; return x; }
    Node *pop(Node *x){down(x); return merge(x->l, x->r);}
    struct DSU { int f[N]; void clear(int n) {
        for (int i=0; i<=n; ++i) f[i]=i; }
    int fd(int x) { if (f[x]==x) return x;
        return f[x]=fd(f[x]); }
    int& operator[](int x) {return f[fd(x)];}};
DSU W, S; Node *H[N], *pe[N];
vector<pair<int, int>> G[N]; int dist[N], pa[N];
// addedge(x, y, w) : NEW(x, y, w, 0)
Val chuliu(int s, int n) { // O(ElogE)
    for (int i = 1; i <= n; ++ i) G[i].clear();
    Val re=0; W.clear(n); S.clear(n); int rid=0;
    fill(H, H + n + 1, (Node*) nil);
    for (auto i = mem + 1; i <= mem + sz; ++ i)
        H[i->y] = merge(i, H[i->y]);
    for (int i = 1; i <= n; ++ i) if (i != s)
        for (;;) {
            auto in = H[S[i]]; H[S[i]] = pop(H[S[i]]);
            if (in == nil) return INF; // no solution
            if (S[in -> x] == S[i]) continue;
            re += in->val; pe[S[i]] = in;
            // if (in->x == s) true root = in->y
            add(H[S[i]], -in->val);
            if (W[in->x]!=W[i]) {W[in->x]=W[i];break;}
            G[in -> x].push_back({in->y,++rid});
            for (int j=S[in->x]; j!=S[i]; j=S[pe[j]->x]) {
                G[pe[j]->x].push_back({pe[j]->y, rid});
                H[j] = merge(H[S[i]], H[j]); S[i]=S[j]; }}
    ++ rid; for (int i=1; i<=n; ++ i) if(i!=s && S[i]==i)
        G[pe[i]->x].push_back({pe[i]->y, rid});
    return re;}
void makeSol(int s, int n) {
    fill(dist, dist + n + 1, n + 1); pa[s] = 0;
    for (multiset<pair<int, int>> h = {{0,s}}; !h.empty();){
        int x=h.begin()->second;
        h.erase(h.begin()); dist[x]=0;
        for (auto i : G[x]) if (i.second < dist[i.first]) {
            h.erase({dist[i.first], i.first});
            h.insert({dist[i.first] = i.second, i.first});
            pa[i.first] = x; }}}
