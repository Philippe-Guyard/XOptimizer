#include "map.hpp"
#include <set>
#include <vector>
#include <iostream>
#include <iomanip>

//TODO: see if the end result is a symmetric matrix for further optimization

std::vector<std::vector<EdgeWeight>> Map::find_distances(std::vector<int> start_nodes){

    std::vector<std::vector<EdgeWeight>> distances;
    int n = start_nodes.size();
    distances.resize(n);

    for(int i = 0; i < n; i++){
        for(int j = 0; j < num_vertices; j++){
            if(i == j){
                distances[i].push_back(0);
            } 
            else{
                distances[i].push_back(std::numeric_limits<EdgeWeight>::max());
            }
        }
    }

    int source;
    int vertex;
    auto compare = [&source, &distances](const int &a, const int &b){
            return distances[source][a] < distances[source][b];
        };
    std::set<int, decltype(compare)> Set(compare);

    for(int k = 0; k<n; k++){

        source = start_nodes[k];

        Set.clear();
        Set.insert(source);

        while(!Set.empty()){
            vertex = *Set.begin();
            Set.erase(Set.begin());
            
            for(Edge* ptr_edge: adjacency_list[vertex]){
                int to = ptr_edge->get_vertices().second->get_index();
                EdgeWeight length = ptr_edge->get_weight();

                if(distances[source][vertex] + length < distances[source][to]){
                    Set.erase(to);
                    distances[source][to] = distances[source][vertex] + length;
                    Set.insert(to);
                }
            }

        }
    }
    return distances;
}

std::vector<std::vector<EdgeWeight>> Map::find_distances(){

    std::vector<std::vector<EdgeWeight>> distances;
    distances.resize(num_vertices);

    for(int i = 0; i < num_vertices; i++){
        for(int j = 0; j < num_vertices; j++){
            if(i == j){
                distances[i].push_back(0);
            } 
            else{
                distances[i].push_back(std::numeric_limits<EdgeWeight>::max());
            }
        }
    }

    int source;
    int vertex;
    auto compare = [&source, &distances](const int &a, const int &b){
            return distances[source][a] < distances[source][b];
        };
    std::set<int, decltype(compare)> Set(compare);

    for(source = 0; source<num_vertices; source++){

        Set.clear();
        Set.insert(source);
        while(!Set.empty()){
            vertex = *Set.begin();
            Set.erase(Set.begin());
            
            for(Edge* ptr_edge: adjacency_list[vertex]){
                int to = ptr_edge->get_vertices().second->get_index();
                EdgeWeight length = ptr_edge->get_weight();

                if(distances[source][vertex] + length < distances[source][to]){
                    Set.erase(to);
                    distances[source][to] = distances[source][vertex] + length;
                    Set.insert(to);
                }
            }

        }
    }
    return distances;
}