
void initTree(AVL *t);
void insert(AVL *t,char *key,int index);
void inorder(AVL t);
int height(AVL t);
int max(int a,int b);
void adjust_bf(AVL *t,node *p);
void deletehelper(AVL *t,node *p);
struct node* delete(AVL *t1,char *key);
void balancetree(AVL *t,node *p);
int search(AVL t,char *key);
void RR(AVL *t,node *p);
void LL(AVL *t,node *p);
void RL(AVL *t,node *p);
void LR(AVL *t,node *p);