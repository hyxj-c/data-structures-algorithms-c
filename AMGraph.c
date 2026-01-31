#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int Status;

/* 使用的队列代码 */
typedef int ElemType;
#define MAXSIZE 100

typedef struct {
  ElemType *elem;
  int front;
  int rear;
} SqQueue;

// 初始化顺序队列
Status initQueue_Sq(SqQueue *Q) {
  Q->elem = (ElemType *)malloc(MAXSIZE * sizeof(ElemType));
  if (Q->elem == NULL) {
    exit(OVERFLOW);
  }
  Q->front = Q->rear = 0;
  return OK;
}
// 入队
Status enQueue(SqQueue *Q, ElemType e) {
  // 判断队列是否已满
  if ((Q->rear + 1) % MAXSIZE == Q->front) {
    return ERROR;
  }
  Q->elem[Q->rear] = e;
  Q->rear = (Q->rear + 1) % MAXSIZE;
  return OK;
}
// 出队
Status deQueue(SqQueue *Q, ElemType *e) {
  // 判断队列是否已空
  if (Q->front == Q->rear) {
    return ERROR;
  }
  *e = Q->elem[Q->front];
  Q->front = (Q->front + 1) % MAXSIZE;
  return OK;
}
// 判断队列是否为空
int isEmpty(SqQueue Q) {
  if (Q.front == Q.rear) {
    return TRUE;
  }
  return FALSE;
}
/* 使用的队列代码 End */

#define MaxInt 32767 // 代表极大值
#define MVNum 100    // 最大顶点数量
typedef char VertexType;
typedef int EdgeType;

// 邻接矩阵图
typedef struct {
  VertexType vexes[MVNum];
  EdgeType edge[MVNum][MVNum];
  int vexNum;
  int edgeNum;
} AMGraph;

int locateVertex(AMGraph G, VertexType vex);

// 采用邻接矩阵创建无向网
void createUDGraph(AMGraph *G) {
  // 输入顶点的数量和边的数量
  printf("请输入顶点的数量\n");
  scanf("%d", &G->vexNum);
  printf("请输入边的数量\n");
  scanf("%d", &G->edgeNum);
  // 依次输入顶点
  printf("请输入%d个顶点\n", G->vexNum);
  for (int i = 0; i < G->vexNum; i++) {
    scanf(" %c", &G->vexes[i]);
  }
  // 初始化默认边为极大值
  for (int i = 0; i < G->vexNum; i++) {
    for (int j = 0; j < G->vexNum; j++) {
      G->edge[i][j] = MaxInt;
    }
  }
  // 输入边的顶点和边，创建边
  for (int i = 0; i < G->edgeNum; i++) {
    printf("请输入第%d条边和链接的两个顶点\n", i + 1);
    VertexType vertex1;
    VertexType vertex2;
    EdgeType edge;
    scanf("%d", &edge);
    scanf(" %c", &vertex1);
    scanf(" %c", &vertex2);
    // 定位顶点的下标
    int vexIndex1 = locateVertex(*G, vertex1);
    int vexIndex2 = locateVertex(*G, vertex2);
    // 给边赋值
    G->edge[vexIndex1][vexIndex2] = edge;
    G->edge[vexIndex2][vexIndex1] = edge;
  }
}

// 查找顶点的下标
int locateVertex(AMGraph G, VertexType vex) {
  for (int i = 0; i < G.vexNum; i++) {
    if (G.vexes[i] == vex) {
      return i;
    }
  }
  return -1;
}

int visited[MaxInt];
// 深度优先遍历图
void dFS(AMGraph G, int vexIndex) {
  // 访问下标为vexIndex的顶点
  printf("%c", G.vexes[vexIndex]);
  // 标识此顶点已被访问过
  visited[vexIndex] = 1;
  for (int i = 0; i < G.vexNum; i++) {
    // 找到当前顶点邻接的顶点并且未被访问的，进行访问
    if (G.edge[vexIndex][i] != MaxInt && visited[i] == 0) {
      dFS(G, i);
    }
  }
}

