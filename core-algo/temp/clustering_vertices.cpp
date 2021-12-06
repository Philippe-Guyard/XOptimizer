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


std::pair<double, double> Graph::find_cluster_center(const std::vector<int> &cluster){

    std::vector< std::pair<double, double> > vertex_coordinates; 

    for(auto index : cluster){
        vertex_coordinates.push_back( vertices[index]->get_eucliean_coordinates() );
    }

    std::pair<double, double> mu = {0, 0};

    for(const auto& point : vertex_coordinates){
        mu.first += point.first;
        mu.second += point.second;
    }

    mu.first = mu.first / (double) cluster.size();
    mu.second = mu.second / (double) cluster.size();

    return mu;

}

std::vector< std::pair<double,double> > Graph::find_clusters_centers(const std::vector< std::vector<int> > &clusters){

    std::vector< std::pair< EdgeWeight, EdgeWeight > > centers;
    for(const auto& cluster : clusters){
        centers.push_back( find_cluster_center(cluster) );
    }

    return centers;
}