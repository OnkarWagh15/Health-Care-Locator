#include<stdio.h>
#include<stdlib.h>
#include"graph.h"
void main()
{   
    Graph g;
    GraphPaths gp;
    Graph **collectionOfNodes;
    HealthCareLocator(&gp,&g,collectionOfNodes);
}