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
bool insert_vertex(ListGraph *G, VertexType v);

bool insert_arc(ListGraph *G, VertexType v, VertexType w);
*/


#include <stdio.h>
#include <stdlib.h>
#include "graph.h" //请勿删除，否则检查不通过

bool insert_vertex(ListGraph *G, VertexType v) {
  int n = locate_vertex(G, v);
  if (n == -1) {
    G->vertex[G->vexnum].data = v;
    G->vertex[G->vexnum].firstarc = NULL;
    G->vexnum++;
    return true;
  } else
    return false;
}


bool insert_arc(ListGraph *G, VertexType v, VertexType w) {
  
  int i = locate_vertex(G, v);
  int j = locate_vertex(G, w);
  
  //判结点是否存在,不存在就返回false
  if (i == -1 || j == -1)
    return false;
  
  ArcNode *p;
  for (p = G->vertex[i].firstarc; p; p = p->nextarc)
    if (p->adjvex == j) return false; //判边是否存在,存在就返回false

  // 分配内存
  p = (ArcNode *) malloc(sizeof(ArcNode));
  p->adjvex = j;
  G->arcnum++;
  if (!G->vertex[i].firstarc)//空的情况
    G->vertex[i].firstarc = p;
  else {//头插
    p->nextarc = G->vertex[i].firstarc->nextarc;
    G->vertex[i].firstarc = p;
  }
  return true;
}
