// Copyright (c) 2021 XOptimzer Team.
// All rights reserved.

// Standard libraries
#include <utility>                  // std::pair, std::make_pair
#include <random>                   // std::mt19937_64
#include <chrono>                   // std::chrono::system_clock::now().time_since_epoch().count()
#include <iostream>

// External libraries
#include "gtest/gtest.h"

// Main files to be tested
#include "random_graph.hpp"

#define EXPECT_IN_RANGE(VAL, MIN, MAX) \
    EXPECT_GE((VAL), (MIN));           \
    EXPECT_LE((VAL), (MAX))

namespace
{
    const int NUMBER_OF_TEST = 20;
    std::mt19937_64 rng(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_real_distribution<double> random_density(0.0, 1.0);

    TEST(TSP, Christofides)
    {
        for (int i = 0; i < NUMBER_OF_TEST; i++)
        {
            int number_of_vertices = rng() % 1000 + 1;
            EdgeWeight weight_limit = 6000.0;
            long long seed = rng();
            
            RandomGraph random_tsp = RandomGraph();
            EdgeWeight result = 
                random_tsp.random_tsp(
                    number_of_vertices, 
                    weight_limit, 
                    seed, 
                    true);
            
            std::vector<int> tsp_solution = random_tsp.TSP();
            if (number_of_vertices > 1)
            {
                tsp_solution.push_back(tsp_solution[0]);
            }
            EdgeWeight computed = random_tsp.cost_of_path(tsp_solution);

            EXPECT_IN_RANGE(computed, result, result * 1.5)
                << "For number_of_vertices = " 
                << number_of_vertices
                << ", weight_limit = "
                << weight_limit
                << ", seed = "
                << seed
                << ", the expected and computed minimum cost \ndo not follow thereotical result: Expected "
                << result 
                << ", found " 
                << computed 
                << "\n"; 
        }
    }

    TEST(TSP, BruteForce)
    {
        for (int i = 0; i < NUMBER_OF_TEST; i++)
        {
            int number_of_vertices = 10;
            EdgeWeight weight_limit = 6000.0;
            long long seed = rng();
            
            RandomGraph random_tsp = RandomGraph();
            EdgeWeight result = 
                random_tsp.random_tsp(
                    number_of_vertices, 
                    weight_limit, 
                    seed, 
                    true);
            std::vector<int> tsp_solution = random_tsp.TSP_held_karp();
            if (number_of_vertices > 1)
            {
                tsp_solution.push_back(tsp_solution[0]);
            }
            EdgeWeight computed = random_tsp.cost_of_path(tsp_solution);
                
            EXPECT_IN_RANGE(computed, result - 1e-7, result + 1e-7)
                << "For number_of_vertices = " 
                << number_of_vertices
                << ", weight_limit = "
                << weight_limit
                << ", seed = "
                << seed
                << ", the expected and computed minimum cost \ndo not follow thereotical result: Expected "
                << result 
                << ", found " 
                << computed 
                << "\n"; 
        }
    }
}