// 广度优先遍历图
void bFS(AMGraph G, int vexIndex) {
  SqQueue queue;
  initQueue_Sq(&queue);
  enQueue(&queue, vexIndex);
  visited[vexIndex] = 1;
  int vIndex;
  while (!isEmpty(queue)) {
    deQueue(&queue, &vIndex);
    printf("%c", G.vexes[vIndex]);
    for (int i = 0; i < G.vexNum; i++) {
      // 把该顶点相邻的，并且没有被访问过的顶点存入队列
      if (G.edge[vIndex][i] != MaxInt && visited[i] == 0) {
        enQueue(&queue, i);
        // 标识顶点为已被访问
        visited[i] = 1;
      }
    }
  }
}

// 最小生成树的边
typedef struct {
  EdgeType weight;
  int vexIndex1;
  int vexIndex2;
} Edge;

// prim算法创建最小生成树
void mSTPrim(AMGraph G, int vexIndex) {
  int vexIndexArr[G.vexNum]; // 存顶点下标的数组
  vexIndexArr[0] = vexIndex;
  // 最小生成树
  AMGraph mST;
  // 初始化默认边为极大值
  for (int i = 0; i < G.vexNum; i++) {
    for (int j = 0; j < G.vexNum; j++) {
      mST.edge[i][j] = MaxInt;
    }
  }
  mST.vexes[vexIndex] = G.vexes[vexIndex];
  mST.vexNum = 1;
  mST.edgeNum = 0;
  visited[vexIndex] = 1;

  while (mST.vexNum < G.vexNum) {
    Edge edgeWeights[G.edgeNum];
    int weightNum = 0;
    // 遍历每个顶点邻接的每一条边，放到edgeWeights数组
    for (int i = 0; i < mST.vexNum; i++) {
      for (int j = 0; j < G.vexNum; j++) {
        // 判断邻接的顶点是否已存入vexU数组，若邻接顶点已存入，说明链接的边已存入，或者再存入此边会形成环
        int index = vexIndexArr[i];
        if (G.edge[index][j] != MaxInt && visited[j] == 0) {
          Edge edge;
          edge.weight = G.edge[index][j];
          edge.vexIndex1 = index;
          edge.vexIndex2 = j;
          edgeWeights[weightNum++] = edge;
        }
      }
    }

    // 找到edgeWeights数组中权值最小的那条边
    EdgeType minWeight = edgeWeights[0].weight;
    Edge minEdge = edgeWeights[0];
    for (int i = 1; i < weightNum; i++) {
      if (edgeWeights[i].weight < minWeight) {
        minWeight = edgeWeights[i].weight;
        minEdge = edgeWeights[i];
      }
    }

    // 把边和顶点存入
    vexIndexArr[mST.vexNum] = minEdge.vexIndex2;
    mST.vexes[minEdge.vexIndex2] = G.vexes[minEdge.vexIndex2];
    mST.vexNum++;
    mST.edge[minEdge.vexIndex1][minEdge.vexIndex2] = minEdge.weight;
    mST.edge[minEdge.vexIndex2][minEdge.vexIndex1] = minEdge.weight;
    mST.edgeNum++;
    // 标识此顶点已存入
    visited[minEdge.vexIndex2] = 1;
  }

  printf("最小生成树:\n");
  for (int i = 0; i < mST.vexNum; i++) {
    for (int j = 0; j < mST.vexNum; j++) {
      printf("%7d", mST.edge[i][j]);
    }
    printf("\n");
  }
}

// 初始化visited数组
void initVisisted() {
  for (int i = 0; i < MVNum; i++) {
    visited[i] = 0;
  }
}

main() {
  AMGraph graph;
  createUDGraph(&graph);
  for (int i = 0; i < graph.vexNum; i++) {
    for (int j = 0; j < graph.vexNum; j++) {
      printf("%7d", graph.edge[i][j]);
    }
    printf("\n");
  }

  initVisisted();
  dFS(graph, 1);

  printf("\n");
  initVisisted();
  bFS(graph, 0);

  printf("\n");
  initVisisted();
  mSTPrim(graph, 0);
}