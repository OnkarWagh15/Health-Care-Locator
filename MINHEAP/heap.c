#include<stdio.h>
#include<stdlib.h>
#include"heap.h"
#include<limits.h>
#include<string.h>

void initHeap(heap *h, int size)
{
	h->Array= (id_time**)malloc(sizeof(id_time*) * size);
	if(!h->Array) return;
	h->size = size;
	h->rear = -1;
	return;
	
}

void insertintoHeap(heap *h, int id, char *time)
{	
	
	if(!h->Array) return;
	if(isFull(*h)) return;
	h->Array[++h->rear] = (id_time*)malloc(sizeof(id_time));
	h->Array[h->rear]->time = time;
	h->Array[h->rear]->id = id;
	int i = h->rear;
	
	
	
	 while(i>0)
	 {
	
		char timep[30];
		strcpy(timep,h->Array[(i-1)/2]->time);
		char time[30];
		strcpy(time,h->Array[i]->time);

		char *t1=(char *)malloc(sizeof(char) * 30);
		char *t2=(char *)malloc(sizeof(char) * 30);
		int j=0;
		while(timep[j]!='-' && timep[j]!='\0')
		{
			t1[j]=timep[j]; //t1 = parent
			j++;
		}
		j=0;
		while(time[j]!='-' && time[j]!='\0')
		{
			t2[j]=time[j]; //t2 = child
			j++;
		}

		int x = atoi(t1);
		int y = atoi(t2);
	
		if(x > y) //child is smaller than parent
		{
			id_time *temp;
			temp = h->Array[i];
			h->Array[i] = h->Array[(i-1)/2]; 
			h->Array[(i-1)/2] = temp;

		}
		
		
			i = (i-1)/2;
		
	}
	return;
}

int isFull(heap h)
{
	return h.size-1 == h.rear;
}

void traverse(heap h)
{
	
	for(int i =0; i<= h.rear; i++)
	{
		printf("%d ", h.Array[i]->id);
		printf("%s ", h.Array[i]->time);
		printf("\n");
	}
	return;
}
