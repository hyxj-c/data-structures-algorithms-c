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
#define MAXSIZE 100

typedef struct {
  ElemType *base;
  ElemType *top;
  int stacksize;
} SqStack;

// 初始化顺序栈
Status initStack_Sq(SqStack *S) {
  S->base = (ElemType*) malloc(MAXSIZE * sizeof(ElemType));
  if (S->base == NULL)
  {
    exit(OVERFLOW);
  }
  S->top = S->base;
  S->stacksize = MAXSIZE;
  return OK;
}

// 销毁栈
Status destoryStack(SqStack *S) {
  if (S->base != NULL)
  {
    free(S->base);
    S->base = S->top = NULL;
    S->stacksize = 0;
  }
  return OK;
}

// 判断栈是否为空
int isEmpty(SqStack S) {
  if (S.base == S.top)
  {
    return TRUE;
  }
  return FALSE;
}

// 获取栈的长度
int getLength(SqStack S) {
  return S.top - S.base;
}

// 清空栈
Status clearStack(SqStack *S) {
  S->top = S->base;
  return OK;
}

// 入栈
Status push(SqStack *S, ElemType e) {
  // 判断栈是否已满
  if (S->top - S->base == MAXSIZE)
  {
    return ERROR;
  }
  *S->top = e;
  S->top++;
  return OK;
}

// 出栈
Status pop(SqStack *S, ElemType *e) {
  // 判断栈是否已空
  if (S->top == S->base)
  {
    return ERROR;
  }
  *e = *(--S->top);
  return OK;
}

main() {
  SqStack s;
  initStack_Sq(&s);
  push(&s, 1);
  push(&s, 2);
  ElemType e;
  pop(&s, &e);
  printf("%d\n", e);
}