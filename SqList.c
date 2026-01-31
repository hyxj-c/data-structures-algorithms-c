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
  int length;
} SqList;

// 初始化线性表
Status initList_Sq(SqList *l) {
  l->elem = (ElemType *) malloc(MAXSIZE * sizeof(ElemType));
  if (l->elem == NULL)
  {
    exit(OVERFLOW);
  }
  l->length = 0;
  return OK;
}

// 销毁线性表
void destroyList(SqList *l) {
  if (l->elem != NULL)
  {
    free(l->elem);
    l->elem = NULL;
  }
}

// 清空线性表
void clearList(SqList *l) {
  l->length = 0;
}

// 获取线性表长度
int getLength(SqList l) {
  return l.length;
}

// 判断线性表是否为空
int isEmpty(SqList l) {
  if (l.length == 0)
  {
    return 1;
  }
  return 0;
}

// 取线性表第i个位置的元素
int getElem(SqList l, int i, ElemType *e) {
  if (i < 1 || i > l.length)
  {
    return ERROR;
  }

  *e = l.elem[i - 1];
  return OK;
}

// 查找给定元素所在的位置，未找到返回0
int locateElem(SqList l, ElemType e) {
  for (int i = 0; i < l.length; i++)
  {
    if (l.elem[i] == e)
    {
      return i + 1;
    }
  }
  return 0;
}

// 在指定位置插入元素
Status listInsert_Sq(SqList *l, int i, ElemType e) {
  // 判断插入的位置是否合法
  if (i < 1 || i > l->length + 1 || (l->length == MAXSIZE))
  {
    return ERROR;
  }
  
  // 插入位置后面的元素向后移动
  for (int j = l->length; j >= i; j--)
  {
    l->elem[j] = l->elem[j - 1];
  }

  // 指定位置插入元素
  l->elem[i - 1] = e;
  
  // 长度加1
  l->length++;

  return OK;
}

// 删除指定位置的元素
Status listDelete_Sq(SqList *l, int i) {
  if (i < 1 || i > l->length)
  {
    return ERROR;
  }
  
  for (int j = i; j < l->length; j++) {
    l->elem[j - 1] = l->elem[j];
  }
  
  l->length--;

  return OK;
}

main() {
  SqList list;
  initList_Sq(&list);
  listInsert_Sq(&list, 1, 'c');
  listInsert_Sq(&list, 2, 'a');
  char elem;
  getElem(list, 1, &elem);
  printf("%c", elem);
}