#include "map.hpp"

std::vector<std::vector<EdgeWeight>> Map::find_distances(){

    //current version works in n^3 time but will be improved to n^2 log(n) using a priority queue

    std::vector<std::vector<EdgeWeight>> distances;
    std::vector<std::vector<bool>> marked;
    distances.resize(num_vertices);
    marked.resize(num_vertices);

    for(int i = 0; i < num_vertices; i++){
        for(int j = 0; j < num_vertices; j++){
            marked[i].push_back(false);
            if(i == j){
                distances[i].push_back(0);
            } 
            else{
                distances[i].push_back(std::numeric_limits<EdgeWeight>::max());
            }
        }
    }

    for(int s = 0; s<num_vertices; s++){
        // select the unmarked vertex with min weight
        int v = -1;
        for(int i = 0; i < num_vertices; i++){
            for (int j = 0; j < num_vertices; j++) {
                if (!marked[s][j] && (v == -1 || distances[s][j] < distances[s][v])){
                    v = j;
                }
            }

            if (distances[s][v] == std::numeric_limits<EdgeWeight>::max()){
                break;
            }

            marked[s][v] = true;

            for(Edge* ptr_edge: adjacency_list[s]){
                int to = ptr_edge->get_vertices().second->get_index();
                EdgeWeight length = ptr_edge->get_weight();

                if(distances[s][v] + length < distances[s][to]){
                    distances[s][to] = distances[s][v] + length;
                }
            }
        }
    }

    return distances;

    }


std::vector<std::vector<EdgeWeight>> Map::find_distances(std::vector<int> start_nodes){

    std::vector<std::vector<EdgeWeight>> distances;
    std::vector<std::vector<bool>> marked;
    int n = start_nodes.size();
    distances.resize(n);
    marked.resize(n);

    for(int i = 0; i < n; i++){
        for(int j = 0; j < num_vertices; j++){
            marked[i].push_back(false);
            if(start_nodes[i] == j){
                distances[i].push_back(0);
            } 
            else{
                distances[i].push_back(std::numeric_limits<EdgeWeight>::max());
            }
        }
    }

    for(int k = 0; k<n; k++){
        int s = start_nodes[k];

        int v = -1;
        for(int i = 0; i < num_vertices; i++){

            // select the unmarked vertex with min weight
            for (int j = 0; j < num_vertices; j++) {
                if (!marked[s][j] && (v == -1 || distances[s][j] < distances[s][v])){
                    v = j;
                }
            }
            if (distances[s][v] == std::numeric_limits<EdgeWeight>::max()){
                break;
            }

            marked[s][v] = true;

            for(Edge* ptr_edge: adjacency_list[s]){
                int to = ptr_edge->get_vertices().second->get_index();
                EdgeWeight length = ptr_edge->get_weight();

                if(distances[s][v] + length < distances[s][to]){
                    distances[s][to] = distances[s][v] + length;
                }
            }
        }
    }

    return distances;

    }