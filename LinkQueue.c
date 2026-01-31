#include <stdlib.h>
#include <stdio.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int Status;

typedef int ElemType;

typedef struct Qnode {
  ElemType data;
  struct Qnode *next;
} Qnode, *QueuePtr;

typedef struct {
  QueuePtr front;
  QueuePtr rear;
} LinkQueue;

// 初始化链队列
Status initQueue_L(LinkQueue *Q) {
  // 带哨兵头结点
  Qnode *p = (QueuePtr) malloc(sizeof(Qnode));
  if (p == NULL)
  {
    exit(OVERFLOW);
  }
  p->next = NULL;
  Q->front = Q->rear = p;
  return OK;
}

// 销毁链队列
Status destoryQueue_L(LinkQueue *Q) {
  while (Q->front != NULL)
  {
    QueuePtr p = Q->front;
    Q->front = p->next;
    free(p);
  }
  return OK;
}

// 入队
Status enQueue(LinkQueue *Q, ElemType e) {
  Qnode *p = (Qnode*) malloc(sizeof(Qnode));
  if (p == NULL)
  {
    return ERROR;
  }
  p->data = e;
  p->next = NULL;
  Q->rear->next = p;
  Q->rear = p;
  return OK;
}

// 出队
Status deQueue(LinkQueue *Q, ElemType *e) {
  // 判断队列是否为空
  if (Q->front == Q->rear)
  {
    return ERROR;
  }
  Qnode *p = Q->front->next;
  *e = p->data;
  Q->front->next = p->next;
  // 判断删除的是否是最后一个节点
  if (p == Q->rear)
  {
    Q->rear = Q->front;
  }
  free(p);
  return OK;
}

// 取队头元素
ElemType getHead(LinkQueue Q) {
  if (Q.front == Q.rear)
  {
    return NULL;
  }
  return Q.front->next->data;
}

main() {
  LinkQueue q;
  initQueue_L(&q);
  enQueue(&q, 1);
  enQueue(&q, 2);
  ElemType e;
  deQueue(&q, &e);
  printf("%d\n", e);
  deQueue(&q, &e);
  printf("%d\n", e);
  printf("出队：%d\n", deQueue(&q, &e));
}