// Copyright (c) 2021 XOptimzer Team.
// All rights reserved.

// Standard libraries

// External libraries
#include "../src/graph.hpp"

using EdgeWeight = long double;

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