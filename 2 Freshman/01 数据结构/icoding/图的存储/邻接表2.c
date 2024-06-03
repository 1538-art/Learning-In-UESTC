/*
typedef int VertexType;

typedef enum {
  DG, UDG
} GraphType;

typedef struct ArcNode {
  int adjvex;
  InfoPtr *info;
  struct ArcNode *nextarc;
} ArcNode;

typedef struct VNode {
  VertexType data;
  ArcNode *firstarc;
} VNode;

typedef struct {
  VNode vertex[MAX_VERTEX_NUM];
  int vexnum, arcnum;
  GraphType type;
} ListGraph;

int locate_vertex(ListGraph *G, VertexType v); //返回顶点 v 在vertex数组中的下标，如果v不存在，返回-1
bool del_vertex(ListGraph *G, VertexType v); //删除顶点 v
*/


#include <stdlib.h>
#include <stdio.h>
#include "graph.h" //请勿删除，否则检查不通过


// 删除顶点v，并释放与该顶点相关的内存空间
bool del_vertex(ListGraph *G, VertexType v) {
  int V = locate_vertex(G, v);
  // 检查顶点v是否存在
  if (V == -1) return false;
  
  // 先删除从该顶点出发的边
  ArcNode *P = G->vertex[V].firstarc;
  ArcNode *temp;
  while (P) {
    temp = P; // 存储当前节点
    P = P->nextarc; // 移动到下一个节点
    free(temp); // 释放当前节点的内存
    G->arcnum--; // 更新边的数量
  }
  G->vertex[V].firstarc = NULL; // 将该顶点的firstarc置为空
  
  // 更新顶点的数量
  G->vexnum--;
  
  // 将顶点数组中v后面的顶点向前移动，覆盖v的位置
  for (int i = V; i < G->vexnum; i++) {
    G->vertex[i] = G->vertex[i + 1];
  }
  
  // 再删除所有指向顶点v的边
  for (int i = 0; i < G->vexnum; i++) {
    P = G->vertex[i].firstarc;
    ArcNode *prev = NULL;
    while (P) {
      if (P->adjvex == V) { // 如果边的终点是v
        if (prev == NULL) { // 如果P是头节点
          G->vertex[i].firstarc = P->nextarc; // 跳过头节点
        } else {
          prev->nextarc = P->nextarc; // 跳过指向v的边
        }
        temp = P;
        P = P->nextarc;
        free(temp); // 释放指向v的边的内存
        G->arcnum--; // 更新边的数量
      } else {
        prev = P;
        P = P->nextarc;
      }
    }
  }
  
  return true; // 返回成功删除顶点
}