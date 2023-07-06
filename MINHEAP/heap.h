
typedef struct id_time
{
	int id;
	char *time;
	int distance;
}id_time;

typedef struct heap
{
	struct id_time **Array;
	int size;
	int rear;
}heap;

void initHeap(heap *h, int size);
void insertintoHeap(heap *h, int id, char *time, int distance);
int isFull(heap h);
void traverse(heap h);
void heapifyMinHeap(heap *h);
id_time* deleteHeap(heap *h);
int isEmpty(heap h);