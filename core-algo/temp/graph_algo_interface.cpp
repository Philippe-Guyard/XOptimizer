#include "graph.hpp"

// Case for one inventory

std::vector<int> Graph::optimal_routing(int inventory_index, std::vector<int> client_indices){
    int m = client_indices.size();

    std::vector<int> to_visit = client_indices;
    to_visit.push_back(inventory_index);
    std::vector<int> path_indices = this->TSP(to_visit);

    int inventory_position;
    for (int i = 0; i <= m; i++){
        if (path_indices[i] == m){
            inventory_position = i;
            break;
        }
    }

    std::vector<int> res;
    for(int i = inventory_position; i <= m; i++){
        res.push_back(path_indices[i]);
    }
    for(int i = 0; i < inventory_position; i++){
        res.push_back(path_indices[i]);
    }

    return res;
}

// Case for multiple inventories

std::vector< std::vector<int> > Graph::optimal_routing(std::vector<int> inventory_indices, std::vector<int> client_indices){
    int m = client_indices.size();
    int n = inventory_indices.size();

    std::vector< std::vector<int> > clusters = this->cluster_vertices(client_indices, n);

    ArrayVec3 inventory_coordinates, cluster_centers;
    for(int i = 0; i < n; i++){
        inventory_coordinates.push_back(vertices[inventory_indices[i]]->get_euclidean_coordinates());
    }

    int cluster_size;
    ArrayVec3 current_cluster;
    for(int i = 0; i < n; i++){
        cluster_size = clusters[i].size();
        for(int j = 0; j < cluster_size; j++){
            current_cluster.push_back(vertices[clusters[i][j]]->get_euclidean_coordinates());
            cluster_centers.push_back(current_cluster.center_of_mass());
            current_cluster.clear();
        }
    }

    std::vector<int> matching = match_function_0(inventory_coordinates, cluster_centers);

    std::vector< std::vector<int> > res;
    for(int i = 0; i < n; i++){
        res.push_back(this->optimal_routing(inventory_indices[i], clusters[matching[i]]));
    }

    return res;
}

