struct node{
    node *left,*right,*up,*down,*col; int row,cnt;
}*head,*col[MAXC],Node[MAXNODE],*ans[MAXNODE];
int totNode, ansNode;
void insert(const std::vector<int> &V,int rownum){
    std::vector<node*> N;
    for(int i=0;i<int(V.size());++i){
        node* now=Node+(totNode++); now->row=rownum;
        now->col=now->up=col[V[i]], now->down=col[V[i]]->down;
        now->up->down=now, now->down->up=now;
        now->col->cnt++; N.push_back(now); }
    for(int i=0;i<int(V.size());++i)
        N[i]->right=N[(i+1)%V.size()], N[i]->left=N[(i-1+V.size())%V.size()];
}
void Remove(node *x){
    x->left->right=x->right, x->right->left=x->left;
    for(node *i=x->down;i!=x;i=i->down)
        for(node *j=i->right;j!=i;j=j->right)
            j->up->down=j->down, j->down->up=j->up, --(j->col->cnt);
}
void Resume(node *x){
    for(node *i=x->up;i!=x;i=i->up)
        for(node *j=i->left;j!=i;j=j->left)
            j->up->down=j->down->up=j, ++(j->col->cnt);
    x->left->right=x, x->right->left=x;
}
bool search(int tot){
    if(head->right==head) return ansNode = tot, true;
    node *choose=NULL;
    for(node *i=head->right;i!=head;i=i->right){
        if(choose==NULL||choose->cnt>i->cnt) choose=i;
        if(choose->cnt<2) break; }
    Remove(choose);
    for(node *i=choose->down;i!=choose;i=i->down){
        for(node *j=i->right;j!=i;j=j->right) Remove(j->col);
        ans[tot]=i;
        if(search(tot+1)) return true;
        ans[tot]=NULL;
        for(node *j=i->left;j!=i;j=j->left) Resume(j->col); }
    Resume(choose); return false;
}
void prepare(int totC){
    head=Node+totC;
    for(int i=0;i<totC;++i) col[i]=Node+i;
    totNode=totC+1; ansNode = 0;
    for(int i=0;i<=totC;++i){
        (Node+i)->right=Node+(i+1)%(totC+1);
        (Node+i)->left=Node+(i+totC)%(totC+1);
        (Node+i)->up=(Node+i)->down=Node+i;
        (Node+i)->cnt=0; }
}
prepare(C); for (i (rows)) insert({col_id}, C); search(0);
