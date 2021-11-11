#include<iostream>
#include<unordered_map>
#include<vector>
#include<cstdio>

#include"disjointset.hpp"
#include"graph.hpp"

bool compare_edges(Edge a, Edge b){
    return a.get_weight() < b.get_weight();
}

std::vector<Edge> Graph::min_spanning(){
    std::vector<Edge> out;
    DisjointSet set = DisjointSet(num_vertices);
    sort(edges.begin(), edges.end(), compare_edges);
    while (out.size() != num_vertices - 1){
        Edge next = edges.back();
        edges.pop_back();
        Vertex* source = next.get_vertices().first;
        Vertex* destination = next.get_vertices().second;
        int x = set.find(source->get_index());
        int y = set.find(destination->get_index());
        if (x != y){
            out.push_back(next);
            set.Union(x, y);
        }
    }
    return out;
};