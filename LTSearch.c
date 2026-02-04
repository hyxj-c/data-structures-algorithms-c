#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int Status;

typedef int KeyType;

typedef struct {
  KeyType key;
} ElemType;

// 顺序查找表
typedef struct {
  ElemType *data;
  int length;
} SSTable;

// 顺序查找
int search_Seq(SSTable sst, KeyType key) {
  for (int i = sst.length; i > 0; i--) {
    if (sst.data[i].key == key) {
      return i;
    }
  }
  return 0;
}

// 顺序查找带哨兵
int search_Seq_Sen(SSTable sst, KeyType key) {
  sst.data[0].key = key;
  int i;
  for (i = sst.length; sst.data[i].key != key; i--) {
  }
  return i;
}

// 二分查找
int search_Bin(SSTable sst, KeyType key) {
  int low = 1;
  int high = sst.length;
  while (low <= high) {
    int mid = (low + high) / 2;
    if (sst.data[mid].key == key) {
      return mid;
    }
    if (sst.data[mid].key > key) {
      high = mid - 1;
    } else {
      low = mid + 1;
    }
  }
  return 0;
}

// 二分查找递归实现
int search_Bin_Rec(SSTable sst, KeyType key, int low, int high) {
  while (low > high) {
    return 0;
  }
  int mid = (low + high) / 2;
  if (sst.data[mid].key == key) {
    return mid;
  }
  if (sst.data[mid].key > key) {
    search_Bin_Rec(sst, key, low, mid - 1);
  } else {
    search_Bin_Rec(sst, key, mid + 1, high);
  }
}

main() {
  SSTable sst;
  int n = 10;
  sst.length = n;
  for (int i = 1; i <= n; i++) {
    ElemType elem;
    elem.key = i;
    sst.data[i] = elem;
  }

  printf("key index:%d\n", search_Seq(sst, 3));
  printf("key index:%d\n", search_Seq_Sen(sst, 5));
  printf("key index:%d\n", search_Bin(sst, 10));
  printf("key index:%d\n", search_Bin_Rec(sst, 7, 1, n));
}