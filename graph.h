#define vertices 1000
#define MAX_NODES 1000
#include<stdbool.h>
// #include"AVLTREE/AVLoperations.c"

typedef struct specialization{
    char *specialist;
    char *time;
}specialization;
typedef struct graph{
    int hospitalId;
    char *hospitalName;
    char *hospitalAddress;
    specialization **record;
}Graph;
typedef struct graphPaths{
    int **paths;
    int size;
}GraphPaths;
typedef struct spnode{
    int nodeIndex;
    int weight;
    bool visited;

    struct spnode* next;
}spnode;
typedef spnode** Sp_tree;
typedef struct node{
    struct node* parent;
    struct node* lchild;
    struct node* rchild;
    int bf;
    char *key;
    int index;
}node;
typedef node* AVL;


void init(GraphPaths *gp);
void takeInputFromUser(char** area_name, char** specialist,char** time,AVL t);
Graph** updateNode(Graph *g, GraphPaths *gp, Graph **collectionOfNodes,AVL *t);
void bfsTravsersal(GraphPaths gp,int start_vertex);
void HealthCareLocator(GraphPaths *gp,Graph *g,Graph **collectionOfNodes);
Sp_tree primsAlgorithm(GraphPaths gp,int startVertex);
void printSpTree(Sp_tree t,GraphPaths gp);
void printCentered();
void displayMenu();
