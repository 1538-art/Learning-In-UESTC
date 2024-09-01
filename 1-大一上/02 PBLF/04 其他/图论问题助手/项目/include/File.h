#ifndef _FILE_H_
#define _FILE_H_

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <ctime>
#include "Status.h"
Status writeGraphToFile(FILE* fp);
Status readGraphFromFile(FILE* fp);
Status ModifyEdge(int From, int To, int Weight, int NewWeight);
Status AddEdge(int From, int To, int Weight);
Status DeleteEdge(int From, int To, int Weight);

#endif
