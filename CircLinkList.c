#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int Status;

typedef struct {
  char name[8];
  char no[8];
  int score;
} ElemType;

typedef struct Lnode {
  ElemType data;
  struct Lnode *next;
} Lnode, *LinkList;

// 初始化循环链表
Status initList_CL(LinkList *L) {
  *L = (LinkList) malloc(sizeof(Lnode));
  if (*L == NULL)
  {
    exit(OVERFLOW);
  }
  (*L)->next = (*L);
  return OK;
}

int listLength_CL(LinkList L) {
  int i = 0;
  Lnode *h = L;
  Lnode *p = L->next;
  while (h != p)
  {
    i++;
    p = p->next;
  }
  return i;
}

// 在指定位置插入一个元素
Status insertList_CL(LinkList L, int i, ElemType e) {
  if (i > listLength_CL(L) + 1 || i < 1)
  {
    return ERROR;
  }

  Lnode *p = L;
  while (i > 1)
  {
    p = p->next;
    i--;
  }
  Lnode *s = (Lnode*) malloc(sizeof(Lnode));
  s->data = e;
  s->next = p->next;
  p->next = s;
  return OK;
}

main() {
  LinkList linkList;
  ElemType e;
  initList_CL(&linkList);
  printf("length:%d\n", listLength_CL(linkList));
  printf("insert:%d\n", insertList_CL(linkList, 2, e));
  printf("insert:%d\n", insertList_CL(linkList, 1, e));
  printf("insert:%d\n", insertList_CL(linkList, 2, e));
  printf("insert:%d\n", insertList_CL(linkList, 2, e));
  printf("length:%d\n", listLength_CL(linkList));
}