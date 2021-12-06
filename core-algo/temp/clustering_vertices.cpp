#include<iostream>
#include<algorithm>
#include<unordered_map>
#include<unordered_set>
#include<stack>

#include<vector>
#include<cstdio>
#include<assert.h>

#include "graph.hpp"
#include "Vec3_temp.cpp"

std::vector< std::vector<int> >Graph::cluster_vertices(const std::vector<int> &vertices_to_cluster, int num_clusters){

    ArrayVec3 vertex_coordinates;

    for(auto index : vertices_to_cluster){
        vertex_coordinates.push_back( vertices[index]->get_eucliean_coordinates() );
    }

    
    std::vector< std::vector<int> > clusters = vertex_coordinates.k_means(num_clusters);

    return clusters;

}