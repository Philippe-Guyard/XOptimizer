#include "graph.hpp"

EdgeWeight Graph::cost_of_path(const std::vector<int>& path) const{
    EdgeWeight cost = 0;
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

    assert( m >= 2 );

    if( m == 2 ){
        return path_vertices;
    }

    int v_initial = path_vertices[0];
    int v_final = path_vertices[m-1];

    std::vector<bool> chosen(m-2, false);


    std::vector<int> min_cost_path;
    min_cost_path.push_back(v_initial);

    EdgeWeight min_cost = -1;

    std::vector<int> path_aux;
    path_aux.push_back(v_initial);

    best_path_brute_force_aux(chosen, path_aux, path_vertices, v_initial, v_final, min_cost, min_cost_path);

    return min_cost_path;
}

void Graph::best_path_brute_force_aux(std::vector<bool> &chosen, std::vector<int> &current_path, const std::vector<int> &path_vertices,
                                    int v_initial, int v_final,
                                    EdgeWeight &min_cost, std::vector<int>& min_cost_path) const{
/**
 * 
 * 
 * 
 */

    int m = chosen.size();

    if( m+1 == current_path.size() ){

        current_path.push_back(v_final);
        EdgeWeight cost = cost_of_path( current_path );

        if(min_cost == -1 || cost < min_cost){
            min_cost_path = current_path;
            min_cost = cost;
        }

        current_path.pop_back();
        
        return;
    }

    for(int i=0; i<m; ++i){
        if( chosen[i] ){
            continue;
        }

        current_path.push_back(path_vertices[i+1]);
        chosen[i] = true;

        best_path_brute_force_aux(chosen, current_path, path_vertices, v_initial, v_final,
                                min_cost, min_cost_path);

        current_path.pop_back();
        chosen[i] = false;

    }
}

std::vector< std::pair<EdgeWeight, EdgeWeight> > Graph::get_euclidean_coordinates(const std::vector<Vertex*> &vertices_to_process) const{

    std::vector< std::pair<EdgeWeight, EdgeWeight> > vertex_coordinates;
    for(const auto &v : vertices_to_process){
        vertex_coordinates.push_back( v->get_eucliean_coordinates() );
    }

    return vertex_coordinates;

}