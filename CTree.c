#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int Status;

typedef char ElemType;
#define MAXSIZE 100

typedef struct CTNode {
  int nodeL; // 节点位置
  struct CTNode *next;
} *ChildPtr;

typedef struct {
  ElemType data;
  ChildPtr firstChild; // 孩子链表头指针
} CTBox;

// 孩子链表树，找孩子节点容易
typedef struct {
  CTBox nodes[MAXSIZE];
  int r; // 根节点位置
  int n; // 元素的数量
} CTree;
