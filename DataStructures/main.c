#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct {
  int info;
} DATA;

typedef struct Node {
  DATA data;
  struct Node *prev;
} NODE;

typedef struct Queue {
  NODE *head;
  NODE *tail;
  int size;
  int limit;
} QUEUE;


QUEUE *constructQueue(int limit);
void destructQueue(QUEUE *pQueue);
int enqueue(QUEUE *pQueue, NODE *pNode);
NODE *dequeue(QUEUE *pQueue);
int isEmpty(QUEUE *pQueue);
void print(QUEUE *pQueue);

QUEUE *constructQueue(int limit) {
  QUEUE *pQueue = (QUEUE*) malloc(sizeof (QUEUE));

  if (pQueue == NULL) {
    return NULL;
  }

  if (limit <= 0) {
    limit = 6535;
  }

  pQueue->limit = limit;
  pQueue->size = 0;
  pQueue->head = NULL;
  pQueue->tail = NULL;

  return pQueue;
}

void destructQueue(QUEUE *pQueue) {
  NODE *pNode;

  while (!isEmpty(pQueue)) {
    pNode = dequeue(pQueue);
    free(pNode);
  }

  free(pQueue);
}

int enqueue(QUEUE *pQueue, NODE *pNode) {
  if ((pQueue == NULL) || (pNode == NULL)) {
    return FALSE;
  }

  if (pQueue->size >= pQueue->limit) {
    return FALSE;
  }

  pNode->prev = NULL;

  if (pQueue->size == 0) {
    pQueue->head = pNode;
    pQueue->tail = pNode;
  } else {
    pQueue->tail->prev = pNode;
    pQueue->tail = pNode;
  }

  pQueue->size++;

  return TRUE;
}

NODE * dequeue(QUEUE *pQueue) {
  NODE *pNode;

  if (isEmpty(pQueue))
    return NULL;

  pNode = pQueue->head;
  pQueue->head = (pQueue->head)->prev;
  pQueue->size--;

  return pNode;
}

int isEmpty(QUEUE *pQueue) {
  if (pQueue == NULL) {
    return FALSE;
  }

  if (pQueue->size == 0) {
    return TRUE;
  } else {
    return FALSE;
  }
}

void print(QUEUE *pQueue) {
  NODE *pNode = pQueue->head;

  if (!pNode) {
    printf("\nQueue is empty");
    return;
  }

  printf("\nData :: %d", pNode->data.info);

  while (pNode->prev) {
    pNode = pNode->prev;
    printf("\nData :: %d", pNode->data.info);
  }


}

int main()
{
    int i;
    QUEUE *pQueue = constructQueue(7);
    NODE *pNode;

    for (i = 0; i <= 7; i++) {
      pNode = (NODE *) malloc(sizeof(NODE));
      pNode->data.info = 100 + i;
      enqueue(pQueue, pNode);
    }

    print(pQueue);

    destructQueue(pQueue);
    printf("\n\nDestructing...\n");

    print(pQueue);

    return 0;
}
