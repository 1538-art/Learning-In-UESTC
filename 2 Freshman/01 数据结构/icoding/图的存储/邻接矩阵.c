/*
typedef int VertexType;

typedef enum {
  DG, UDG // 有向图，无向图
} GraphType;

typedef struct {
  VertexType vertex[MAX_VERTEX_NUM]; //顶点向量
  int arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; //邻接矩阵
  int vexnum, arcnum;   //图的当前顶点数和弧数
  GraphType type;     //图的种类标志
} MatrixGraph;

int matrix_locate_vertex(MatrixGraph *MG, VertexType vex); //返回顶点 v 在vertex数组中的下标，如果v不存在，返回-1
bool matrix_insert_vertex(MatrixGraph *G, VertexType v);
bool matrix_insert_arc(MatrixGraph *G, VertexType v, VertexType w);
*/


#include <stdio.h>
#include "graph.h" // 请不要删除，否则检查不通过

bool matrix_insert_vertex(MatrixGraph *G, VertexType v) {
  if (G->vexnum == MAX_VERTEX_NUM)
    return false;
  if (matrix_locate_vertex(G, v) == -1) {
    G->vertex[G->vexnum++] = v;
    for (int i = 0; i < G->vexnum; i++)   // 初始化邻接矩阵
      G->arcs[i][G->vexnum - 1] = G->arcs[G->vexnum - 1][i] = 0;
    return true;
  } else
    return false;
}

bool matrix_insert_arc(MatrixGraph *G, VertexType v, VertexType w) {
  int v1 = matrix_locate_vertex(G, v), w1 = matrix_locate_vertex(G, w);
  if (v1 == -1 || w1 == -1 || G->arcs[v1][w1] == 1) //假设有向图里v1是弧尾，w1是弧头
    return false;
  if (G->type == DG) {//加边
    G->arcnum++;
    G->arcs[v1][w1] = 1;
    return true;
  } else {
    G->arcnum++;
    G->arcs[v1][w1] = G->arcs[w1][v1] = 1;
    return true;
  }
}