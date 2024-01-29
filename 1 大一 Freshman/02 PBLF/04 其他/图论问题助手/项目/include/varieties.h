#ifndef _VARIETIES_H_
#define _VARIETIES_H_
#include <cstring>
#include <vector>
#include <iostream>
#define N 105
typedef struct Edge{
    int v;
    int w;
} Edge;

std::vector<Edge> FileG[105];

void Clear() {
    for(int i=0;i<N;i++) FileG[i].clear();
}
#endif