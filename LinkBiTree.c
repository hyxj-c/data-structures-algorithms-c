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

typedef struct {
  ElemType *base;
  ElemType *top;
  int stacksize;
} SqStack;

typedef struct {
  ElemType *elem;
  int front;
  int rear;
} SqQueue;

typedef struct BiTreeNode {
  ElemType data;
  struct BitreeNode *lchild, *rchild;
} BiTreeNode, *BiTree;

// 先序遍历二叉树
void preOrderTraverse(BiTree T) {
  if (T != NULL) // 递归的结束条件
  {
    printf("%c", T->data);
    preOrderTraverse(T->lchild);
    preOrderTraverse(T->rchild);
  }
}

// 中序遍历二叉树
void inOrderTraverse(BiTree T) {
  if (T != NULL) {
    inOrderTraverse(T->lchild);
    printf("%c", T->data);
    inOrderTraverse(T->rchild);
  }
}

// 后续遍历二叉树
void afterOrderTraverse(BiTree T) {
  if (T != NULL) {
    afterOrderTraverse(T->lchild);
    afterOrderTraverse(T->rchild);
    printf("%c", T->data);
  }
}

// 中序非递归遍历二叉树
// void inOrderUnrecTraverse(BiTree T) {
//   SqStack s;
//   initStack_Sq(&s);
//   BiTreeNode *p = T;
//   while (p != NULL || !isEmpty(s))
//   {
//     if (p != NULL)
//     {
//       push(&s, p);
//       p = p->lchild;
//     } else {
//       BiTreeNode *treeNode;
//       pop(&s, &treeNode);
//       printf("%c", treeNode->data);
//       p = treeNode->rchild;
//     }
//   }
// }

// // 层次遍历二叉树
// void levelOrderTraverse(BiTree T) {
//   SqQueue q;
//   initQueue_Sq(&q);
//   BiTreeNode *p;
//   enQueue(&q, T);
//   while (!isEmpty(q))
//   {
//     deQueue(&q, &p);
//     printf("%c", p->data);
//     if (p->lchild != NULL)
//     {
//       enQueue(&q, p->lchild);
//     }
//     if (p->rchild != NULL)
//     {
//       enQueue(&q, p->rchild);
//     }
//   }
// }

// 创建二叉树
Status createBiTree(BiTree *T) {
  char ch;
  scanf("%c", &ch);
  if (ch == '#') {
    *T = NULL;
  } else {
    *T = (BiTreeNode *)malloc(sizeof(BiTreeNode));
    if (*T == NULL) {
      exit(OVERFLOW);
    }
    (*T)->data = ch;
    createBiTree(&(*T)->lchild);
    createBiTree(&(*T)->rchild);
  }

  return OK;
}

// 复制二叉树
void copy(BiTree T, BiTree *NewT) {
  if (T == NULL) {
    *NewT = NULL;
  } else {
    *NewT = (BiTreeNode *)malloc(sizeof(BiTreeNode));
    (*NewT)->data = T->data;
    copy(T->lchild, &(*NewT)->lchild);
    copy(T->rchild, &(*NewT)->rchild);
  }
}

// 计算二叉树的深度
int depth(BiTree T) {
  if (T == NULL) {
    return 0;
  } else {
    int n = depth(T->lchild);
    int m = depth(T->rchild);
    if (n > m) {
      return n + 1;
    } else {
      return m + 1;
    }
  }
}

// 计算二叉树的节点个数
int nodeCount(BiTree T) {
  if (T == NULL) {
    return 0;
  } else {
    int n = nodeCount(T->lchild);
    int m = nodeCount(T->rchild);
    return n + m + 1;
  }
}

// 计算二叉树叶子节点的数量
int leafCount(BiTree T) {
  if (T == NULL) {
    return 0;
  }
  if (T->lchild == NULL && T->rchild == NULL) {
    return 1;
  } else {
    return leafCount(T->lchild) + leafCount(T->rchild);
  }
}

main() {
  BiTree t;
  createBiTree(&t);
  preOrderTraverse(t);
  printf("\n");
  BiTree newt;
  copy(t, &newt);
  preOrderTraverse(newt);
  printf("\n");
  printf("depth:%d\n", depth(t));
  printf("nodeCount:%d\n", nodeCount(t));
  printf("leafCount:%d\n", leafCount(t));
}