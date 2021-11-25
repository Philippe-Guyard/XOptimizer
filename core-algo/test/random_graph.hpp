// Copyright (c) 2021 XOptimzer Team.
// All rights reserved.

// Standard libraries

// External libraries
#include "../temp/graph.hpp"

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
};

class RandomTSP : public RandomGraph
{
    public:
        EdgeWeight random_tsp(
            int number_of_vertices,
            EdgeWeight weight_limit,
            int seed, 
            bool symmetric);
};