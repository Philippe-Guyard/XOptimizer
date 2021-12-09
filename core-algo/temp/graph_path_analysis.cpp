#include "graph.hpp"
#include "graph_algorithms.hpp"

double Graph::cost_of_path(const std::vector<int>& path) const{
    double cost = 0;
    for(int i=1; i<path.size(); ++i){
        cost += get_edge_weight(path[i-1], path[i]);
    }
    
    return cost;
}

std::vector<int> Graph::best_path_brute_force(const std::vector<int>& path_vertices) const{
/**
 * Find the min cost path that goes through the vertices in path_vertices while mantaining the first and last vertices fixed.
 *
 * Example: path_vertices = {v1, v2, v3, v4, v5}, it returns the minimum cost path that starts in v1, passes through v2,v3,v4 in some
 * order, and ends in v5.
 * 
 * Warning: Takes exponential time in the size of path_vertices.
 * 
 */

    int m = path_vertices.size();

    // If the input is too big or too small, it doesn't change the path
    if( m <= 2 || m >=10 ){
        return path_vertices;
    }

    return graph_algorithms::best_path_brute_force(
        this->build_adjacency_matrix(),
        path_vertices
        );

}