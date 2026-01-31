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

typedef struct {
  ElemType data;
  int parent; // 父节点位置下标
} PTNode;

// 双亲树，找父节点容易
typedef struct {
  PTNode nodes[MAXSIZE];
  int r; // 根节点位置
  int n; // 元素的数量
} PTree;
