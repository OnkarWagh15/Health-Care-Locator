typedef struct graph{
    int hospitalId;
    char *hospitalName;
    char *hospitalAddress;
    char *specialization;
    char *time;
}Graph;
typedef struct graphPaths{
    int **paths;
    int size;
}GraphPaths;
void init(Graph *g,GraphPaths *gp);
void bfsTravsersal(GraphPaths gp,int start_vertex);