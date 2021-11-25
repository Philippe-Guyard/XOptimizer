/*
#include "graph.hpp"

int main(){

    int number_of_vertices = 5;
    
    VertexData locations[5];
    for(int i = 0; i < 5; i++){
        locations[i] = VertexData(std::pair<double, double>{i, i});
    }
    
    std::vector<std::vector<EdgeWeight> > distances;
    
    for(int i = 0; i<5; i++){
        distances.push_back(std::vector<EdgeWeight>());
        for(int j = 0; j<5; j++){
            distances[i].push_back(EdgeWeight(i+j+1));
        }
    }

    Graph graph = Graph(number_of_vertices,
                            locations, 
                            distances);

    std::vector<int> path = graph.TSP_held_karp();
    for(auto i : path){
        std::cout << i << " ";
    }
    std::cout << std::endl;
    return 0;
    
}
*/