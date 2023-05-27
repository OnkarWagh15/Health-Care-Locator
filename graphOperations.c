#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "graph.h"
#include "queue/queueOperations.c"
#include "AVLTREE/AVLoperations.c"

void init(GraphPaths *gp)
{
    FILE *path;
    path = fopen("inputpath.txt", "r");
    int size1;
    fscanf(path, "%d", &size1);
    (*gp).size = size1;
    gp->paths = (int **)malloc(sizeof(int *) * gp->size);
    for (int i = 0; i < gp->size; i++)
    {
        gp->paths[i] = (int *)malloc(sizeof(int) * gp->size);
        for (int j = 0; j < gp->size; j++)
        {
            fscanf(path, "%d", &(gp->paths[i][j]));
        }
    }
}

Graph **updateNode(Graph *g, GraphPaths *gp, Graph **collectionOfNodes)
{
    FILE *ptr;
    ptr = fopen("dataset.txt", "r");
    if (!ptr)
        return NULL;
    int size = 0;
    fscanf(ptr, "%d", &size);
    collectionOfNodes = (Graph **)malloc(sizeof(Graph *) * size);
    char hospiAddr[30] = "xyz";
    char hospiName[30] = "xyz";
    int id = -1;
    int i = -1;
    int j = 0;
    int flag = 0;
    AVL t;
    int noOfNodes = 0;
    initTree(&t);
    while (!feof(ptr))
    {
        fscanf(ptr, "%s", hospiAddr);
        fscanf(ptr, "%s", hospiName);

        if (flag == 0)
        {
            g->hospitalId = ++id;
            g->hospitalAddress = (char *)malloc(sizeof(char) * 20);
            strcpy(g->hospitalAddress, hospiAddr);
            g->hospitalName = (char *)malloc(sizeof(char) * 20);
            strcpy(g->hospitalName, hospiName);
            collectionOfNodes[++i] = g;
            g->record = (specialization **)malloc(sizeof(specialization *) * 15);
            flag = 1;
            noOfNodes++;
        }
        if (flag == 1 && strcmp(g->hospitalAddress, hospiAddr) != 0 && strcmp(g->hospitalName, hospiName) != 0)
        {
            g = (Graph *)malloc(sizeof(Graph));
            (*g).hospitalId = ++id;
            g->hospitalAddress = (char *)malloc(sizeof(char) * 20);
            strcpy(g->hospitalAddress, hospiAddr);

            g->hospitalName = (char *)malloc(sizeof(char) * 20);
            strcpy(g->hospitalName, hospiName);

            collectionOfNodes[++i] = g;
            g->record = (specialization **)malloc(sizeof(specialization *) * 15);
            noOfNodes++;
        }
        if (strcmp(g->hospitalAddress, hospiAddr) == 0)
        {
            if (strcmp(g->hospitalName, hospiName) == 0)
            {
                strcpy(g->hospitalAddress, hospiAddr);
                strcpy(g->hospitalName, hospiName);
            }
            else
            {
                g = (Graph *)malloc(sizeof(Graph));
                (*g).hospitalId = ++id;
                g->hospitalAddress = (char *)malloc(sizeof(char) * 20);
                strcpy(g->hospitalAddress, hospiAddr);

                g->hospitalName = (char *)malloc(sizeof(char) * 20);
                strcpy(g->hospitalName, hospiName);

                collectionOfNodes[++i] = g;
                g->record = (specialization **)malloc(sizeof(specialization *) * 15);
                noOfNodes++;
            }
        }
        g->record[j] = (specialization *)malloc(sizeof(specialization));
        g->record[j]->specialist = (char *)malloc(sizeof(char));
        g->record[j]->time = (char *)malloc(sizeof(char));
        fscanf(ptr, "%s", g->record[j]->specialist);
        fscanf(ptr, "%s", g->record[j++]->time);

        insert(&t, g->hospitalAddress, i);
    }
    j = 0;
    fclose(ptr);
    return collectionOfNodes;
}

