#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include"queue.h"


void initQ(Queue *q)
{
    q->front=q->rear=NULL;
}

void enqueue(Queue *q,int data)
{
    Node *nn=(Node *)malloc(sizeof(Node));
    nn->data=data;
    nn->next=NULL;
    if(q->rear==NULL && q->front==NULL)
    {
        q->rear=q->front=nn;
        return;
    }
    Node *temp=q->front;
    while(temp->next)
    {
        temp=temp->next;
    }
    temp->next=nn;
    q->rear=nn;
    return;


}
void display(Queue q)
{
    Node *temp=q.front;
    while(temp)
    {
        printf("%d->",temp->data);
        temp=temp->next;
    }
}
void dequeue(Queue *q)
{
    
    if(q->front==NULL)
        return;
    Node *temp=q->front;
    if(q->rear==q->front){
        free(q->front);
        q->front=q->rear=NULL;
        return;
    }
    Node *temp2=temp->next;
    temp->next=NULL;
    free(temp);
    temp=NULL;
    q->front=temp2;
    return;
}