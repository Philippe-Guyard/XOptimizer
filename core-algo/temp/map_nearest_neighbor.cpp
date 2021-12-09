#include "map.hpp"

int Map::brute_force_closest_vertex_index(VertexData& vertex_data){

    double distance;
    double min_distance = vertex_data.get_distance(vertices[0]->get_data());;
    int min_index = 0;
    for(int i = 1; i<this->num_vertices; ++i){
        distance = vertex_data.get_distance(vertices[i]->get_data());
        if (distance < min_distance){
            min_distance = distance;
            min_index = i;
        }
    }
    return min_index;
}