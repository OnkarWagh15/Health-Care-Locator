#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "heap.h"

void initHeap(heap *h, int size)
{
	h->Array = (id_time **)malloc(sizeof(id_time *) * size);
	if (!h->Array)
		return;
	h->size = size;
	h->rear = -1;
	return;
}

void insertintoHeap(heap *h, int id, char *time, int distance)
{

	id_time *temp;

	if (!h->Array)
		return;
	if (isFull(*h))
		return;

	h->Array[++h->rear] = (id_time *)malloc(sizeof(id_time));
	h->Array[h->rear]->time = time;
	h->Array[h->rear]->id = id;
	h->Array[h->rear]->distance = distance;
	int i = h->rear;

	while (i > 0)
	{
		char timep[30];
		strcpy(timep, h->Array[(i - 1) / 2]->time);
		char time[30];
		strcpy(time, h->Array[i]->time);

		char *t1 = (char *)malloc(sizeof(char) * 30);
		char *t2 = (char *)malloc(sizeof(char) * 30);
		int j = 0;
		while (timep[j] != '-' )
		{
			t1[j] = timep[j]; // t1 = parent
			j++;
		}
		j = 0;
		while (time[j] != '-')
		{
			t2[j] = time[j]; // t2 = child
			j++;
		}

		int x = atoi(t1);
		int y = atoi(t2);

		if (x >= y) // child is smaller than parent
		{

			temp = h->Array[i];
			h->Array[i] = h->Array[(i - 1) / 2];
			h->Array[(i - 1) / 2] = temp;
		}
		
		

		i = (i - 1) / 2;
	}
	return;
}

int isFull(heap h)
{
	return h.size - 1 == h.rear;
}

int isEmpty(heap h)
{
	return h.rear == -1;
}

id_time* deleteHeap(heap *h)
{
	if(!h->Array) return NULL;
	
	if(isEmpty(*h)) return NULL;
	
	id_time *temp = h->Array[0];
	h->Array[0] = h->Array[h->rear];
	h->rear --;
	
	heapifyMinHeap(h);
	return temp;
}

void heapifyMinHeap(heap *h)
{
	
	int i = 0;
	int iLeft, iRight;
	int iMin;
	int r = h->rear;
	
	while(1)
	{
		
		iLeft = 2*i+1;
		iRight = 2*i+2;
		
		if(iLeft > r) return;
		else
		{
			
			char timeLeft[30];
			strcpy(timeLeft,h->Array[iLeft]->time);
			
			char timeRight[30];
			strcpy(timeRight,h->Array[iRight]->time);
			

			char *tleft=(char *)malloc(sizeof(char) * 30);
			char *tright=(char *)malloc(sizeof(char) * 30);
			int j=0;
			while(timeLeft[j]!='-' && timeLeft[j]!='\0')
			{
				tleft[j]=timeLeft[j]; 
				j++;
			}
			
			j=0;
			while(timeRight[j]!='-' && timeRight[j]!='\0')
			{
				tright[j]=timeRight[j]; 
				j++;
			}
			
			int x = atoi(tleft);
			int y = atoi(tright);


			if (x>y)
				iMin = iRight;
			else
				iMin = iLeft;
		}

		
		char timeParent[30];
		strcpy(timeParent,h->Array[i]->time);
		

		char timeChild[30];
		if(iMin == iLeft)
		{
			strcpy(timeChild,h->Array[iLeft]->time);	
		}
		else
		{
			strcpy(timeChild,h->Array[iRight]->time);
		}
		

		char *tparent=(char *)malloc(sizeof(char) * 30);
		char *tchild=(char *)malloc(sizeof(char) * 30);
		int j=0;
		while(timeParent[j]!='-' && timeParent[j]!='\0')
		{
			tparent[j]=timeParent[j]; 
			j++;
		}
		j=0;
		while(timeChild[j]!='-' && timeChild[j]!='\0')
		{
			tchild[j]=timeChild[j]; 
			j++;
		}

		int p = atoi(tparent);
		int c = atoi(tchild);
	

		if(p < c) return;
		
		//swap(&(h->A[i]), &h->A[iMax]);
			id_time *temp;
			temp = h->Array[i];
			h->Array[i] = h->Array[iMin]; 
			h->Array[iMin] = temp;
			i = iMin;
	}
}
