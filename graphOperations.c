#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "queue/queueOperations.c"
#include "AVLTREE/AVLoperations.c"

Graph** init(Graph *g, GraphPaths *gp, Graph **collectionOfNodes) {
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

    fclose(path);
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
    // display(q);
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

void HealthCareLocator(GraphPaths *gp, Graph *g, Graph **collectionOfNodes)
{
    collectionOfNodes = init(&(*g), &(*gp), &(*collectionOfNodes));
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
        printf("\n\n");
    }
    bfsTravsersal(*gp,0);
}
// void LocateHospital(GraphPaths gp,int startVertex,Graph **collectionOfNodes)          //Dijisktra algorithm
// {
//     int *visited=(int *)calloc(gp.size,sizeof(int));
//     for(int i=startVertex;i<gp.size;i++)
//     {
//         for(int j=0;j<gp.size;j++)
//         {
//             if(gp.paths[i][j] && collectionOfNodes[j]->specialization)
//             {

//             }

//         }
//     }

// }