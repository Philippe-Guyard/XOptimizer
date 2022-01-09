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
            distances[i][j] = EdgeWeight(i-j+10);
            distances[j][i] = EdgeWeight(i-j+10);    
        }
    }

    Graph g = Graph(n, v, distances);
    g.sort_edges();
    return 0;



}