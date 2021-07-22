#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int data[20];
	int front;
	int rear;
} queue;

queue* queue_create()
{
	queue *q = malloc(sizeof(queue));
	if (q) {
		q->front = 0;
		q->rear = 0;
	}

	return q;
}

void queue_add(queue *q, int data)
{
	q->data[q->rear++] = data;
}

int queue_del(queue *q)
{
	return q->data[q->front++];
}

int main(int argc, char *argv[])
{
	queue *q = queue_create();

	queue_add(q, 10);
	printf("%d\n", queue_del(q));
	queue_add(q, 20);
	printf("%d\n", queue_del(q));
	queue_add(q, 30);
	printf("%d\n", queue_del(q));
	queue_add(q, 40);
	printf("%d\n", queue_del(q));


	return 0;
}
