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

#define MVNum 100 // 最大顶点数量
typedef char VertexType;
typedef int ArcType;

typedef struct ArcNode {
  ArcType info;            // 边的权重
  int vexIndex;            // 临接顶点的下标
  struct ArcNode *nextArc; // 下一条边的指针
} ArcNode;

typedef struct VNode {
  VertexType data;   // 顶点信息
  ArcNode *firstArc; // 第一个边节点
} VNode, AdjArray[MVNum];

// 邻接表图
typedef struct {
  AdjArray vertexes;
  int vexNum;
  int arcNum;
} ALGraph;

int locateVertex(ALGraph G, VertexType vex);

// 采用邻接表创建无向网
void createUDGraph(ALGraph *G) {
  // 输入顶点的数量和边的数量
  printf("请输入顶点的数量\n");
  scanf("%d", &G->vexNum);
  printf("请输入边的数量\n");
  scanf("%d", &G->arcNum);
  // 依次输入顶点
  printf("请输入%d个顶点\n", G->vexNum);
  for (int i = 0; i < G->vexNum; i++) {
    scanf(" %c", &G->vertexes[i].data);
    G->vertexes[i].firstArc = NULL;
  }
  // 输入边
  for (int i = 0; i < G->arcNum; i++) {
    printf("请输入第%d条边和链接的两个顶点\n", i + 1);
    VertexType vertex1;
    VertexType vertex2;
    ArcType arc;
    scanf("%d", &arc);
    scanf(" %c", &vertex1);
    scanf(" %c", &vertex2);
    // 定位顶点的下标
    int vexIndex1 = locateVertex(*G, vertex1);
    int vexIndex2 = locateVertex(*G, vertex2);
    // 创建边节点
    ArcNode *arcNode1 = (ArcNode *)malloc(sizeof(ArcNode));
    arcNode1->info = arc;
    arcNode1->vexIndex = vexIndex1;
    arcNode1->nextArc = G->vertexes[vexIndex2].firstArc;
    ArcNode *arcNode2 = (ArcNode *)malloc(sizeof(ArcNode));
    arcNode2->info = arc;
    arcNode2->vexIndex = vexIndex2;
    arcNode2->nextArc = G->vertexes[vexIndex1].firstArc;
    // 设置顶点的边节点
    G->vertexes[vexIndex1].firstArc = arcNode2;
    G->vertexes[vexIndex2].firstArc = arcNode1;
  }
}

// 查找顶点的下标
int locateVertex(ALGraph G, VertexType vex) {
  for (int i = 0; i < G.vexNum; i++) {
    if (G.vertexes[i].data == vex) {
      return i;
    }
  }
  return -1;
}

int visited[MVNum];
// 深度优先遍历图
void dFS(ALGraph G, int vexIndex) {
  // 访问下标为vexIndex的顶点
  printf("%c", G.vertexes[vexIndex].data);
  // 标识此顶点已被访问
  visited[vexIndex] = 1;
  // 找到此顶点邻接的并且未被访问过的顶点进行访问
  ArcNode *arcNode = G.vertexes[vexIndex].firstArc;
  while (arcNode) {
    if (visited[arcNode->vexIndex] == 0) {
      dFS(G, arcNode->vexIndex);
    }
    arcNode = arcNode->nextArc;
  }
}

// 广度优先遍历树
void bFS(ALGraph G, int vexIndex) {
  SqQueue queue;
  initQueue_Sq(&queue);
  enQueue(&queue, vexIndex);
  visited[vexIndex] = 1;
  ElemType vIndex;
  while (!isEmpty(queue)) {
    deQueue(&queue, &vIndex);
    // 遍历出队的顶点
    printf("%c", G.vertexes[vIndex].data);
    // 将其邻接并未被访问过的顶点进行入队
    ArcNode *arcNode = G.vertexes[vIndex].firstArc;
    while (arcNode != NULL) {
      if (visited[arcNode->vexIndex] == 0) {
        enQueue(&queue, arcNode->vexIndex);
        // 标识为已被访问
        visited[arcNode->vexIndex] = 1;
      }
      arcNode = arcNode->nextArc;
    }
  }
}

// 初始化visited数组
void initVisisted() {
  for (int i = 0; i < MVNum; i++) {
    visited[i] = 0;
  }
}

// 最小生成树的边
typedef struct {
  ArcType weight;
  VertexType vertex1;
  VertexType vertex2;
} Edge;

// prim算法创建最小生成树
void mSTPrim(ALGraph G, int vexIndex) {
  Edge edgeTE[G.vexNum - 1]; // 存边的数组
  int edgeTENum = 0;
  VNode vexU[G.vexNum]; // 存顶点的数组
  int vexUNum = 0;
  vexU[vexUNum++] = G.vertexes[vexIndex];
  visited[vexIndex] = 1;

  while (vexUNum < G.vexNum) {
    Edge edgeWeights[G.arcNum];
    int weightNum = 0;
    // 遍历每个顶点邻接的每一条边，放到edgeWeights数组
    for (int i = 0; i < vexUNum; i++) {
      ArcNode *arcNode = vexU[i].firstArc;
      while (arcNode != NULL) {
        // 判断邻接的顶点是否已存入vexU数组，若邻接顶点已存入，说明链接的边已存入，或者再存入此边会形成环
        if (visited[arcNode->vexIndex] == 0) {
          Edge edge;
          edge.weight = arcNode->info;
          edge.vertex1 = vexU[i].data;
          edge.vertex2 = G.vertexes[arcNode->vexIndex].data;
          edgeWeights[weightNum++] = edge;
        }
        arcNode = arcNode->nextArc;
      }
    }

    // 找到edgeWeights数组中权值最小的那条边
    ArcType minWeight = edgeWeights[0].weight;
    Edge minEdge = edgeWeights[0];
    for (int i = 1; i < weightNum; i++) {
      if (edgeWeights[i].weight < minWeight) {
        minWeight = edgeWeights[i].weight;
        minEdge = edgeWeights[i];
      }
    }

    // 把边和顶点存入
    edgeTE[edgeTENum++] = minEdge;
    int vexIndex = locateVertex(G, minEdge.vertex2);
    vexU[vexUNum++] = G.vertexes[vexIndex];
    // 标识此顶点已存入vexU数组
    visited[vexIndex] = 1;
  }

  printf("最小生成树顶点:");
  for (int i = 0; i < vexUNum; i++) {
    printf("%c", vexU[i].data);
  }
  printf("\n");

  for (int i = 0; i < edgeTENum; i++) {
    printf("边值:%d,顶点1:%c,顶点2:%c\n", edgeTE[i].weight, edgeTE[i].vertex1,
           edgeTE[i].vertex2);
  }
}

main() {
  ALGraph graph;
  createUDGraph(&graph);
  for (int i = 0; i < graph.vexNum; i++) {
    printf("顶点%c,", graph.vertexes[i].data);
    ArcNode *arcNode = graph.vertexes[i].firstArc;
    while (arcNode) {
      printf("边:%d,邻接点:%d;", arcNode->info, arcNode->vexIndex);
      arcNode = arcNode->nextArc;
    }
    printf("\n");
  }

  // 深度优先遍历
  initVisisted();
  dFS(graph, 1);
  printf("\n");

  // 广度优先遍历
  initVisisted();
  bFS(graph, 0);
  printf("\n");

  // 最小生成树
  initVisisted();
  mSTPrim(graph, 0);
}