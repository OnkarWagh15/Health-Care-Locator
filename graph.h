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
Graph** init(Graph *g, GraphPaths *gp, Graph **collectionOfNodes);
void bfsTravsersal(GraphPaths gp,int start_vertex);
void HealthCareLocator(GraphPaths *gp,Graph *g,Graph **collectionOfNodes);
