#include<iostream>
#include<algorithm>
#include<unordered_map>
#include<unordered_set>
#include<stack>

#include<vector>
#include<cstdio>
#include<assert.h>

#include "graph.hpp"
#include "kmeans.cpp"

std::vector< std::vector<Vertex*> > Graph::cluster_vertices(const std::vector<Vertex*> &vertices_to_cluster, int num_clusters){

    return k_means(get_euclidean_coordinates(vertices_to_cluster), num_clusters);

}


std::pair< EdgeWeight, EdgeWeight > Graph::find_cluster_center(const std::vector<Vertex*> &cluster){

    std::vector< std::pair<EdgeWeight, EdgeWeight> > vertex_coordinates; 

    std::pair<EdgeWeight, EdgeWeight> mu = {0, 0};

    for(const auto& point : vertex_coordinates){
        mu.first += point.first;
        mu.second += point.second;
    }

    mu.first = (EdgeWeight) mu.first / (EdgeWeight) cluster.size();
    mu.second = (EdgeWeight) mu.second / (EdgeWeight) cluster.size();

    return mu;

}

std::vector< std::pair< EdgeWeight, EdgeWeight > > Graph::find_clusters_centers(const std::vector< std::vector<Vertex*> > &clusters){

    std::vector< std::pair< EdgeWeight, EdgeWeight > > centers;
    for(const auto& cluster : clusters){
        centers.push_back( find_cluster_center(cluster) );
    }

    return centers;
}