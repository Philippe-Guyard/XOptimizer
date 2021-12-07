#include "graph.hpp"



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



std::vector<int> Graph::optimal_routing(std::vector<int> inventory_indices, std::vector<int> client_indices){return std::vector<int>();}












