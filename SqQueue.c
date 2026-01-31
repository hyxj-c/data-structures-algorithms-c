#include <stdlib.h>
#include <stdio.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int Status;

typedef char ElemType;
#define MAXSIZE 100

typedef struct {
  ElemType *elem;
  int front;
  int rear;
} SqQueue;

// 初始化顺序队列
Status initQueue_Sq(SqQueue *Q) {
  Q->elem = (ElemType*) malloc(MAXSIZE * sizeof(ElemType));
  if (Q->elem == NULL)
  {
    exit(OVERFLOW);
  }
  Q->front = Q->rear = 0;
  return OK;
}

// 销毁队列
Status destoryQueue(SqQueue *Q) {
  if (Q->elem != NULL)
  {
    free(Q->elem);
    Q->elem = NULL;
  }
  return OK;
}

// 判断队列是否为空
int isEmpty(SqQueue Q) {
  if (Q.front == Q.rear)
  {
    return TRUE;
  }
  return FALSE;
}

// 获取队列长度
int getLength(SqQueue Q) {
  return (Q.rear + MAXSIZE - Q.front) % MAXSIZE;
}

// 清空队列
Status clearQueue(SqQueue *Q) {
  Q->front = Q->rear = 0;
  return OK;
}

// 入队
Status enQueue(SqQueue *Q, ElemType e) {
  // 判断队列是否已满
  if ((Q->rear + 1) % MAXSIZE == Q->front)
  {
    return ERROR;
  }
  Q->elem[Q->rear] = e;
  Q->rear = (Q->rear + 1) % MAXSIZE;
  return OK;
}

// 出队
Status deQueue(SqQueue *Q, ElemType *e) {
  // 判断队列是否已空
  if (Q->front == Q->rear)
  {
    return ERROR;
  }
  *e = Q->elem[Q->front];
  Q->front = (Q->front + 1) % MAXSIZE;
  return OK;
}

// 取队头元素
ElemType getHead(SqQueue Q) {
  if (Q.front != Q.rear)
  {
    return Q.elem[Q.front];
  }
  return NULL;
}

main() {
  SqQueue q;
  initQueue_Sq(&q);
  ElemType e = 'a';
  enQueue(&q, e);
  enQueue(&q, 'b');
  deQueue(&q, &e);
  printf("%c\n", e);
  deQueue(&q, &e);
  printf("%c\n", e);
  printf("出队：%d\n", deQueue(&q, &e));
}