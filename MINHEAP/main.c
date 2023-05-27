#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"heap.h"

int main()
{
	
	heap h;
	initHeap(&h, 10);

	insertintoHeap(&h, 2, "43-5");
	insertintoHeap(&h, 1, "12-12");
	
	insertintoHeap(&h, 3, "21-4");
	insertintoHeap(&h, 4, "6-4");
	insertintoHeap(&h, 5, "13-1");
	insertintoHeap(&h, 6, "9");
	insertintoHeap(&h, 7, "5");
	insertintoHeap(&h, 8, "4");
	traverse(h);
	

	
	return 0;
}
