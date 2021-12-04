#include "graph.hpp"

std::vector<int> Graph::TSP_held_karp(){
    std::vector<int> path;
    std::pair<EdgeWeight, int> min_costs[1<<num_vertices][num_vertices];

    for(int i = 1; i<num_vertices; ++i){
        min_costs[0][i] = std::make_pair(get_edge_weight(0,i), 0);
    }
    for(int i = 1; i<(1<<num_vertices); i++){
        for(int j = 1; j<num_vertices; j++){
            min_costs[i][j] = std::make_pair(std::numeric_limits<EdgeWeight>::max(), -1);
            for(int k = 1; k<num_vertices; k++){
                if(i&(1<<k)){
                    min_costs[i][j].first = std::min(min_costs[i][j].first, min_costs[i-(1<<k)][k].first+get_edge_weight(k,j));
                    min_costs[i][j].second = k;
                }
            }
        }   
    }
    int minind = 1;
    EdgeWeight mincost = std::numeric_limits<EdgeWeight>::max();
    for(int i = 1; i<num_vertices; i++){
        if(min_costs[(1<<num_vertices)-1-(1<<i)][i].first + get_edge_weight(i,0)<mincost){
            mincost = min_costs[(1<<num_vertices)-1-(1<<i)][i].first;
            minind = i;
        }
    }
    int curr = minind;
    int i = (1<<num_vertices)-1-(1<<minind);
    path.push_back(0);
    path.push_back(minind);
    while(path.size() != num_vertices){
        path.push_back(min_costs[i][curr].second);
        curr = min_costs[i][curr].second;
        i -= (1<<curr);
    }
    return path;
}