#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include"queue.h"

void main()
{
    Queue q;
    initQ(&q);
    enqueue(&q,10);
    enqueue(&q,20);
    enqueue(&q,30);
    enqueue(&q,40);
    display(q);
    dequeue(&q);
    dequeue(&q);
    printf("\n");
    display(q);
    printf("\n%d",q.front->data);
    printf("\n%d",q.rear->data);


}