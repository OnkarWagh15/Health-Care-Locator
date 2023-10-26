#define MAX_LINE_LENGTH 1000
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "graph.h"
#include "AVLTREE/AVLoperations.c"
#include "MINHEAP/heap.c"

void init(GraphPaths *gp)
{
    FILE *path;
    int kj;
    path = fopen("path.txt", "r");
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

Graph **updateNode(Graph *g, GraphPaths *gp, Graph **collectionOfNodes, AVL *t)
{
    FILE *ptr;
    ptr = fopen("dataset.txt", "r");
    if (!ptr)
        return NULL;
    int size = 0;
    fscanf(ptr, "%d", &size);
    collectionOfNodes = (Graph **)malloc(sizeof(Graph *) * size);
    char hospiAddr[300] = "xyz";
    char hospiName[300] = "xyz";
    int id = -1;
    int i = -1;
    int j = 0;
    int flag = 0;
    int noOfNodes = 0;
    while (!feof(ptr))
    {
        fscanf(ptr, "%s", hospiAddr);
        fscanf(ptr, "%s", hospiName);

        if (flag == 0)
        {
            g->hospitalId = ++id;

            g->hospitalAddress = (char *)malloc(sizeof(char) * 200);
            strcpy(g->hospitalAddress, hospiAddr);
            g->hospitalName = (char *)malloc(sizeof(char) * 200);
            strcpy(g->hospitalName, hospiName);
            collectionOfNodes[++i] = g;
            g->record = (specialization **)malloc(sizeof(specialization *) * 150);
            j = 0;

            flag = 1;
            noOfNodes++;
        }
        if (flag == 1 && strcmp(g->hospitalAddress, hospiAddr) != 0 && strcmp(g->hospitalName, hospiName) != 0)
        {
            g = (Graph *)malloc(sizeof(Graph));
            (*g).hospitalId = ++id;
            g->hospitalAddress = (char *)malloc(sizeof(char) * 200);
            strcpy(g->hospitalAddress, hospiAddr);

            g->hospitalName = (char *)malloc(sizeof(char) * 200);
            strcpy(g->hospitalName, hospiName);

            collectionOfNodes[++i] = g;
            g->record = (specialization **)malloc(sizeof(specialization *) * 150);
            j = 0;

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
                g->hospitalAddress = (char *)malloc(sizeof(char) * 200);
                strcpy(g->hospitalAddress, hospiAddr);

                g->hospitalName = (char *)malloc(sizeof(char) * 200);
                strcpy(g->hospitalName, hospiName);

                collectionOfNodes[++i] = g;
                g->record = (specialization **)malloc(sizeof(specialization *) * 150);
                j = 0;

                noOfNodes++;
            }
        }
        g->record[j] = (specialization *)malloc(sizeof(specialization));
        g->record[j]->specialist = (char *)malloc(sizeof(char));
        g->record[j]->time = (char *)malloc(sizeof(char));
        fscanf(ptr, "%s", g->record[j]->specialist);
        fscanf(ptr, "%s", g->record[j++]->time);

        insert(t, g->hospitalAddress, i);
    }
    return collectionOfNodes;
}

char *strupr(char *str)
{
    unsigned char *p = (unsigned char *)str;

    while (*p)
    {
        *p = toupper((unsigned char)*p);
        p++;
    }

    return str;
}

void printSpecialist()
{
    FILE *file;
    char line[MAX_LINE_LENGTH];

    file = fopen("Specialist.txt", "r");
    printf("SPECIALISTS AVAILABLE - \n");
    if (file == NULL)
    {
        printf("Unable to open the file.\n");
        return;
    }

    while (fgets(line, MAX_LINE_LENGTH, file) != NULL)
    {
        printf("\n%s", line);
    }
    printf("\n\n\n\n");
    fclose(file);
}

