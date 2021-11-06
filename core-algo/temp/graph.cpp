#include<iostream>

#include<unordered_map>
#include<vector>
#include<cstdio>

#include "graph.hpp"

/*
For quick reference:

class Graph{
    Graph(VertexData[], std::vector<std::vector<EdgeWeight>> distances);
    Graph();
    void add_vertex(VertexData& data, std::vector<std::pair<VertexData, EdgeWeight>>& distances );
    void delete_vertex(VertexData& data);
    void update_vertex_data(VertexData& data);
    int num_vertices;
    std::vector<Vertex> vertices; 
    std::vector<Edge> edges; 
    std::vector<std::vector<Edge*>> adjacency_list; 
    std::unordered_map<VertexData, int> vertex_position;
};

class Edge{
    private:
        std::pair<Vertex*, Vertex*> vertices;
        EdgeWeight weight;
    public:
        Edge(Vertex &v1, Vertex &v2, EdgeWeight weight);
        Edge();
        void set_weight(EdgeWeight weight);
        void set_vertices(std::pair<Vertex*, Vertex*> pair_vertices);
        std::pair<Vertex*, Vertex*> get_vertices();
        EdgeWeight get_weight();
};

class VertexData{};

class Vertex{
    private:
        int v_index;
        VertexData v_data;
    public:
        Vertex(VertexData v_data, int v_index);
        int get_index();
        VertexData get_data();
};
*/


Graph::Graph(int num_vertices, VertexData* vertex_data_array, std::vector<std::vector<EdgeWeight>> distances){

    /*
        Remarks:
            It is ignoring the possibility that some vertices are equivalent (as vertices in the same location).

    */

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

            // WARNING 1:
            // Passing vertices by reference
            Edge* new_edge_ptr = new Edge(vertices[i], vertices[j], distances[i][j]);

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


void Graph::add_vertex(){}