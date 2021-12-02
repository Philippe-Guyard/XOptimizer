// Copyright (c) 2021 XOptimzer Team.
// All rights reserved.

// Standard libraries
#include <utility>                  // std::pair, std::make_pair
#include <vector>                   // std::vector
#include <limits>                   // std::numeric_limits
#include <queue>                    // std::priority_queue
#include <random>                   // std::mt19937_64
#include <chrono>                   // std::chrono::system_clock::now().time_since_epoch().count()
#include <functional>               // std::greater

// External libraries
#include "gtest/gtest.h"

// Main files to be tested
#include "random_graph.hpp"

namespace
{
    const int NUMBER_OF_TEST = 20;
    std::mt19937_64 rng(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_real_distribution<double> random_density(0.0, 1.0);

    TEST(MinimumSpanningTree, Kruskal)
    {
        for (int i = 0; i < NUMBER_OF_TEST; i++)
        {
            int number_of_vertices = rng() % 1000 + 1;
            EdgeWeight weight_limit = 6000.0;
            double density = random_density(rng);
            long long seed = rng();

            std::pair<EdgeWeight, EdgeWeight> result = 
                RandomGraph()
                    .minimum_spanning_tree_test(
                        number_of_vertices,
                        weight_limit,
                        density,
                        seed);
            
            EXPECT_NEAR(result.first, result.second, 0.00000001)
                << "For number_of_vertices = " 
                << number_of_vertices
                << ", weight_limit = "
                << weight_limit
                << ", density = "
                << density
                << ", seed = "
                << seed
                << ", the expected and computed minimum cost differ.\n"; 
        }
    }
}