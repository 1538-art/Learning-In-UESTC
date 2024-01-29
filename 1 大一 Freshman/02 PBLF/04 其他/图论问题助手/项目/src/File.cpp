#include "../include/File.h"
#include "../include/varieties.h"
#include "../include/Status.h"
#define MAX_VERTEX 105

Status writeGraphToFile(FILE* fp) {
    if(fp == NULL) return ERROR;
    for(int i = 0; i < MAX_VERTEX; i ++) {
        for(int j = 0; j < FileG[i].size(); j ++) {
            fprintf(fp, "%d %d %d\n", i, FileG[i][j].v, FileG[i][j].w);
        }
    }
    Clear();
    return SUCCESS;
}

Status readGraphFromFile(FILE* fp) {
    if(fp == NULL) return ERROR;
    int u, v ,w;
    while(fscanf(fp,"%d%d%d",&u, &v, &w)!=EOF)
        FileG[u].push_back(Edge{v, w});
    return SUCCESS;
}
/* 把 From 到 To 的边权为 Weight 的边改成 NewWeight
 * 改了返回 SUCCESS，不存在完全一致的边 (u,v,w) 就返回 ERROR
 */
Status ModifyEdge(int From, int To, int Weight, int NewWeight) {
    for(int i = 0; i < FileG[From].size(); i ++) {
        if(FileG[From][i].v == To && FileG[From][i].w == Weight) {
            FileG[From][i].w = NewWeight;
            return SUCCESS;
        }
    }
    return ERROR;
}

/* 加 From 到 To 的边权 Weight 的边
 * 能加返回 SUCCESS，不能加返回 ERROR
 */
Status AddEdge(int From, int To, int Weight) {
    if(From > 100 || To > 100) return ERROR;
    FileG[From].push_back(Edge{To, Weight});
    return SUCCESS;
}

/* 把 From 到 To 的边权为 Weight 的边删掉
 * 改了返回 SUCCESS，不存在完全一致的边 (u,v,w) 就返回 ERROR
 */
Status DeleteEdge(int From, int To, int Weight) {
    for(int i = 0; i < FileG[From].size(); i ++) {
        if(FileG[From][i].v == To && FileG[From][i].w == Weight) {
            FileG[From].erase(FileG[From].begin() + i);
            return SUCCESS;
        }
    }
    return ERROR;
}