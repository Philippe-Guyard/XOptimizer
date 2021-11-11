// Copyright (c) 2021 XOptimzer Team.
// All rights reserved.

// Standard libraries

// External libraries
#include "temp/graph.hpp"

class RandomGraph : public Graph
{
    public:
        void random_graph(
            int number_of_vertices, 
            int seed);
        void random_complete_graph(
            int number_of_vertices, 
            int seed);
}