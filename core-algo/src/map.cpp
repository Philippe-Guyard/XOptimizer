#include "map.hpp"

Map::Map(int num_vertices, VertexData* vertex_data_array, std::vector<std::vector<std::pair<int, EdgeWeight>>> adjacency_list){

    // we assume that the graph is undirected
    this->num_vertices = num_vertices;
    this->num_edges = 0;

    // sort the vertex data array by geolocations 
    // std::sort(vertex_data_array, vertex_data_array + num_vertices, [](VertexData* ptr1, VertexData* ptr2) {return ptr1->get_geolocation() < ptr2->get_geolocation();});

    // create unordered maps for every vertex for O(1) access to weights
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
    int position;
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
            position = vertex_position[vertex_data_array[j]];
            this->edge_weights[i][position] = edge_weight;
            
        }
    }

}

Map::~Map(){

/**
 * Default Destructor
 * 
 */

    adjacency_list.clear();

    while( edges.size() > 0 ){
        Edge* edge_to_delete = edges.back();
        edges.pop_back();

        delete edge_to_delete;
    }

    while( vertices.size() > 0 ){
        Vertex* vertex_to_delete = vertices.back();
        vertices.pop_back();

        delete vertex_to_delete;
    }

}

EdgeWeight Map::get_edge_weight(int i, int j){

    if (this->edge_weights[i].count(j)){
        return this->edge_weights[i][j];
    }
    return std::numeric_limits<EdgeWeight>::max();
}

EdgeWeight Map::get_edge_weight(int i, Vertex* v2){

    int j = v2->get_index();
    if (this->edge_weights[i].count(j)){
        return this->edge_weights[i][j];
    }
    return std::numeric_limits<EdgeWeight>::max();
}

EdgeWeight Map::get_edge_weight(Vertex* v1, int j){

    int i = v1->get_index();
    if (this->edge_weights[i].count(j)){
        return this->edge_weights[i][j];
    }
    return std::numeric_limits<EdgeWeight>::max();
}

EdgeWeight Map::get_edge_weight(Vertex* v1, Vertex* v2){

    int i = v1->get_index();
    int j = v2->get_index();
    if (this->edge_weights[i].count(j)){
        return this->edge_weights[i][j];
    }
    return std::numeric_limits<EdgeWeight>::max();
}