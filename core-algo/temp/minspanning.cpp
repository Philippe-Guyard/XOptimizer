#include<iostream>
#include<unordered_map>
#include<vector>
#include<cstdio>

#include"disjointset.hpp"
#include"graph.hpp"

std::vector<Edge> Graph::min_spanning(){
    std::vector<Edge> out;
    DisjointSet set = DisjointSet(num_vertices);
    int index = 0;
    while (out.size() != num_vertices - 1){
        Edge next = edges[index++];
        std::pair<Vertex*, Vertex*> source_dest = next.get_vertices();
        int x = set.find(source_dest.first->get_index());
        int y = set.find(source_dest.second->get_index());
        if (x != y){
            out.push_back(next);
            set.Union(x, y);
        }
    }
    return out;
};