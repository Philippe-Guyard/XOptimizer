// Copyright (c) 2021 XOptimzer Team.
// All rights reserved.

// Standard libraries
#include <utility>   // std::pair, std::make_pair
#include <chrono>    // std::chrono::system_clock::now().time_since_epoch().count()
#include <random>    // std::mt19937_64
#include <vector>    // std::vector
#include <limits>    // std::numeric_limits
#include <stdexcept> // std::invalid_argument
#include <algorithm> // std::min
#include <iostream>
#include <assert.h>

// External libraries
#include "random_map.hpp"

/**
 * Initialize a random map, with given number of vertices and weight limit for the edges.
 *
 * @param {int}         number_of_vertices  : Number of vertices.
 * @param {EdgeWeight}  weight_limit        : Upper limit for ranom weight. The lower bound is set by default to 0. Default set to be 6000.0
 * @param {int}         seed                : Seed fed into random number generator. Default set to be the EPOCH time at runtime.
 */
RandomMap::RandomMap(int number_of_vertices,
                     EdgeWeight weight_limit,
                     int seed = -1)
{
    if (weight_limit < 0)
    {
        weight_limit = 1;
    }
    // Seeding the random number generator
    if (seed == -1)
    {
        seed = std::chrono::system_clock::now().time_since_epoch().count();
    }
    std::mt19937_64 rng(seed);
    std::uniform_real_distribution<long double> random_weight(0.0, weight_limit);

    // Set number of vertices
    random_num_vertices = number_of_vertices;

    // Generate random edges
    random_edge_weights.resize(number_of_vertices);
    for (int u = 0; u < number_of_vertices; u++)
    {
        random_edge_weights[u].resize(number_of_vertices);
    }
    for (int u = 0; u < number_of_vertices; u++)
    {
        for (int v = 0; v < u; v++)
        {
            EdgeWeight weight = random_weight(rng);
            random_edge_weights[u][v] = {v, weight};
            random_edge_weights[v][u] = {u, weight};
        }
        random_edge_weights[u][u] = {u, 0};
    }

    random_shortest_paths.resize(number_of_vertices);
    for (int u = 0; u < number_of_vertices; u++)
    {
        random_shortest_paths[u].resize(number_of_vertices);
        for (int v = 0; v < number_of_vertices; v++)
        {
            random_shortest_paths[u][v] = random_edge_weights[u][v].second;
        }
    }
    for (int w = 0; w < number_of_vertices; w++)
    {
        for (int u = 0; u < number_of_vertices; u++)
        {
            for (int v = 0; v < number_of_vertices; v++)
            {
                random_shortest_paths[u][v] = std::min(random_shortest_paths[u][v], random_shortest_paths[u][w] + random_shortest_paths[w][v]);
            }
        }
    }
}

EdgeWeight RandomMap ::random_shortest_path(int i, int j)
{
    return random_shortest_paths[i][j];
}