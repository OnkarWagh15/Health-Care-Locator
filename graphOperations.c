#include<stdio.h>
#include<stdlib.h>
#include"graph.h"
#include"queue/queueOperations.c"
#include"AVLTREE/AVLoperations.c"


void init(Graph *g,GraphPaths *gp)
{
    FILE *ptr;
    ptr=fopen("dataset.txt","r");
    if(!ptr)    return;
    int size=0;
    fscanf(ptr,"%d", &size);
    Graph **temp;
    temp = (Graph **)malloc(sizeof(Graph *) * size);
    char address[30]="xyz";                                           // for checking areas
    int id=-1;
    int i=-1;
    AVL t;
    initTree(&t);
    while(!feof(ptr)){
        g=(Graph *)malloc(sizeof(Graph));
        (*g).hospitalId=++id;
        g->hospitalName=(char *)malloc(sizeof(char)*20);
        g->hospitalAddress=(char *)malloc(sizeof(char)*20);
        g->specialization=(char *)malloc(sizeof(char)*20);
        g->time=(char *)malloc(sizeof(char)*20);
        fscanf(ptr,"%s",g->hospitalAddress);
        fscanf(ptr,"%s",g->hospitalName);
        fscanf(ptr,"%s",g->specialization);
        fscanf(ptr,"%s",g->time);
        if(strcmp(address,g->hospitalAddress)!=0){
            insert(&t,g->hospitalAddress,i+1);
            strcpy(address,g->hospitalAddress);
        }
        temp[++i] = g;
    }
    // inorder(t);
    // printf("%d",search(t,"Deccan"));
    fclose(ptr);  
    FILE *path;
    path=fopen("inputpath.txt","r");
    int size1;
    // gp=(GraphPaths*)malloc(sizeof(GraphPaths));
    fscanf(path,"%d",&size1);
    (*gp).size=size1;
    gp->paths=(int**)malloc(sizeof(int *) * gp->size);
    for(int i=0;i<gp->size;i++)
    {
        gp->paths[i]=(int*)malloc(sizeof(int) * gp->size);
        for(int j=0;j<gp->size;j++)
        {
            fscanf(path,"%d",&(gp->paths[i][j]));
        }
    }
    
    fclose(path);

    return;   
}

void bfsTravsersal(GraphPaths gp,int start_vertex)
{
    
    int i=0;
    int *visitedNodes=(int *)calloc(gp.size,sizeof(int));
    Queue q;
    initQ(&q);
    enqueue(&q,start_vertex);
    visitedNodes[start_vertex]=1;
    // display(q);
    while(q.rear)
    {
        for(i=0;i<gp.size;i++)
        {   
            
            if(gp.paths[start_vertex][i]!=0 && visitedNodes[i]==0)
            {
                enqueue(&q,i);
                visitedNodes[i]=1;
            }
        }
        
        printf("%d\t->\t",q.front->data);
        dequeue(&q);
        if(q.front)
        start_vertex=q.front->data;
    }

    return;
}
