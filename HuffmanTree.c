#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int Status;

typedef float ElemType;

typedef struct {
  ElemType weight;
  int parent, lChild, rChild;
} HTNode, *HuffmanTree;

typedef struct {
  char **data;
} HuffmanCode;

// 创建哈夫曼树
void createHuffmanTree(HuffmanTree *HT, int n) {
  // 初始化哈夫曼树
  int m = 2 * n - 1;
  *HT = (HTNode *)malloc((m + 1) * sizeof(HTNode));
  for (int i = 1; i <= m; i++) {
    (*HT)[i].parent = (*HT)[i].lChild = (*HT)[i].rChild = 0;
  }
  for (int i = 1; i <= n; i++) {
    ElemType num;
    scanf("%f", &num);
    (*HT)[i].weight = num;
  }

  // 构造哈夫曼树
  for (int i = n + 1; i <= m; i++) {
    int l1, l2;
    select(*HT, i - 1, &l1, &l2);
    (*HT)[i].weight = (*HT)[l1].weight + (*HT)[l2].weight;
    (*HT)[i].lChild = l1;
    (*HT)[i].rChild = l2;
    (*HT)[l1].parent = (*HT)[l2].parent = i;
  }
}

// 从哈夫曼树中查找两个权重最小的节点
void select(HuffmanTree HT, int n, int *l1, int *l2) {
  int j;
  for (int i = 1; i <= n; i++) {
    if (HT[i].parent == 0) {
      *l1 = i;
      j = i + 1;
      break;
    }
  }
  for (int i = j; i <= n; i++) {
    if (HT[i].parent == 0) {
      *l2 = i;
      j = i + 1;
      break;
    }
  }
  if (HT[*l1].weight > HT[*l2].weight) {
    int temp = *l2;
    *l2 = *l1;
    *l1 = temp;
  }
  for (int i = j; i <= n; i++) {
    if (HT[i].parent == 0) {
      if (HT[i].weight < HT[*l1].weight) {
        int temp = *l1;
        *l1 = i;
        *l2 = temp;
      } else if (HT[i].weight < HT[*l2].weight) {
        *l2 = i;
      }
    }
  }
}

// 根据哈夫曼树创建哈夫曼编码
void createHuffmanCode(HuffmanTree HT, HuffmanCode *HC, int n) {
  HC->data = (char **)malloc((n + 1) * sizeof(char *));
  char *cd = (char *)malloc(n * sizeof(char));
  cd[n - 1] = '\0';

  for (int i = 1; i <= n; i++) {
    int parent = HT[i].parent;
    int start = n - 1;
    int child = i;
    while (parent != 0) {
      if (HT[parent].lChild == child) {
        // 是parent的左孩子，赋值为'0'
        cd[--start] = '0';
      } else {
        cd[--start] = '1';
      }
      child = parent;
      // 继续寻找父节点的父节点
      parent = HT[parent].parent;
    }
    // 动态创建字符数组
    HC->data[i] = (char *)malloc((n - start) * sizeof(char));
    // 复制字符串到哈夫曼编码字符数组中
    strcpy(HC->data[i], &cd[start]);
  }

  free(cd);
}

void printHuffmanTree(HuffmanTree HT, int n) {
  for (int i = 1; i <= n; i++) {
    printf("%3d weight:%.2f parent:%3d lChild:%3d rChild:%3d\n", i,
           HT[i].weight, HT[i].parent, HT[i].lChild, HT[i].rChild);
  }
}

void printHuffmanCode(HuffmanCode HC, int n) {
  for (int i = 1; i <= n; i++) {
    printf("%3d code:%s\n", i, HC.data[i]);
  }
}

void main() {
  HuffmanTree ht;
  int n = 7;
  // 5 29 7 8 14 23 3 11
  // 0.4 0.3 0.15 0.05 0.04 0.03 0.03
  createHuffmanTree(&ht, n);
  printHuffmanTree(ht, 2 * n - 1);
  HuffmanCode hc;
  createHuffmanCode(ht, &hc, n);
  printHuffmanCode(hc, n);
}