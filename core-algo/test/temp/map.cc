// Copyright (c) 2021 XOptimzer Team.
// All rights reserved.

// Standard libraries
#include <utility> // std::pair, std::make_pair
#include <vector>  // std::vector
#include <random>  // std::mt19937_64
#include <chrono>  // std::chrono::system_clock::now().time_since_epoch().count()

// External libraries
#include "gtest/gtest.h"

// Main files to be tested
#include "random_map.hpp"

/*
 * Untestable functionalities:
 * - brute_force_closest_vertex_index()
 * - find_distances(std::vector<int>)
 * - find_distances_slow(std::vector<int>)
 * - get_edge_weight(Vertex* v1, Vertex* v2);
 * - get_edge_weight(int i, int j);
 * - get_edge_weight(Vertex* v1, int j);
 * - EdgeWeight get_edge_weight(int i, Vertex* v2);
 */
namespace
{
    const int NUMBER_OF_TESTS = 1;
    std::mt19937_64 rng(std::chrono::system_clock::now().time_since_epoch().count());
    TEST(Map, Map)
    {
        for (int test = 0; test < NUMBER_OF_TESTS; test++)
        {
            int number_of_vertices = rng() % 9 + 2;
            EdgeWeight weight_limit = 6000.0;
            long long seed = rng();

            RandomMap random_map = RandomMap(number_of_vertices,
                                             weight_limit,
                                             seed);
            // dummy vertex data array
            VertexData vertex_data_array[number_of_vertices];
            std::uniform_real_distribution<double> random_coordinate(-180.0, 180.0);
            for (int u = 0; u < number_of_vertices; u++)
            {
                vertex_data_array[u] = VertexData({random_coordinate(rng), random_coordinate(rng)});
            }

            std::cerr << "1\n";
            // Testing constructor
            Map test_map = Map(number_of_vertices, vertex_data_array, random_map.random_edge_weights);

            std::cerr << "2\n";
            // Testing A* shortest paths
            for (int u = 0; u < number_of_vertices; u++)
            {
                for (int v = 0; v < number_of_vertices; v++)
                {
                    EdgeWeight expected_result = random_map.random_shortest_path(u, v),
                               computed_result = test_map.find_distances_astar(u, v);

                    EXPECT_NEAR(expected_result, computed_result, 0.00000001)
                        << "For number_of_vertices = "
                        << number_of_vertices
                        << ", weight_limit = "
                        << weight_limit
                        << ", seed = "
                        << seed
                        << ", the expected and computed shortest path differ.\n";
                }
            }

            std::cerr << "3\n";
            continue;
            // Testing all pair shortest path : find_distances()
            std::vector<std::vector<EdgeWeight>> results = test_map.find_distances();
            for (int u = 0; u < number_of_vertices; u++)
            {
                for (int v = 0; v < number_of_vertices; v++)
                {
                    EdgeWeight expected_result = random_map.random_shortest_path(u, v),
                               computed_result = results[u][v];

                    EXPECT_NEAR(expected_result, computed_result, 0.00000001)
                        << "For number_of_vertices = "
                        << number_of_vertices
                        << ", weight_limit = "
                        << weight_limit
                        << ", seed = "
                        << seed
                        << ", the expected and computed shortest path from find_distances() differ.\n";
                }
            }

            std::cerr << "4\n";
            // Testing all pair shortest path : find_distances_slow()
            results = test_map.find_distances_slow();
            for (int u = 0; u < number_of_vertices; u++)
            {
                for (int v = 0; v < number_of_vertices; v++)
                {
                    EdgeWeight expected_result = random_map.random_shortest_path(u, v),
                               computed_result = results[u][v];

                    EXPECT_NEAR(expected_result, computed_result, 0.00000001)
                        << "For number_of_vertices = "
                        << number_of_vertices
                        << ", weight_limit = "
                        << weight_limit
                        << ", seed = "
                        << seed
                        << ", the expected and computed shortest path from find_distances_slow() differ.\n";
                }
            }
        }
    }
}