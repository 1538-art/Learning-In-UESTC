#include "../include/ShortestPath.h"
#define SP_MAX_VERTEX 105
Status Dijkstra(FILE *fp,int Start,int End,std::vector<int> &Path,int &Distance){
    Path.clear();
    if(Start>100||End>100) return ERROR;
    std::vector<std::pair<int,int>> N[SP_MAX_VERTEX];
    std::string s;
    int fr,to,va,pa[SP_MAX_VERTEX],dist[SP_MAX_VERTEX],pre[SP_MAX_VERTEX];
    bool cv[SP_MAX_VERTEX];
    while(fscanf(fp,"%d %d %d",&fr,&to,&va)!=EOF){
        N[fr].push_back(std::make_pair(va,to));
    }
    std::priority_queue<std::pair<int,int>,std::vector<std::pair<int,int>>,std::greater<std::pair<int,int>>> pq;
    memset(dist,0x3f,sizeof(dist));
    memset(pre,-1,sizeof(pre));
    memset(cv,0,sizeof(cv));
    dist[Start]=0;
    pq.push(std::make_pair(0,Start));
    while(!pq.empty()){
        std::pair<int,int> t = pq.top();
        pq.pop();
        if(cv[t.second]==1)continue;
        cv[t.second] = 1;
        for(int i=0;i<N[t.second].size();i++){
            if(dist[N[t.second][i].second]>dist[t.second]+N[t.second][i].first){
                dist[N[t.second][i].second]=dist[t.second]+N[t.second][i].first;
                pre[N[t.second][i].second]=t.second;
            }
            pq.push(std::make_pair(dist[N[t.second][i].second],N[t.second][i].second));
        }
    }
    Distance=dist[End];
    if(Distance>=0x3f3f3f) return ERROR;
    else{
        int it=End,fl=0;
        while(1){
            pa[fl++]=it;
            if(pre[it]==-1)break;
            it=pre[it];
        }
        for(int i=fl-1;i>=0;i--)Path.push_back(pa[i]);
        return SUCCESS;
    }
    return ERROR;
}