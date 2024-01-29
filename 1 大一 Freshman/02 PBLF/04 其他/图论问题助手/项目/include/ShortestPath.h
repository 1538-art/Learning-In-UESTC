#ifndef _SHORTESTPATH_H_
#define _SHORTESTPATH_H_
#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
#include "Status.h"
Status Dijkstra(FILE *fp,int Start,int End,std::vector<int> &Path,int &Distance);
#endif