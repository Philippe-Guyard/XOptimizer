// Copyright (c) 2021 XOptimzer Team.
// All rights reserved.

// Standard libraries
#include <utility>                  // std::pair, std::make_pair

// External libraries
#include "../../temp/graph/graph.hpp"

/**
 * Generete random undirected weight.
 */
class RandomGraph : public Graph
{
    public:
        void random_graph(
            int number_of_vertices, 
            EdgeWeight weight_limit, 
            double density, 
            int seed);
        
        std::pair<EdgeWeight, EdgeWeight> minimum_spanning_tree_test(
            int number_of_vertices,
            EdgeWeight weight_limit, 
            double density, 
            int seed);
        
        std::pair<EdgeWeight, EdgeWeight> maximal_mincost_matching_test(
            std::vector<int>& vertex_indices);

        EdgeWeight random_tsp(
            int number_of_vertices,
            EdgeWeight weight_limit,
            int seed, 
            bool symmetric);
        
        void random_graph_with_eulerian_circuits(
            int number_of_vertices, 
            EdgeWeight weight_limit, 
            double density, 
            int seed);
        
        bool eulerian_circuit_check();
};