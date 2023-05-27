#define vertices 10

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
    struct spnode* next;
}spnode;
typedef spnode** Sp_tree;

void init(GraphPaths *gp);
void takeInputFromUser(char** area_name, char** specialist, char** time);
Graph** updateNode(Graph *g, GraphPaths *gp, Graph **collectionOfNodes);
void bfsTravsersal(GraphPaths gp,int start_vertex);
void HealthCareLocator(GraphPaths *gp,Graph *g,Graph **collectionOfNodes);
Sp_tree primsAlgorithm(GraphPaths gp,int startVertex);
void printSpTree(Sp_tree t,GraphPaths gp);
int **prim(int **g);