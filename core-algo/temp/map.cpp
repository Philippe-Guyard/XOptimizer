#include "map.hpp"
#include "../src/graph.hpp"

Map::Map(int num_vertices, VertexData* vertex_data_array, std::vector<std::vector<std::pair<int, EdgeWeight>>> adjacency_list){

    // we assume that the graph is undirected
    this->num_vertices = num_vertices;
    this->num_edges = 0;

    this->edge_weights.resize(num_vertices);

    for(int i=0; i<num_vertices; ++i){
        this->vertices.push_back(new Vertex(vertex_data_array[i], i));
        this->adjacency_list.push_back({});
    }

    //unordered_map construction
    for(int i=0; i<num_vertices; ++i){
        vertex_position[vertex_data_array[i]] = i;
    }

    
    int vertex_ind;
    EdgeWeight edge_weight;
    for(int i = 0; i<num_vertices; ++i){
        for(int j = 0; j<adjacency_list[i].size(); ++j){

            // Passing vertices by address
            vertex_ind = adjacency_list[i][j].first;
            edge_weight = adjacency_list[i][j].second;
            Edge* new_edge_ptr = new Edge(std::make_pair(vertices[i], vertices[vertex_ind]), edge_weight, this->num_edges);

            // saving edge pointers
            edges.push_back(new_edge_ptr);
            this->num_edges++;

            this->adjacency_list[i].push_back(new_edge_ptr);
            this->edge_weights[i][vertex_data_array[j]] = edge_weight;
            
        }
    }

}