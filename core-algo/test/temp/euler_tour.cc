// Copyright (c) 2021 XOptimzer Team.
// All rights reserved.

// Standard libraries
#include <utility>                  // std::pair, std::make_pair
#include <random>                   // std::mt19937_64, std::bernoulli_distribution
#include <chrono>                   // std::chrono::system_clock::now().time_since_epoch().count()

// External libraries
#include "gtest/gtest.h"

// Main files to be tested
#include "random_graph.hpp"

namespace
{
    const int NUMBER_OF_TEST = 20;
    std::mt19937_64 rng(std::chrono::system_clock::now().time_since_epoch().count());
    std::bernoulli_distribution random_bit(0.5);

    TEST(EulerianCycle, EulerianCycle)
    {
        for (int test = 0; test < NUMBER_OF_TEST; test++)
        {
            int number_of_vertices = rng() % 5000 + 3;
            number_of_vertices = 10;
            EdgeWeight weight_limit = 6000.0;
            double density = 1.0;
            long long seed = rng();

            RandomGraph random_graph = RandomGraph();
            if (random_bit(rng))
            {
                random_graph.random_graph_with_eulerian_circuits(
                    number_of_vertices,
                    weight_limit,
                    density,
                    seed);
                
            }
            else
            {
                random_graph.random_graph(
                    number_of_vertices,
                    weight_limit,
                    density,
                    seed);
            }
        }
    }
}