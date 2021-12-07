#include "graph.hpp"

std::vector< std::vector<int> >Graph::cluster_vertices(const std::vector<int> &vertices_to_cluster, int num_clusters){

    ArrayVec3 vertex_coordinates;

    for(auto index : vertices_to_cluster){
        vertex_coordinates.push_back( vertices[index]->get_euclidean_coordinates() );
    }

    
    std::vector< std::vector<int> > clusters = vertex_coordinates.k_means(num_clusters);

    return clusters;

}