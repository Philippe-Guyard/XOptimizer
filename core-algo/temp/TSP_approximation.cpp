#include<iostream>
#include<algorithm>
#include<unordered_map>
#include<unordered_set>
#include<stack>

#include<vector>
#include<cstdio>
#include<assert.h>

#include "graph.hpp"
#include "graph_algorithms_temp.cpp"

std::vector<int> Graph::euler_tour(const std::vector<Edge*>& edges_subgraph)    const{

    int n = num_vertices;

    std::vector<std::vector<int>> subgraph_adjacency_list(n);

    for(const auto &e : edges_subgraph){
        int x1 = (e->get_vertices()).first->get_index();
        int x2 = (e->get_vertices()).second->get_index();

        subgraph_adjacency_list[x1].push_back(x2);
        subgraph_adjacency_list[x2].push_back(x1);
    }

    return graph_algorithms::euler_tour( subgraph_adjacency_list );
}

// TSP Functions

std::vector<int> Graph::shortcut_path(const std::vector<int> &path) const{

    std::vector<bool> chosen(num_vertices, false);
    std::vector<int> final_path;

    for(const auto& v : path){
        if( chosen[v] ){
            continue;
        }

        chosen[v] = true;
        final_path.push_back(v);
    }

    return final_path;

}

std::vector<int> Graph::TSP(){

    std::vector<int> vertices_in_tour;

    for(int i=0; i < num_vertices; ++i){
        vertices_in_tour.push_back(i);
    }

    return TSP(vertices_in_tour);

}


// For the multiple inventories case
std::vector<int> Graph::TSP(std::vector<int> &vertices_in_tour){


    std::vector<Edge*> MST = min_spanning(vertices_in_tour);
    
    int n = num_vertices;

    // Vector with the degrees of vertices in MST
    std::vector<int> deg(n, 0);

    for(const auto &e : MST){
        deg[ (e->get_vertices()).first->get_index() ]++;
        deg[ (e->get_vertices()).second->get_index() ]++;
    }

    // We get the vertices with odd degrees
    std::vector<int> odd_degree_vertices;

    for(int i=0; i<n; ++i){
        if( deg[i]%2 == 1 ){
            odd_degree_vertices.push_back(i);
        }
    }

    std::vector< std::pair<int,int> > min_cost_matching = perfect_mincost_matching(odd_degree_vertices);

    // Tactical renaming
    std::vector<Edge*> &christofides_graph = MST;

    for(const auto &match : min_cost_matching){
        christofides_graph.push_back( adjacency_list[match.first][match.second] );
    }

    std::vector<int> christofides_euler_path = euler_tour(christofides_graph);

    return shortcut_path(christofides_euler_path);
}



std::vector<int> Graph::TSP(const std::vector<Vertex*> &vertices_in_tour){
    
    std::vector<int> indices_in_tour;
    for(auto& v : vertices_in_tour){
        indices_in_tour.push_back(v->get_index());
    }

    return TSP(indices_in_tour);

}