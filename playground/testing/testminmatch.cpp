#include "graph.hpp"
#include <iostream>

// THIS CODE DOES NOT BELONG TO THIS FOLDER AND THEY ARE PUSHED HERE J
// JUST TO HAVE THESE WORK COMMITTED TO GITHUB


int main(){

    int n = 6;
    VertexData v[n];
    std::vector<std::vector<EdgeWeight>> distances;
    distances.resize(n);
    for(int i = 0; i<n; i++){
        v[i] = VertexData(std::make_pair(double(i), double(i)));
        distances[i].resize(n);
    }
    for(int i = 0; i<n; i++){
        for(int j = i+1; j<n; j++){
            distances[i][j] = EdgeWeight(10000);
            distances[j][i] = EdgeWeight(10000);    
        }
    }
    std::vector<int> edges = {0,1,0,3,0,4,1,2,1,4,1,5,2,5,3,4,4,5};
    std::vector<EdgeWeight> weights = {3,10,7,-1,5,4,-7,0,4};
    for(int i = 0; i<9; i++){
        distances[edges[2*i]][edges[2*i+1]] = weights[i];
    }

    Graph g = Graph(n, v, distances);
    std::vector<int> vertices = {0,1,2,3,4,5};
    std::vector<std::pair<int,int>> matching = g.perfect_mincost_matching(vertices);

    for(std::pair<int,int> p : matching){
        std::cout << p.first << " " << p.second << std::endl;
    }

    return 0;
}
