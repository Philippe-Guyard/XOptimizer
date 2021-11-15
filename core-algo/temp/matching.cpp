#include "graph.hpp"
#include "../lib/blossom5-v2_05/PerfectMatching.h"

std::pair<int,int> Graph::perfect_mincost_matching(std::vector<Vertex*> vertices){


    //in progress
    int n_vertices = vertices.size();
    int n_edges = (n_vertices*(n_vertices-1))/2;
    PerfectMatching *pm = new PerfectMatching(n_vertices, n_edges);
    for(Vertex* v : vertices){
        pm->AddEdge(edges[2*e], edges[2*e+1], weights[e]);
    }
    return std::make_pair(0,0);
}