#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include"AVL.h"
#include<string.h>

void initTree(AVL (*t))
{
    ((*t))=NULL;
    return;

}
void inorder(AVL t)
{
    
    if(!t)
    return;
    inorder(t->lchild);
    printf("%s\t",t->key);
      inorder(t->rchild);
}
int max(int a,int b)
{
    if(a>b)
        return a;
    else
        return b;
}
int height(AVL t)
{
    if(!t)
        return -1;
    if(!(t->lchild && t->rchild))
        return 0;
    
    return 1+max(height(t->lchild),height(t->rchild));
}
void insert(AVL (*t),char *key,int index)
{
    
    node *nn=(node *)malloc(sizeof(node));
    nn->bf=0;
    nn->key=key;
    nn->lchild=nn->rchild=nn->parent=NULL;
    nn->index=index;
    if(((*t))==NULL)
    {
        ((*t))=nn;
        nn->parent=NULL;
        adjust_bf(t,nn);
        return;
    }
    node *p=NULL;
    node *q=NULL;
    p=(*t);
    while(p)
    {
        q=p;
        int comp=strcmp(p->key,key);
        if(comp < 0)
        {
    
            p=p->rchild;
            
        }
        else if(comp==0){
            free(nn);
            return;}
        else
        {
            p=p->lchild;
        }

    }
    int comp2=strcmp(q->key,key);
    if(comp2<0)
        q->rchild=nn;
    else
        q->lchild=nn;

    nn->parent=q;
    adjust_bf(t,nn);
    balancetree(t,nn);
    return;
}

void adjust_bf(AVL (*t),node *q)
{
    node *p=q;
    while(p)
    {
        p->bf= height(p->lchild) - height(p->rchild);
        // printf("\n%s has bf %d",p->key,p->bf);
        p=p->parent;
    }
    return;
}
void balancetree(AVL (*t),node *q)
{
    node *p=q;
    while(p)
    {
    
        if(p->bf>=2 || p->bf<=-2){
        break;
        }

        p=p->parent;
    }
    if(p==NULL)
    {
        return;
    }

    if (p->bf == -2)
    {

        if (p->rchild->bf == -1){
            // printf("\nRR Imbalance caused by %s to %s",q->key,p->key);
            RR(t,p);
            return;
         }
        else{
            // printf("\nRL Imbalance caused by %s to %s",q->key,p->key);
            RL(t,p);
            return;
        }
    }
    else
    {

        if (p->lchild->bf == 1){
            // printf("\nLL Imbalance caused by %s to %s",q->key,p->key);
            LL(t,p);
            return;
        }
        else{
            // printf("\nLR Imbalance caused by %s to %s",q->key,p->key);
            LR(t,p);
            return;
        }
    }

    
}
void RR(AVL (*t),node *p)
{
    
    node *A=p;
    node  *B;
    B=(A)->rchild;
    if(A->parent==NULL){
        (*t)=B;
    }
    else{
        if((A)->parent->rchild==(A))
            (A)->parent->rchild=(B);
        if((A)->parent->lchild==(A))
            (A)->parent->lchild=(B);
    }
    B->parent=A->parent;
    A->parent=B;
    if(B->lchild)
        B->lchild->parent=A;
    A->rchild=B->lchild;
    B->lchild=A;
    adjust_bf(t,A);
    return;  
    
}

void LL(AVL (*t),node * p)
{

    node *A=p;
    node  *B;
    B=(A)->lchild;
    if(A->parent==NULL){
        (*t)=B;
    }
    else{
        if((A)->parent->rchild==(A))
            (A)->parent->rchild=(B);
        if((A)->parent->lchild==(A))
            (A)->parent->lchild=(B);
    }
    B->parent=A->parent;
    A->parent=B;
    if(B->rchild)    
     B->rchild->parent=A;
    A->lchild=B->rchild;
    B->rchild=A;
    adjust_bf(t,A);
    return;  

}
void LR(AVL (*t), node *p)
{
    
    RR(t,p->lchild);
    LL(t,p);
    return;
}
void RL(AVL (*t), node *p)
{
    
    LL(t,p->rchild);
    RR(t,p);
    return;

}

