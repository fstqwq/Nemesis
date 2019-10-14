int merge(int x,int y) {
//p[i] 结点i的权值，这里是维护大根堆
//d[i] 在i的子树中，i到右叶子结点的最远距离.
    if(!x) return y;
    if(!y) return x;
    if(p[x] < p[y]) std::swap(x, y);
    r[x] = merge(r[x], y);
    if(r[x]) fa[r[x]] = x;
    if(d[l[x]] < d[r[x]]) std::swap(l[x], r[x]);//调整树的结构，使其满足左偏性质
    d[x] = d[r[x]] + 1;
    return x;
}
