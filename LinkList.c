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

// 初始化链表
Status initList_L(Lnode **L) {
  *L = (LinkList) malloc(sizeof(Lnode));
  if (*L == NULL)
  {
    exit(OVERFLOW);
  }
  
  (*L)->next = NULL;
  return OK;
}

// 判断链表是否为空
int isEmpety(LinkList L) {
  if (L->next)
  {
    return FALSE;
  }
  return TRUE;
}

// 销毁链表
Status destoryList_L(Lnode **L) {
  Lnode *p;
  while (*L)
  {
    p = *L;
    *L = (*L)->next;
    free(p);
  }
  *L = NULL;
  return OK;
}

// 清空链表
Status clearList_L(LinkList L) {
  Lnode *p, *q;
  p = L->next;
  while (p)
  {
    q = p->next;
    free(p);
    p = q;
  }
  L->next = NULL;
  return OK;
}

// 获取链表的长度
int listLength_L(LinkList L) {
  int i = 0;
  Lnode *p = L->next;
  while (p)
  {
    i++;
    p = p->next;
  }
  return i;
}

// 获取第i个元素
Status getElem_L(LinkList L, int i, ElemType *e) {
  Lnode *p = L->next;
  int j = 1;
  while (p && j < i)
  {
    p = p->next;
    j++;
  }
  if (p == NULL || i < j)
  {
    return ERROR;
  }
  *e = p->data;
  return OK;
}

// 查找元素地址
Lnode *locateAddrElem_L(LinkList L, ElemType e) {
  Lnode *p = L->next;

  while (p && strcmp(p->data.name, e.name) != 0)
  {
    p = p->next;
  }
  return p;
}

// 查找元素在链表中的位置
int locateElem_L(LinkList L, ElemType e) {
  Lnode *p = L->next;
  int j = 1;
  while (p && strcmp(p->data.no, e.no) != 0)
  {
    p = p->next;
    j++;
  }
  if (p == NULL)
  {
    return 0;
  }
  return j;
}

// 在指定位置插入一个元素
Status listInsert_L(LinkList L, int i, ElemType e) {
  Lnode *p = L;
  int j = 0;
  while (p && j < i - 1)
  {
    p = p->next;
    j++;
  }
  if (p == NULL || i < 1)
  {
    return ERROR;
  }
  Lnode *s = (Lnode*) malloc(sizeof(Lnode));
  s->data = e;
  s->next = p->next;
  p->next = s;
  return OK;
}

// 删除指定位置的节点
Status listDelete_L(LinkList L, int i) {
  Lnode *p = L;
  int j = 0;
  while (p->next && j < i - 1)
  {
    p = p->next;
    j++;
  }
  if (p->next == NULL || i < 1)
  {
    return ERROR;
  }
  Lnode *q = p->next;
  p->next = p->next->next;
  free(q);
  return OK;
}

// 头插法创建链表
void createList_H(LinkList *L, int n) {
  *L = (LinkList) malloc(sizeof(Lnode));
  (*L)->next = NULL;
  for (int i = n; i > 0; i--)
  {
    Lnode *p = (Lnode*) malloc(sizeof(Lnode));
    scanf(&p->data);
    p->next = (*L)->next;
    (*L)->next = p;
  }
}

// 尾插法创建链表
void createList_R(LinkList *L, int n) {
  *L = (LinkList) malloc(sizeof(Lnode));
  (*L)->next = NULL;
  Lnode *r = *L; // 定义尾节点，指向头指针
  for (int i = 0; i < n; i++)
  {
    Lnode *p = (Lnode*) malloc(sizeof(Lnode));
    scanf(&p->data);
    p->next = NULL;
    r->next = p;
    r = p;
  }
}

// 合并两个有序链表
LinkList mergeList_L(LinkList La, LinkList Lb) {
  LinkList Lc = (LinkList) malloc(sizeof(Lnode));
  Lc->next = NULL;
  
  Lnode *pa = La->next;
  Lnode *pb = Lb->next;
  Lnode *pc = Lc;
  
  while (pa && pb)
  {
    if (pa->data.score <= pb->data.score)
    {
      pc->next = pa;
      pc = pa;
      pa = pa->next;
    } else {
      pc->next = pb;
      pc = pb;
      pb = pb->next;
    }
  }
  pc->next = pa ? pa : pb;
  free(La);
  free(Lb);

  return Lc;
}

main() {
  ElemType e;
  LinkList linkList;
  createList_H(&linkList, 3);
  createList_R(&linkList, 10);
  printf("lengths %d\n", listLength_L(linkList));
  initList_L(&linkList);
  printf("插入 %d\n", listInsert_L(linkList, 1, e));
  printf("插入 %d\n", listInsert_L(linkList, 1, e));
  printf("插入 %d\n", listInsert_L(linkList, 2, e));
  printf("lengths %d\n", listLength_L(linkList));
  printf("删除 %d\n", listDelete_L(linkList, 1));
  printf("lengths %d\n", listLength_L(linkList));
  printf("获取 %d\n", getElem_L(linkList, 1, &e));
  clearList_L(linkList);
  destoryList_L(&linkList);
}