void deletehelper(AVL *t,node *p)
{
    if (!p)
        return;
    adjust_bf(t,p->lchild);
    adjust_bf(t,p->rchild);
    balancetree(t,p);
    
    return;

}

struct node* delete(AVL *t, char *key){
    
    node *p, *q;
    if (!(*t))
    {
        return NULL;
    }

    p = *t;
    while (p)
    {
        int res= strcmp(p->key, key);
        if (res== 0)
            break;
        q = p; 
        if (res> 0)
            p = p->lchild;
        else
            p = p->rchild;
    }
    if (!p)
    {
        return NULL; 
    }
    
    int flag = 0;
    
    if (!p->rchild && !p->lchild)
    {
          
        node *dn = p;
        AVL temp = dn->parent;
        if (p == *t) 
            {
                *t= NULL; 
            }

        else
        {
            if (q->lchild == p)
            {
                q->lchild = NULL;
            }
            else
            {
                q->rchild = NULL;
            }
            p -> parent = NULL;
        }
        free(dn);
        deletehelper(t,temp);

        if((*t) && (*t) -> parent == (temp))
            *t = temp;
        return NULL;
    }
   
    if (!p->rchild && p->lchild)
    {
        AVL dn = p;
        AVL temp = dn->parent;
        if (p == *t) 
        {
           
            (*t) -> parent = NULL ;
            (*t)= p->lchild;
        }

        else
        {
            if (q->lchild == p)
            {

                q->lchild = p->lchild;
            }
            else
            {
                q->rchild = p->lchild;
            }
            p -> lchild -> parent = q;
        }
        free(dn);
        deletehelper(t,temp);
        if((*t) && (*t) -> parent == (temp))
            *t = temp;

        return NULL;
    }
    
    if (p->rchild && !p->lchild)
    {
        node *dn= p;
        AVL temp = dn->parent;
        if (p == *t)
        {
            p -> rchild-> parent = (*t) -> parent;
            *t= p->rchild;
        }
        else
        {
            if (q->lchild== p)
                q->lchild = p->rchild;

            else
                q->rchild = p->rchild;
            
            p -> rchild -> parent = q;
        }
        free(dn);
        deletehelper(t,temp);
        if((*t) && (*t) -> parent == (temp))
        *t = temp;
        return NULL;
    }
  
    if (p->rchild && p->lchild)
    {

        node *temp, *pp; 
        pp = p->lchild;
        temp = pp->rchild;
        AVL parentOfTemp = NULL;
        if (!temp)
        {
            p->key = (char *)malloc(sizeof(pp->key));
            strcpy(p->key, pp->key);
            p->lchild= pp->lchild;
            if(pp -> lchild)
            pp -> lchild -> parent = p;
            parentOfTemp = pp->parent;
            free(pp);
        }
        else
        {
            while (temp->rchild)
            {
                pp = temp;
                temp = temp->rchild;
            }
            char *tempo = temp->key;
            (p)->key = (char *)malloc(sizeof(p->key));
            strcpy(p->key, temp->key);

            parentOfTemp = pp;
            if(temp -> lchild){
                pp -> rchild = temp -> lchild;
                temp -> lchild -> parent = pp; 
            }
            else
                pp->rchild = NULL;
            free(temp);
        }
        deletehelper(t,parentOfTemp);
        if((*t) && (*t) -> parent == parentOfTemp)
            *t = parentOfTemp;
    }
}

int search(AVL t,char *key)
{
    if(!t){
        printf("\nTree not found\n");
        return INT_MIN;
    }  
    while(t)
    {
        if(strcmp(key,t->key)==0)
            return t->index;
        if(strcmp(key,t->key)<0)
        {
            t = t->lchild;
        }
        else{
            t = t->rchild;
        }
    }
    return -1;
}