void printCentered()
{
    struct winsize w, w1, w2;
    const char *star1 = "*************************************";
    const char *text = "H E A L T H C A R E  L O C A T O R";
    const char *star2 = "*************************************";
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    int terminal_width = w.ws_col;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w1);
    int terminal_width1 = w1.ws_col;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w2);
    int terminal_width2 = w2.ws_col;

    int text_length1 = strlen(star1);
    int text_length = strlen(text);
    int text_length2 = strlen(star2);
    int padding = (terminal_width - text_length) / 2;
    int padding1 = (terminal_width1 - text_length1) / 2;
    int padding2 = (terminal_width2 - text_length2) / 2;

    printf("\033[%dC%s\n", padding1, star1);
    printf("\n");
    printf("\033[%dC%s\n", padding, text);
    printf("\n");
    printf("\033[%dC%s\n", padding2, star2);
    printf("\n");
}


void displayMenu()
{
    while (1)
    {
        printCentered();
        printf("\n1. Locate a Hospital near you");
        printf("\n2. Find your Specialist");
        printf("\n3. EXIT, Thank you");
        int choice;
        printf("\n\nEnter your choice : ");
        scanf("%d", &choice);

        system("clear");
        printCentered();
        switch (choice)
        {
        case 1:
            Graph g;
            GraphPaths gp;
            Graph **collectionOfNodes;
            HealthCareLocator(&gp, &g, collectionOfNodes);

            break;
        case 2:
            printSpecialist();
            break;

        case 3:
            // system("clear");
            printf("\nTake Care!!\n");
            exit(0);
        default:
            printf("Invalid option");
            break;
        }
    }
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

void searchForUserChoice(AVL t, char userChoice)
{
    if (!t)
    {
        return;
    }

    if (userChoice == t->key[0])
    {
        printf("\n%s\n", t->key);
    }

    searchForUserChoice(t->lchild, userChoice);
    searchForUserChoice(t->rchild, userChoice);

    return;
}

void takeInputFromUser(char **area_name, char **specialist, char **time, AVL t)
{
    char userchoice;

    print_styled_input("Enter the area name");
    scanf("%s", *area_name);
    if (search(t, *area_name) == -1)
    {
        printf("\n\nI guess you spelled it wrong!\n\n");
        searchForUserChoice(t, toupper(*area_name[0]));
        printf("\n\nWere you looking for any of these?? (y/n)\t");
        scanf("%c", &userchoice);
        scanf("%c", &userchoice);
        if (userchoice == 'y')
        {
            print_styled_input("Enter the area name");
            scanf("%s", *area_name);
        }
        else
        {
            printf("\nIt seems like your area is out of reachability\n\n");
            displayMenu();
        }
        //}
    }
    print_styled_input("Enter the specialist required");
    scanf("%s", *specialist);
    print_styled_input("Enter time slot");
    scanf("%s", *time);
    printf("\n\nDisplaying Availabilty of %s at hospital from %s onwards:", *specialist, *time);

    return;
}

int findMinDistanceNode(int dist[], bool visited[], int numNodes)
{
    int minDistance = INT_MAX;
    int minIndex = -1;

    for (int i = 0; i < numNodes; i++)
    {
        if (!visited[i] && dist[i] < minDistance)
        {
            minDistance = dist[i];
            minIndex = i;
        }
    }

    return minIndex;
}

int findMinimumDistance(int **graph, int numNodes, int source, int destination)
{
    int dist[MAX_NODES];
    bool visited[MAX_NODES];

    for (int i = 0; i < numNodes; i++)
    {
        dist[i] = INT_MAX;
        visited[i] = false;
    }

    dist[source] = 0;

    for (int count = 0; count < numNodes - 1; count++)
    {
        int u = findMinDistanceNode(dist, visited, numNodes);
        visited[u] = true;

        for (int v = 0; v < numNodes; v++)
        {
            if (!visited[v] && graph[u][v] && (dist[u] != INT_MAX) && dist[u] + graph[u][v] < dist[v])
            {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    return dist[destination];
}

int timecomparator(char *docTime, char *userTime)
{
    char *docT = (char *)malloc(sizeof(char) * 30);
    char *userT = (char *)malloc(sizeof(char) * 30);
    int j = 0;
    while (docTime[j] != '-')
    {
        docT[j] = docTime[j]; // t1 = parent
        j++;
    }
    j = 0;
    while (userTime[j] != '-')
    {
        userT[j] = userTime[j]; // t2 = child
        j++;
    }

    int d = atoi(docT);
    int u = atoi(userT);

    if (d >= u) // child is smaller than parent
    {

        return 1;
    }
    else
    {
        return 0;
    }
}

void HealthCareLocator(GraphPaths *gp, Graph *g, Graph **collectionOfNodes)
{
    init(gp);
    AVL t;
    initTree(&t);
    collectionOfNodes = updateNode(&(*g), &(*gp), &(*collectionOfNodes), &t);
    int i, j = 0;
    char *area_name = (char *)malloc(sizeof(char) * 50);
    char *specialist = (char *)malloc(sizeof(char) * 50);
    char *time = (char *)malloc(sizeof(char) * 50);

    takeInputFromUser(&area_name, &specialist, &time, t);

    heap h;
    initHeap(&h, gp->size);
    j = 0;
    int minDistance = 1;

    int startVertex = search(t, area_name);
    if (startVertex < 0)
    {
        printf("\n\nSorry! We Could Not Find You a Hospital!!\n");
        exit(0);
    }
    for (i = 0; i < vertices; i++)
    {
        j = 0;
        while (collectionOfNodes[i]->record[j])
        {
            if (strcmp(collectionOfNodes[i]->record[j]->specialist, specialist) == 0 && (timecomparator(collectionOfNodes[i]->record[j]->time, time)) == 1)
            {
                minDistance = findMinimumDistance(gp->paths, gp->size, startVertex, i);

                insertintoHeap(&h, i, collectionOfNodes[i]->record[j]->time, minDistance);
            }
            j++;
        }
    }

    char fileChoice;
    printf("\n\nDo you want the Data in a file? (y/n): ");
    scanf("%c", &fileChoice);
    scanf("%c", &fileChoice);

    FILE *fp = fopen("User_Output.txt", "w");

    if (fileChoice == 'n')
    {
        printf("\n");
        printf("\nLooking for specialist: %s\n\n", specialist);
        printf("======================================================================================================================================\n");
        printf("\033[30m");
        printf("\033[46m");
        printf("| %-4s | %-75s | %-20s | %-8s | %-1s |\n", "ID", "Hospital Name", "Address", "Time", "Distance");
        printf("\033[0m");
        printf("======================================================================================================================================");
        printf("\033[0m");
        printf("\n");

        int var = 21;
        char continueChoice;

        while (!isEmpty(h))
        {
            for (i = 1; i <= var; i++)
            {
                id_time *t = deleteHeap(&h);
                if (h.Array[i])
                {
                    printf("| %-4d | %-75s | %-20s | %-8s | %-2d Km |\n", i, collectionOfNodes[h.Array[i]->id]->hospitalName, collectionOfNodes[h.Array[i]->id]->hospitalAddress, t->time, t->distance);
                    printf("--------------------------------------------------------------------------------------------------------------------------------------\n");
                    if (i % 20 == 0)
                    {
                        printf("\nShow more (y/n): ");
                        scanf("%c", &continueChoice);
                        scanf("%c", &continueChoice);

                        if (continueChoice == 'n')
                            break;
                        else if (continueChoice == 'y')
                        {
                            printf("--------------------------------------------------------------------------------------------------------------------------------------\n");
                            var = var + 20;
                        }
                    }
                }
            }
            if (continueChoice == 'n')
                break;
        }
        printf("\n\n");
    }
    else if (fileChoice == 'y')
    {
        int i = 1;
        while (!isEmpty(h))
        {
            id_time *t = deleteHeap(&h);
            if (h.Array[i])
            {
                fprintf(fp, "%d - %s\t%s\t%s\t%d Km\n", i, collectionOfNodes[h.Array[i]->id]->hospitalName, collectionOfNodes[h.Array[i]->id]->hospitalAddress, t->time, t->distance);
                i++;
            }
            fprintf(fp, "\n");
        }
        printf("\nData Printed in File!!\n");
        fclose(fp);
    }
    else {
        printf("\nInvalid Choice\n");
    }
}