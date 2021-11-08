#include<iostream>
#include<unordered_map>
#include<vector>
#include<cstdio>
#include<assert.h>

#include "graph.hpp"

// Graph Class Implementation

Graph::Graph(int num_vertices, VertexData* vertex_data_array, std::vector<std::vector<EdgeWeight>> distances){

    /*
        Remarks:
            It is ignoring the possibility that some vertices are equivalent (as vertices in the same location).

    */


   //Probably better code:
   //TODO:  for() add_vertex();


    this->num_vertices = num_vertices;
    for(int i=0; i<num_vertices; ++i){
        vertices.push_back(Vertex(vertex_data_array[i], i));
    }

    // Resizing adjacency_list
    adjacency_list.resize(num_vertices);
    for(int i=0; i<num_vertices; ++i){ adjacency_list[i].resize(num_vertices); }

    // we are ignoring the edge that goes from i to i
    for(int i=0; i<num_vertices; ++i){
        for(int j=i+1; j<num_vertices; ++j){

            // Passing vertices by address
            Edge* new_edge_ptr = new Edge(std::make_pair(&vertices[i], &vertices[j]), distances[i][j]);

            // Passing edge by reference
            edges.push_back(*new_edge_ptr); 

            adjacency_list[i][j] = adjacency_list[j][i] = new_edge_ptr;
        }
    }

    //unordered_map construction
    for(int i=0; i<num_vertices; ++i){
        vertex_position[vertex_data_array[i]] = i;
    }
}

void Graph::add_vertex(VertexData& data, std::vector<std::pair<VertexData, EdgeWeight>>& distances){

    // It is necessary to try to update the vertex before just adding it
    // e.g. repeated vertices


    /*== Maybe unecessary ==*/
    if( vertex_position.count(data) ){
        // repeated vertex
        this->update_vertex_data(data);
        return;
    }

    // Main code

    Vertex *new_vertex = new Vertex(data, num_vertices);
    
    vertices.push_back(*new_vertex);

    adjacency_list.emplace_back();
    adjacency_list[num_vertices].resize(num_vertices);

    for(int i=0; i<num_vertices; ++i){
        int j = vertex_position[ distances[i].first ];
        Edge *new_edge = new Edge( std::make_pair(new_vertex, &vertices[j]), distances[i].second );

        adjacency_list[j].push_back(new_edge);
        adjacency_list[num_vertices][j] = new_edge;

        edges.push_back(*new_edge);
    }

    vertex_position[data] = num_vertices;
    num_vertices++;
}

void Graph::delete_vertex(VertexData& data){

    // prevent deletion of vertices that don't exist
    assert( vertex_position.count(data) );

    int pos = vertex_position[data];
    Vertex *vertex_to_delete = &vertices[ vertex_position[data] ];
    Vertex *aux_vertex = &vertices[ num_vertices-1 ];

    // swap vertex at positions (pos, num_vertices-1)

    aux_vertex->set_index(pos);
    vertices[pos] = *aux_vertex;

    //fixing adjacency list

    std::vector<Edge*> edges_to_delete;

    for(int i=0; i<num_vertices; ++i){
        edges_to_delete.push_back(adjacency_list[i][pos]);

        adjacency_list[i][pos] = adjacency_list[i][num_vertices-1];
        adjacency_list[pos][i] = adjacency_list[num_vertices-1][i];
    }

    adjacency_list[pos][pos] = adjacency_list[num_vertices-1][num_vertices-1];
    
    adjacency_list.pop_back();
    for(int i=0; i<num_vertices-1; ++i){
        adjacency_list[i].pop_back();
    }

    // delete edges that have this vertex;
    for(auto edge_to_delete : edges_to_delete){
        
    }

    


    num_vertices--;
}