void bfsTravsersal(GraphPaths gp, int start_vertex)
{
    int i = 0;
    int *visitedNodes = (int *)calloc(gp.size, sizeof(int));
    Queue q;
    initQ(&q);
    enqueue(&q, start_vertex);
    visitedNodes[start_vertex] = 1;
    while (q.rear)
    {
        for (i = 0; i < gp.size; i++)
        {

            if (gp.paths[start_vertex][i] != 0 && visitedNodes[i] == 0)
            {
                enqueue(&q, i);
                visitedNodes[i] = 1;
            }
        }

        printf("%d\t->\t", q.front->data);
        dequeue(&q);
        if (q.front)
            start_vertex = q.front->data;
    }
    return;
}
void print_styled_input(const char *message)
{
    printf("\n");
    printf("\033[0;37m");
    printf("\033[0;43m");
    printf("%s", message);
    printf("\033[0m"); // Reset text color
    printf(": ");
}
void takeInputFromUser(char **area_name, char **specialist, char **time)
{
    print_styled_input("Enter the area name");
    scanf("%s", *area_name);

    print_styled_input("Enter the specialist required");
    scanf("%s", *specialist);

    print_styled_input("Enter the time");
    scanf("%s", *time);

    return;
}

int minimum_key(int k[], int mst[])
{
    int minimum = INT_MAX, min, i;

    for (i = 0; i < vertices; i++)
        if (mst[i] == 0 && k[i] < minimum)
            minimum = k[i], min = i;
    return min;
}
int **prim(int **g)
{
    int parent[vertices];
    int k[vertices];
    int mst[vertices];
    int i, count, edge, v; 
    for (i = 0; i < vertices; i++)
    {
        k[i] = INT_MAX;
        mst[i] = 0;
    }
    k[0] = 0;       
    parent[0] = -1; 
    for (count = 0; count < vertices - 1; count++)
    {
        edge = minimum_key(k, mst);
        mst[edge] = 1;
        for (v = 0; v < vertices; v++)
        {
            if (g[edge][v] && mst[v] == 0 && g[edge][v] < k[v])
            {
                parent[v] = edge, k[v] = g[edge][v];
            }
        }
    }

    Sp_tree t = (spnode**)malloc(sizeof(spnode)*vertices);

    for(int i = 0; i<vertices-1;i++) {
        t[i] = NULL;
    }

    spnode *nn;

    for (int j = 0; j < vertices; j++)
    {
        nn = (spnode *)malloc(sizeof(spnode));
        if(!nn) return NULL;
        nn->nodeIndex = j;
        nn->weight = g[j][parent[j]];
        nn->next = NULL;
        if(!t[j]) {
            t[j] = nn;
        }
        else {
            spnode *p = t[i];
            while(p->next) {
                p = p->next;
            }
            p->next = nn;
        }
    }

    int **spMatrix=(int **)malloc(sizeof(int*) * vertices);
    for (int i = 0; i < vertices; ++i) {
                spMatrix[i] = (int *)calloc(vertices,sizeof(int));

        spnode* temp = t[i];
        while (temp != NULL) {
            spMatrix[i][parent[i]] = t[i]->weight;
            temp = temp->next;
        }
    }
    for(int i =0;i<vertices;i++)
    {
        for(int j=0;j<vertices;j++)
        {
            spMatrix[i][j]=spMatrix[j][i];
            
        }
    }

    return spMatrix;

}


void HealthCareLocator(GraphPaths *gp, Graph *g, Graph **collectionOfNodes)
{
    init(gp);
    collectionOfNodes = updateNode(&(*g), &(*gp), &(*collectionOfNodes));
    int j = 0;
    for (int i = 0; i < 3; i++)
    {
        printf("\n%d", collectionOfNodes[i]->hospitalId);
        printf("\n%s", collectionOfNodes[i]->hospitalName);
        printf("\n%s", collectionOfNodes[i]->hospitalAddress);
        while (collectionOfNodes[i]->record[j])
        {
            printf("\n%s", collectionOfNodes[i]->record[j]->specialist);
            printf("\n%s", collectionOfNodes[i]->record[j]->time);
            j++;
        }
    }

    char *area_name = (char *)malloc(sizeof(char) * 50);
    char *specialist = (char *)malloc(sizeof(char) * 50);
    char *time = (char *)malloc(sizeof(char) * 50);

    takeInputFromUser(&area_name, &specialist, &time);

    int ** spMatrix=prim(gp->paths);
    printf("\nSpanning Matrix:\n");
    for(int i =0;i<vertices;i++)
    {
        for(int j=0;j<vertices;j++)
        {
            printf("%d\t",spMatrix[i][j]);
            
        }
        printf("\n");
    }
    
}


