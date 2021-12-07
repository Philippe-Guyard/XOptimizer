#include<iostream>
#include<unordered_map>
#include<vector>
#include<cstdio>

#include"disjointset.hpp"
#include"graph.hpp"

std::vector<Edge*> Graph::min_spanning(){

    this->sort_edges();

    std::vector<Edge*> out;

    DisjointSet set = DisjointSet(num_vertices);

    int index = 0;
    int x, y;
    Edge* next;
    std::pair<Vertex*, Vertex*> source_dest;

    while (out.size() != num_vertices - 1){
        next = edges[index++];
        source_dest = next->get_vertices();
        x = set.find(source_dest.first->get_index());
        y = set.find(source_dest.second->get_index());
        if (x != y){
            out.push_back(next);
            set.Union(x, y);
        }
    }

    return out;
};

std::vector<Edge*> Graph::min_spanning(const std::vector<int> &vertices_in_tree){

    int n = vertices_in_tree.size();

    sort_edges();

    std::vector<Edge*> mst;

    std::vector<bool> inside_tree(n);
    for(auto& v : vertices_in_tree){
        inside_tree[v] = true;
    }

    DisjointSet union_find_object = DisjointSet(num_vertices);

    int index = 0;
    int x, y;
    Edge* edge_to_process;
    std::pair<Vertex*, Vertex*> vertices_in_edge;

    while (mst.size() < n-1){
        edge_to_process = edges[index++];
        vertices_in_edge = edge_to_process->get_vertices();

        x = vertices_in_edge.first->get_index();
        y = vertices_in_edge.second->get_index();

        if( (!inside_tree[x]) || (!inside_tree[y]) ){
            continue;
        }

        x = union_find_object.find(x);
        y = union_find_object.find(y);

        if( x!=y ){
            mst.push_back(edge_to_process);
            union_find_object.Union(x,y);
        }

    }

    return mst;

}