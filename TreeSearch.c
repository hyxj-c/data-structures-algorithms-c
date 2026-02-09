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

// 二叉排序树节点
typedef struct BSTNode {
  ElemType data;
  struct BSTNode *lchild, *rchild;
} BSTNode, *BSTree;

// 从二叉排序树中查找结点递归实现
BSTree searchBST_Rec(BSTree bst, KeyType key) {
  if (bst == NULL || key == bst->data.key) {
    return bst;
  }
  if (key < bst->data.key) {
    // 查找左子树
    return searchBST_Rec(bst->lchild, key);
  } else {
    // 查找右子树
    return searchBST_Rec(bst->rchild, key);
  }
}

// 从二叉排序树中查找结点
BSTree searchBST(BSTree bst, KeyType key) {
  while (bst != NULL && key != bst->data.key) {
    if (key < bst->data.key) {
      bst = bst->lchild;
    } else {
      bst = bst->rchild;
    }
  }
  return bst;
}

// 二叉排序树插入节点
void insertBST(BSTree *T, ElemType elem) {
  // 空树插入第一个节点
  if (*T == NULL) {
    *T = (BSTNode *) malloc(sizeof(BSTNode));
    (*T)->data = elem;
    (*T)->lchild = NULL;
    (*T)->rchild = NULL;
    return;
  }
  
  if (elem.key < (*T)->data.key) {
    // 在左子树插入
    if ((*T)->lchild == NULL) {
      BSTNode *node = (BSTNode *) malloc(sizeof(BSTNode));
      node->data = elem;
      node->lchild = NULL;
      node->rchild = NULL;
      (*T)->lchild = node;
    } else {
      insertBST(&(*T)->lchild, elem);
    }
  } else if (elem.key > (*T)->data.key) {
    // 在右子树插入
    if ((*T)->rchild == NULL) {
      BSTNode *node = (BSTNode *) malloc(sizeof(BSTNode));
      node->data = elem;
      node->lchild = NULL;
      node->rchild = NULL;
      (*T)->rchild = node;
    } else {
      insertBST(&(*T)->rchild, elem);
    }
  }
}

main() {
  // 在树中依次插入元素创建二叉排序树
  BSTree tree = NULL;
  KeyType data[] = {122, 99, 110, 105, 250, 200, 230, 216, 300};
  for (int i = 0; i < 9; i++) {
    ElemType elem;
    elem.key = data[i];
    insertBST(&tree, elem);
  }

  // 在二叉排序树中查找元素
  BSTree bSTree = searchBST(tree, 216);
  if (bSTree) {
    printf("%p，%d\n", bSTree, bSTree->data.key);
  } else {
    printf("%p\n", bSTree);
  }
}