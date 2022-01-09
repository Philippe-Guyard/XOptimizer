// Copyright (c) 2021 XOptimzer Team.
// All rights reserved.

// Standard libraries
#include <vector>  // std::vector
#include <utility> // std::pair, std::make_pair

// External libraries
#include "../../temp/map/map.hpp"

/**
 * Generate random map
 */
class RandomMap
{
public:
    RandomMap(int number_of_vertices,
              EdgeWeight weight_limit,
              int seed);
    EdgeWeight random_shortest_path(int i, int j);
    std::vector<std::vector<std::pair<int, EdgeWeight>>> random_edge_weights;

protected:
    int random_num_vertices;
    std::vector<std::vector<EdgeWeight>> random_shortest_paths;
};