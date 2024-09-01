#include <stdio.h>
#include <stdlib.h>

// 定义图结构
typedef struct {
    int vertex_num;  // 顶点数量
    int edge_num;    // 边数量
    int **edges;     // 邻接矩阵
} GraphStruct;

typedef GraphStruct *Graph;
typedef unsigned int Vertex;

// 定义边结构
typedef struct {
    Vertex v;        // 边的起点
    Vertex w;        // 边的终点
    int weight;      // 边的权重
} Edge;

// 定义布尔类型
typedef enum {No, Yes} YesNo;

// 获取图的函数
Graph GetGraph() {
    int vertex_num, edge_num;
    scanf("%d,%d", &vertex_num, &edge_num);  // 输入顶点数和边数

    Graph pGraph = (Graph)malloc(sizeof(GraphStruct));
    pGraph->vertex_num = vertex_num;
    pGraph->edge_num = edge_num;
    pGraph->edges = (int **)malloc(vertex_num * sizeof(int *));  // 创建邻接矩阵
    for (int i = 0; i < vertex_num; i++) {
        pGraph->edges[i] = (int *)calloc(vertex_num, sizeof(int));  // 为邻接矩阵每个元素创建空间并赋0
    }

    for (int i = 0; i < edge_num; i++) {
        int v, w, weight;
        scanf("%d,%d,%d", &v, &w, &weight);
        pGraph->edges[v][w] = weight;
    }
    return pGraph;
}

// 打印图的邻接矩阵函数
void PrintAdjacencyMatrix(Graph graph) {
    printf("Adjacency Matrix:\n");
    for (int i = 0; i < graph->vertex_num; i++) {
        for (int j = 0; j < graph->vertex_num; j++) {
            printf("%d ", graph->edges[i][j]);
        }
        printf("\n");
    }
}

// 删除顶点的函数
void DeleteVertex(Graph graph, int vertex) {
    for (int i = 0; i < graph->vertex_num; i++) {
        graph->edges[i][vertex] = 0;
        graph->edges[vertex][i] = 0;
    }
}

// 深度优先搜索的辅助函数
void DFSUtil(Graph graph, Vertex v, YesNo *visited) {
    visited[v] = Yes;  // 标记当前顶点为已访问

    // 打印当前顶点
    //printf("%d ", v);

    // 递归访问所有邻接的未访问顶点
    for (int i = 0; i < graph->vertex_num; i++) {
        if (graph->edges[v][i] != 0 && visited[i] == No) {
            DFSUtil(graph, i, visited);
        }
    }
}


// 深度优先搜索的主函数
void DFS(Graph graph, Vertex start,YesNo* visited) {

    // 打印 DFS 遍历的起始信息
    // printf("DFS traversal starting from vertex %d:\n", start);

    DFSUtil(graph, start, visited);  // 从起始顶点开始DFS
}

YesNo* Creat_visited(Graph graph){
    YesNo *visited = (YesNo *)malloc(graph->vertex_num * sizeof(YesNo));  // 创建访问数组
    for (int i = 0; i < graph->vertex_num; i++) {
        visited[i] = No;  // 初始化为未访问
    }
    return visited;
}

void GetDomPoint(Graph pGraph,YesNo* visited,int num){
    printf("(%d#%d)",num,num);
    for(int i=1;i<pGraph->vertex_num;i++){
        if(visited[i]==No) {
            printf("(%d#%d)",num,i);
        }
    }
}

// 复制图的函数
Graph CopyGraph(Graph graph) {
    Graph newGraph = (Graph)malloc(sizeof(GraphStruct));
    newGraph->vertex_num = graph->vertex_num;
    newGraph->edge_num = graph->edge_num;
    newGraph->edges = (int **)malloc(graph->vertex_num * sizeof(int *));
    for (int i = 0; i < graph->vertex_num; i++) {
        newGraph->edges[i] = (int *)malloc(graph->vertex_num * sizeof(int));
        for (int j = 0; j < graph->vertex_num; j++) {
            newGraph->edges[i][j] = graph->edges[i][j];
        }
    }
    return newGraph;
}

// 主函数
int main() {
    Graph graph = GetGraph();  // 获取图
    Vertex start=0;
    Graph pGraph=CopyGraph(graph);

    for(int i=1;i<pGraph->vertex_num;i++) {
        YesNo *visited = Creat_visited(pGraph);
        visited[i] = -1;
        DeleteVertex(pGraph, i);
        DFS(pGraph, start, visited);
        GetDomPoint(pGraph, visited,i);
        pGraph=CopyGraph(graph);
    }


    // 释放图的内存
    for (int i = 0; i < graph->vertex_num; i++) {
        free(graph->edges[i]);
    }
    free(graph->edges);
    free(graph);

    return 0;
}