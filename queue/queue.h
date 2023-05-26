typedef struct queueNode{
    int data;
    struct queueNode *next;

}Node;
typedef struct queue{
    struct queueNode *front;
    struct queueNode *rear;
}Queue;

void initQ(Queue *q);
void enqueue(Queue *q,int data);
void display(Queue q);
void dequeue(Queue *q);