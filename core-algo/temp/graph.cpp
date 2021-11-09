#include<iostream>
#include<unordered_map>
#include<vector>
#include<cstdio>
#include<assert.h>

#include "graph.hpp"

// Graph Class Implementation

Graph::Graph(){
    num_vertices = 0;
    num_edges = 0;

    // Add default constructor to vertex_position
}

Graph::Graph(int num_vertices, VertexData* vertex_data_array, std::vector<std::vector<EdgeWeight>> distances){

    /*
        Remarks:
            It is ignoring the possibility that some vertices are equivalent (as vertices in the same location).

    */


   //Probably better code:
   //TODO:  for() add_vertex();


    this->num_vertices = num_vertices;
    num_edges = 0;

    for(int i=0; i<num_vertices; ++i){
        vertices.push_back(Vertex(vertex_data_array[i], i));
    }

    // Resizing adjacency_list
    adjacency_list.resize(num_vertices);
    for(int i=0; i<num_vertices; ++i){
        adjacency_list[i].resize(num_vertices);
    }

    // we are ignoring the edge that goes from i to i
    for(int i=0; i<num_vertices; ++i){
        for(int j=i+1; j<num_vertices; ++j){

            // Passing vertices by address
            Edge* new_edge_ptr = new Edge(std::make_pair(&vertices[i], &vertices[j]), distances[i][j], num_edges);

            // Passing edge by reference
            edges.push_back(*new_edge_ptr); 
            num_edges++;

            adjacency_list[i][j] = adjacency_list[j][i] = new_edge_ptr;
        }
    }

    //unordered_map construction
    for(int i=0; i<num_vertices; ++i){
        vertex_position[vertex_data_array[i]] = i;
    }
}

void Graph::add_vertex(VertexData& data, std::vector<std::pair<VertexData, EdgeWeight>>& distances){

/**
 * Adds a vertex to the graph with the corresponding edges.
 * 
 * PARAMETERS:
 * VertexData& data :
 * The data that should be stored in the vertex.
 * 
 * 
 * std::vector<std::pair<VertexData, EdgeWeight>>& distances : 
 * Contains the distances from this new vertex to all vertices already in the graph. The structure of pair<VertexData, EdgeWeight>
 * means distances[i].second is the distance of the new vertex to the vertex with data distances[i].first
 * 
 *  
 * RETURN:
 * void
 * 
 */

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
        Edge *new_edge = new Edge(std::make_pair(new_vertex, &vertices[j]), distances[i].second, num_edges);

        adjacency_list[j].push_back(new_edge);
        adjacency_list[num_vertices][j] = new_edge;

        edges.push_back(*new_edge);
        num_edges++;
    }

    vertex_position[data] = num_vertices;
    num_vertices++;
}


void Graph::swap_vertex_indices(int pos1, int pos2){

/**
 * Swap the indices of the vertices vertices[pos1] and vertices[pos2] and the corresponding graph structure.
 * 
 * PARAMETERS:
 * int pos1
 * 
 * int pos2
 * 
 * RETURN:
 * void
 * 
 */

    if(pos1==pos2) return;

    Vertex *vertex_1 = &vertices[pos1];
    Vertex *vertex_2 = &vertices[pos2];

    vertex_1->set_index(pos2);
    vertex_2->set_index(pos1);

    vertices[pos1] = *vertex_2;
    vertices[pos2] = *vertex_1;

    // Fixing adjacency list

    for(int i=0; i<num_vertices; ++i){

        if(i==pos1 || i==pos2) continue;

        Edge *edge1 = adjacency_list[i][pos1];
        Edge *edge2 = adjacency_list[i][pos2];

        adjacency_list[i][pos1] = adjacency_list[pos1][i] = edge2;
        adjacency_list[i][pos2] = adjacency_list[pos2][i] = edge1;

    }
}

void Graph::swap_vertex_to_last(int pos){
    /**
     * Swaps vertex vertices[pos] with the vertex in the last position of vertices.
     * 
     * PARAMETERS:
     * int pos
     * 
     * RETURN:
     * void
     */
    swap_vertex_indices(pos, num_vertices-1);
}

void Graph::delete_vertex(VertexData& data){

    /**
     * Deletes the vertex that carries the data given as parameter. Also delete the edges connected to this vertex and
     * mantains the graph structure.
     * 
     * PARAMETERS:
     * VertexData& data :
     * Data that specifies which vertex will be deleted.
     * 
     * RETURN:
     * void
     * 
     */

    // prevent deletion of vertices that don't exist
    assert( vertex_position.count(data) );

    int pos = vertex_position[data];
    swap_vertex_to_last(pos);

    std::vector<Edge*> edges_to_delete;

    // Fixing adjacency_list

    adjacency_list.pop_back();

    for(int i=0; i<num_vertices-1; ++i){
        edges_to_delete.push_back(adjacency_list[i][num_vertices-1]);
        adjacency_list[i].pop_back();
    }

    // removing the edges from edges

    for(int i=0; i<edges_to_delete.size(); ++i){

        Edge *edge_to_delete = edges_to_delete[i];
        int position_edge_to_delete = edge_to_delete->get_index();

        std::swap(edges[position_edge_to_delete], edges[num_edges-edges_to_delete.size()+i]);
    }
    
    for(int i=0; i<edges_to_delete.size(); ++i){
        edges.pop_back();
    }

    for(int i=0; i<edges_to_delete.size(); ++i){
        Edge *edge_to_delete = edges_to_delete[edges_to_delete.size()-1];
    
        edges_to_delete.pop_back();

        delete edge_to_delete;
    }

    num_edges -= edges_to_delete.size();
    num_vertices--;

}