#include<iostream>
#include<algorithm>
#include<unordered_map>
#include<unordered_set>

#include<vector>
#include<cstdio>
#include<assert.h>

#include "graph.hpp"

std::vector<int> Graph::euler_tour(const std::vector<Edge*>& smaller_graph) const{

    int n = num_vertices;
    int m = smaller_graph.size();

    std::vector<bool> chosen(m, false);

    

}

std::vector<int> Graph::TSP(){

    std::vector<Edge*> MST = min_spanning();

    int n = num_vertices;

    // Vector with the degrees of vertices in MST
    std::vector<int> deg(n, 0);

    for(auto& e : MST{
        deg[ (e->get_vertices()).first->get_index() ]++;
        deg[ (e->get_vertices()).second->get_index() ]++;
    }

    std::vector<int> odd_degree_vertices;

    for(int i=0; i<n; ++i){
        if( deg[i]%2 == 1 ){
            odd_degree_vertices.push_back(i);
        }
    }

    std::vector< pair<int,int> > min_cost_matching = perfect_mincost_matching(odd_degree_vertices);

    // Tactical renaming
    std::vector<Edge*> &christofidesGraph = MST;


    // I don't really know if this syntax works
    for(auto& [x1, x2] : min_cost_matching){
        christofidesGraph.push_back( adjacency_list[x1][x2] );
    }

    std::vector<int> eulerPath = Euler_path(christofidesGraph);

    std::vector<bool> chosen(n, false);
    std::vector<int> finalPath;

    for(auto& v : eulerPath){
        if( chosen[v] ){
            continue;
        }

        chosen[v] = true;
        finalPath.push_back(v);
    }

    return finalPath;
}