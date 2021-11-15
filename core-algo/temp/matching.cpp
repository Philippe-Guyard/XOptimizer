#include "graph.hpp"
#include "../lib/blossom5-v2_05/PerfectMatching.h"

std::vector<std::pair<int,int>> Graph::perfect_mincost_matching(std::vector<Vertex*> vertices){


    int n_vertices = vertices.size();
    int n_edges = (n_vertices*(n_vertices-1))/2;
    
    // we are going to number the vertices 0,1,2....,n-1 based on the order they appear in vertices
    //int vertex_to_index[this->num_vertices];
    int index_to_vertex[n_vertices];

    for(int i = 0; i<n_vertices; i++){
        index_to_vertex[i] = vertices[i]->get_index();
        //vertex_to_index[vertices[i]->get_index()] = i;
    }

    int vertex_i, vertex_j;
    PerfectMatching *pm = new PerfectMatching(n_vertices, n_edges);
    struct PerfectMatching::Options options;

    for(int i = 0; i<n_vertices; i++){
        for(int j = i+1; j<n_vertices; j++){
            vertex_i = index_to_vertex[i];
            vertex_j = index_to_vertex[j];
            pm->AddEdge(i,j,this->adjacency_list[vertex_i][vertex_j]->get_weight());
        }
    }

    pm->options = options;
    pm->Solve();

    std::vector<std::pair<int,int>> solution;
    int index1, index2;
    int v_index1, v_index2;
    for(index1 = 0; index1<n_vertices; index1++){
        index2 = pm->GetMatch(index1);
        if(index1 > index2){
            v_index1 = index_to_vertex[index1];
            v_index2 = index_to_vertex[index2];
            solution.push_back(std::make_pair(v_index1, v_index2));
        }
    }

    delete pm;
    
    return solution;
}