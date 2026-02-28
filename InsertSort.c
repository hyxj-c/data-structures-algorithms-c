#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int Status;

#define MAXSIXE 20

typedef int KeyType;

typedef struct {
  KeyType key;
} RecType;

typedef struct {
  RecType r[MAXSIXE + 1]; // 最大值加1是为了存储哨兵
  int length;
} SqList;

// 直接插入排序
void DInsertSort(SqList *L) {
  int i, j;
  for (i = 2; i <= L->length; i++) {
    // 判断要排序的元素是否比前一个元素小
    if (L->r[i].key < L->r[i - 1].key) {
      L->r[0] = L->r[i]; // 把要插入的元素存到哨兵位置
      for (j = i - 1; L->r[j].key > L->r[0].key; j--) {
        // 大于要插入元素的值，元素后移
        L->r[j + 1] = L->r[j];
      }
      L->r[j + 1] = L->r[0];
    }
  }
}

// 折半插入排序
void BInsertSort(SqList *L) {
  int i, j;
  for (int i = 2; i <= L->length; i++) {
    if (L->r[i].key < L->r[i - 1].key) {
      L->r[0] = L->r[i]; // 保存当前要插入的元素(可以不用哨兵，此处放到了哨兵位置)
      int low = 1;
      int high = i - 1;
      int mid;
      // 采用折半查找法找到元素的插入位置
      while (low <= high) {
        mid = (high + low) / 2;
        if (L->r[mid].key > L->r[0].key) {
          high = mid - 1;
        } else {
          low = mid + 1;
        }
      }
      // 循环结束，high+1为元素插入的位置，移动元素
      for (j = i - 1; j > high ; j--) {
        L->r[j + 1] = L->r[j];
      }
      L->r[high + 1] = L->r[0];
    }
  }
}

// 进行步长为dk的直接插入排序
void ShellInsert(SqList *L, int dk) {
  int i, j;
  for (i = dk + 1; i <= L->length; i++) {
    if (L->r[i].key < L->r[i - dk].key) {
      L->r[0] = L->r[i]; // 保存当前要插入的元素(可以不用哨兵，此处放到了哨兵位置)
      for(j = i - dk; j > 0 && L->r[j].key > L->r[0].key; j -= dk) {
        // 大于要插入元素的值，元素后移
        L->r[j + dk] = L->r[j];
      }
      L->r[j + dk] = L->r[0];
    }
  }
}

// 希尔插入排序
void ShellInsertSort(SqList *L, int dlta[], int t) {
  for (int i = 0; i < t; i++) {
    // 一趟增量为dlta[i]的插入排序
    ShellInsert(L, dlta[i]);
  }
}

main() {
  SqList list;
  list.length = 11;
  KeyType keys[11] = {3, 5, 10, 16, 7, 32, 83, 23, 54, 29, 96};
  for (int i = 0; i < list.length; i++) {
    RecType record;
    record.key  = keys[i];
    list.r[i + 1] = record;
  }

  // DInsertSort(&list);
  // BInsertSort(&list);
  int dlta[3] = {5, 3, 1};
  ShellInsertSort(&list, dlta, 3);
  for (int i = 1; i <= list.length; i++) {
    printf("%d ", list.r[i].key);
  }
}