// Copyright (c) 2021 XOptimzer Team.
// All rights reserved.

// Standard libraries

// External libraries
#include "../temp/graph.hpp"

class RandomGraph : public Graph
{
    public:
        void random_graph(
            int number_of_vertices, 
            double weight_limit, 
            double density, 
            int seed);
};