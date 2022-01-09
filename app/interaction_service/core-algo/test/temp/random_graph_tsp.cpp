// Copyright (c) 2021 XOptimzer Team.
// All rights reserved.

// Standard libraries
#include <utility>                  // std::pair, std::make_pair
#include <chrono>                   // std::chrono::system_clock::now().time_since_epoch().count()
#include <random>                   // std::mt19937_64
#include <algorithm>                // std::random_shuffle, std::min
#include <vector>                   // std::vector
#include <limits>                   // std::numeric_limits
#include <queue>                    // std::priority_queue
#include <stdexcept>                // std::invalid_argument
#include <iostream>
#include <assert.h>

// External libraries
#include "random_graph.hpp"

/**
 * Initialize to a random undirected weighted graph, with given density, weight limit and known solution to Travelling Salesman Problem.
 * This is implemented based on:
 * Generating Travelling-Salesman Problems with Known Optimal Tours, 
 * Jeffrey L. Arthur and James O. Frendewey, 
 * Journal of the Operational Research Society, 39, 153-159 (1988).
 * 
 * @param {int}         number_of_vertices  : Number of vertices.
 * @param {EdgeWeight}  weight_limit        : Upper limit for ranom weight. The lower bound is set by default to 0. Default set to be 6000.0
 * @param {double}      density             : Density of random graph from 0 to 1, e.g. 0 corresponds to a tree, and 1 corresponds to complete graph. Default set to be 0.5
 * @param {int}         seed                : Seed fed into random number generator. Default set to be the EPOCH time at runtime.
 */
EdgeWeight RandomGraph::random_tsp(
    int number_of_vertices,
    EdgeWeight weight_limit = 6000.0,
    int seed = -1, 
    bool symmetric = true)
{   
    // Seeding the random number generator
    if (seed == -1)
    {
        seed = std::chrono::system_clock::now().time_since_epoch().count();
    }
    std::mt19937_64 rng(seed);
    std::uniform_real_distribution<EdgeWeight> random_coordinate(-180.0, 180.0);
    std::uniform_real_distribution<EdgeWeight> random_weight(0.0, weight_limit);

    // Generate random data for random graph
    VertexData vertex_data_array[number_of_vertices];
    std::vector<std::vector<EdgeWeight> > distances(number_of_vertices * number_of_vertices);
    for (int i = 0; i < number_of_vertices; i++)
    {
        vertex_data_array[i] = VertexData({random_coordinate(rng), random_coordinate(rng)});
        distances[i].assign(number_of_vertices, std::numeric_limits<EdgeWeight>::max());
    }

    // Generate random_permutation
    int permu[number_of_vertices];
    EdgeWeight alpha[number_of_vertices];
    EdgeWeight gamma = std::numeric_limits<EdgeWeight>::max(), optimal_cost = 0, d;
    int u, v;
    for (int i = 0; i < number_of_vertices; i++)
    {
        permu[i] = i;
        alpha[i] = random_weight(rng);
        gamma = std::min(gamma, 2*alpha[i]);
    }
    std::random_shuffle(permu, permu + number_of_vertices);
    
    std::uniform_real_distribution<EdgeWeight> random_pertubation(0.0, gamma);
    for (u = 0; u < number_of_vertices; u++)
    {
        for (v = 0; v < number_of_vertices; v++)
        {
            if (u < v)
            {
                distances[u][v] = distances[v][u] = alpha[u] + alpha[v] + random_pertubation(rng);
            }
        }
    }
    for (int i = 0; i < number_of_vertices - 1; i++)
    {
        u = permu[i], v = permu[i+1], d = alpha[u] + alpha[v];
        distances[u][v] = distances[v][u] = d;
        optimal_cost += d;
    }
    u = permu[0], v = permu[number_of_vertices - 1], d = alpha[u] + alpha[v];
    distances[u][v] = distances[v][u] = d;
    optimal_cost += d; 

    // Build the graph
    for (int i = 0; i < number_of_vertices; i++)
    {
        std::vector<std::pair<VertexData, EdgeWeight>> distance(i); 
        for (int j = 0; j < i; j++)
        {
            distance[j] = {vertex_data_array[j], distances[i][j]};
        }
        add_vertex(vertex_data_array[i], distance);
    }

    return optimal_cost;
}