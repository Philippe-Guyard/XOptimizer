// Copyright (c) 2021 XOptimzer Team.
// All rights reserved.

// Standard libraries
#include <utility>                  // std::pair, std::make_pair
#include <vector>                   // std::vector
#include <random>                   // std::mt19937_64
#include <chrono>                   // std::chrono::system_clock::now().time_since_epoch().count()

// External libraries
#include "gtest/gtest.h"

// Main files to be tested
#include "random_graph.hpp"

namespace
{
    const int NUMBER_OF_TEST = 1;
    std::mt19937_64 rng(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_real_distribution<double> random_density(0.0, 1.0);

    TEST(PerfectMincostMatching, BlossomV)
    {
        for (int i = 0; i < NUMBER_OF_TEST; i++)
        {
            int number_of_vertices = rng() % 5000 + 3;
            number_of_vertices = 10;
            EdgeWeight weight_limit = 6000.0;
            double density = 1.0;
            long long seed = rng();

            RandomGraph graph = RandomGraph();
            graph.random_graph(number_of_vertices,
                            weight_limit,
                            density,
                            seed);

            std::vector<int> vertex_indices;
            for (int i = 0; i < number_of_vertices - 1; i++)
            {
                if (rng() & 1)
                {
                    vertex_indices.push_back(i);
                }
            }
            if (vertex_indices.size() & 1)
            {
                vertex_indices.push_back(number_of_vertices - 1);
            }

            std::pair<EdgeWeight, EdgeWeight> result = 
                graph.maximal_mincost_matching_test(vertex_indices);

            EXPECT_EQ(result.first, result.second)
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