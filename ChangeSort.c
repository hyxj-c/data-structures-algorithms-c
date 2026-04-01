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
  RecType r[MAXSIXE];
  int length;
} SqList;

// 冒泡排序
void bubbleSort(SqList *L) {
  for (int i = 1; i < L->length; i++) {
    int flag = 0;
    for (int j = 0; j < L->length - i; j++) {
      if (L->r[j].key > L->r[j + 1].key) {
        // 前一个比后一个大，向后冒泡，交换位置
        RecType temp = L->r[j];
        L->r[j] = L->r[j + 1];
        L->r[j + 1] = temp;
        flag = 1;
      }
    }
    if (flag == 0) {
      // 这一轮比较没有发生交换，说明已经有序，结束以后轮数的比较
      break;
    }
  }
}

// 确定中心点位置，划分前后区域
int partition(SqList *L, int low, int high) {
  RecType pivot = L->r[low]; // 假设第一个值为中心点
  while (low < high) {
    // 找到比中心点小的值往前排
    while (low < high && L->r[high].key >= pivot.key) {
      high--;
    }
    L->r[low] = L->r[high];
    // 找到比中心点大的值往后排
    while (low < high && L->r[low].key <= pivot.key) {
      low++;
    }
    L->r[high] = L->r[low];
  }
  // 中心点的位置 = low = heigh
  L->r[low] = pivot;
  return low;
}

// 快速排序
void quickSort(SqList *L, int low, int high) {
  if (low < high) {
    int pivot = partition(L, low, high);
    // 递归排序前半部分
    quickSort(L, low, pivot - 1);
    // 递归排序后半部分
    quickSort(L, pivot + 1, high);
  }
}

main() {
  SqList list;
  list.length = 11;
  KeyType keys[11] = {3, 5, 10, 16, 7, 32, 83, 23, 54, 29, 96};
  for (int i = 0; i < list.length; i++) {
    RecType record;
    record.key  = keys[i];
    list.r[i] = record;
  }

  // bubbleSort(&list);
  quickSort(&list, 0, list.length - 1);
  for (int i = 0; i < list.length; i++) {
    printf("%d ", list.r[i].key);
  }
  
}