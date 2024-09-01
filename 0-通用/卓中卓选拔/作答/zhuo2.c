/*图中是否有环
定义一个带权无向图的数据结构如下
typedef struct Graphstruct{
    int vertex num;
    int edge num;
    int **edges;
}Graphstruct;
typedef struct Graphstruct *Graph;
typedef unsigned int Vertex;

typedef struct {
    Vertex w;
    Vertex w:
    int weight;
}Edge;
其中 edges 指向图的邻接矩阵，矩阵元素为对应边上的权重(权重为自然数，请使用该数据结构，从标准输入读入一个图，并判断
图是否有环，如果有环，则输出yes，否则输出no。
输入数据示例如下:
15,7
8,7,69
1,10,68
3,9,71
3,12_92
4,6,71
4,8,6
5,18,83
其中第1行分别为图中结点的个数 15、图中边的个数;之后的7行分别是各边的信息，以第2行为例，其表示结点0和7之间有权重
为69的无向边。*/



//发现某个结点有一条边指向已访问过的结点，并且这个已访问过的结点不是上一步访问的结点，则表示存在环。
#include <stdio.h>
#include <stdlib.h>

typedef struct GraphStruct {
    int vertex_num;
    int edge_num;
    int **edges;
} GraphStruct;
typedef struct GraphStruct *Graph;
typedef unsigned int Vertex;

typedef struct {
    Vertex v;
    Vertex w;
    int weight;
} Edge;

Graph createGraph(int vertex_num) {
    Graph g = (Graph)malloc(sizeof(GraphStruct));
    g->vertex_num = vertex_num;
    g->edge_num = 0;
    g->edges = (int **)malloc(vertex_num * sizeof(int *));
    for (int i = 0; i < vertex_num; i++) {
        g->edges[i] = (int *)malloc(vertex_num * sizeof(int));
        for (int j = 0; j < vertex_num; j++) {
            g->edges[i][j] = 0; // Initialize all edges to 0
        }
    }
    return g;
}

void addEdge(Graph g, Edge e) {
    g->edges[e.v][e.w] = e.weight;
    g->edges[e.w][e.v] = e.weight; // Since the graph is undirected
    g->edge_num++;
}

int hasCycleUtil(Graph g, int v, int visited[], int parent) {
    visited[v] = 1;

    for (int i = 0; i < g->vertex_num; i++) {
        if (g->edges[v][i]) { //判断是否有边
            if (!visited[i]) { //边的另一个端点是否被访问了
                if (hasCycleUtil(g, i, visited, v))//没有访问就访问一遍
                    return 1;
            } else if (i != parent) {
                return 1; // //发现某个结点有一条边指向已访问过的结点，并且这个已访问过的结点不是上一步访问的结点，则表示存在环。
            }
        }
    }
    return 0;
}

int hasCycle(Graph g) {
    int *visited = (int *)malloc(g->vertex_num * sizeof(int));
    for (int i = 0; i < g->vertex_num; i++) {
        visited[i] = 0; // Initialize all vertices as not visited
    }

    for (int u = 0; u < g->vertex_num; u++) {
        if (!visited[u]) { // Don't recur for u if already visited
            if (hasCycleUtil(g, u, visited, -1)) {
                free(visited);
                return 1;
            }
        }
    }

    free(visited);
    return 0;
}

int main() {
    int vertex_num, edge_num;
    scanf("%d,%d", &vertex_num, &edge_num);

    Graph g = createGraph(vertex_num);

    for (int i = 0; i < edge_num; i++) {
        Edge e;
        scanf("%u,%u,%d", &e.v, &e.w, &e.weight);
        addEdge(g, e);
    }

    if (hasCycle(g)) {
        printf("yes\n");
    } else {
        printf("no\n");
    }

    // Free allocated memory
    for (int i = 0; i < vertex_num; i++) {
        free(g->edges[i]);
    }
    free(g->edges);
    free(g);

    return 0;
}
