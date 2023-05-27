
typedef struct id_time
{
	int id;
	char *time;
}id_time;

typedef struct heap
{
	struct id_time **Array;
	int size;
	int rear;
}heap;

void initHeap(heap *h, int size);
void insertintoHeap(heap *h, int id, char *time);

int isFull(heap h);
void traverse(heap h);