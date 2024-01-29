#include "../include/Flow.h"
#define MAX_VERTEX 105
#define INF INT_MAX
void add(int u, int v, int c, std::vector<edge>& edges, std::vector<int> G[]);
bool BFS(int *vis, int *d, int S, int T, std::vector<edge>& edges, std::vector<int> G[]);
int DFS(int x, int a, int T, int* cur, int *d, std::vector<edge>& edges, std::vector<int> []);
int Dinic(int *d, int S, int T, std::vector<edge>& edges, std::vector<int> G[]);

Status MaxFlow(FILE* fp, int Source, int Sink, int& Flow) {
    
    if(fp == NULL) return ERROR;
    if(Source > 100 || Sink > 100) return ERROR;

    std::vector<edge> edges;
    std::vector<int> G[MAX_VERTEX];

    int d[MAX_VERTEX];
    memset(d, 0, sizeof(d));
    int u, v, c;
    while(fscanf(fp,"%d%d%d",&u,&v,&c)!=EOF) {
        add(u, v, c, edges, G);
    }
    Flow = Dinic(d,Source, Sink, edges, G);
    return SUCCESS;
}

void add(int u, int v, int c, std::vector<edge>& edges, std::vector<int> G[]) {
    edges.push_back(edge(u, v, c, 0));
    edges.push_back(edge(v, u, 0, 0));
    int sz = edges.size();
    G[u].push_back(sz - 2);
    G[v].push_back(sz - 1);
}

bool BFS(int d[], int S, int T, std::vector<edge>& edges, std::vector<int> G[]) {
    int vis[MAX_VERTEX];
    memset(vis, 0, sizeof(vis));
    std::queue<int> Q;
    Q.push(S);
    d[S] = 0;
    vis[S] = 1;
    while(!Q.empty()) {
        int x = Q.front(); Q.pop();
        for(int i = 0; i < G[x].size(); i ++) {
            int j = G[x][i];
            edge& e = edges[j];
            if(!vis[e.to] && e.cap > e.flow) {
                vis[e.to] = 1;
                d[e.to] = d[x] + 1;
                Q.push(e.to);
            }
        }
    }
    return vis[T];
}
int DFS(int x, int a, int T, int* cur, int *d, std::vector<edge>& edges, std::vector<int> G[]) {
    if(x == T || a == 0) return a;
    int flow = 0, f;
    for(int& i = cur[x]; i < G[x].size(); i ++) {
        edge& e = edges[G[x][i]];
        if(d[x] + 1 == d[e.to] && (f = DFS(e.to, std::min(a, e.cap - e.flow), T, cur, d, edges, G)) > 0) {
            e.flow += f;
			edges[G[x][i] ^ 1].flow -= f;
			flow += f;
			a -= f;
			if(a == 0) break;
        }
    }
    return flow;
}

int Dinic(int *d, int S, int T, std::vector<edge>& edges, std::vector<int> G[]) {
    int flow = 0;
    int cur[MAX_VERTEX];
    while(BFS(d, S, T, edges, G)) {
        memset(cur, 0, sizeof(cur));
        flow += DFS(S, INF, T, cur, d, edges, G);
    }
    return flow;
}