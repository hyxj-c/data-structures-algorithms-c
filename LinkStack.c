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

typedef struct StackNode {
  ElemType data;
  struct StackNode *next;
} StackNode, *LinkStack;

// 初始化链栈
Status initStack_L(LinkStack *S) {
  // 不带哨兵头节点
  *S = NULL;
  return OK;
}

// 是否为空 
int isEmpty(LinkStack S) {
  if (S == NULL)
  {
    return TRUE;
  }
  return FALSE;
}

// 入栈
Status push(LinkStack *S, ElemType e) {
  StackNode *p = (StackNode*) malloc(sizeof(StackNode));
  if (p == NULL)
  {
    return ERROR;
  }
  p->data = e;
  p->next = *S;
  *S = p; 
  return OK;
}

// 出栈
Status pop(LinkStack *S, ElemType *e) {
  // 判断栈是否已空
  if (*S == NULL)
  {
    return ERROR;
  }
  *e = (*S)->data;
  StackNode *p = *S;
  (*S) = (*S)->next;
  free(p);
  return OK;
}

// 获取栈顶元素
ElemType getTop(LinkStack S) {
  if (S != NULL)
  {
    return S->data;
  }
}

main() {
  LinkStack s;
  initStack_L(&s);
}