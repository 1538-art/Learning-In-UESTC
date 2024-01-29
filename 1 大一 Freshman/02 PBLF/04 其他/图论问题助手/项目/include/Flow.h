#ifndef _FLOW_H_
#define _FLOW_H_
#include "Status.h"
#include <vector>
#include <string.h>
#include <queue>
#include <stdio.h>
#include <climits>
typedef struct edge {
    int from, to, cap, flow;
    edge(int u, int v, int c, int f) : from(u),to(v),cap(c),flow(f){}
} edge;
Status MaxFlow(FILE* fp, int Source, int Sink, int& Flow);

#endif // _FLOW_H_