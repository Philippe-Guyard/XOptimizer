// Copyright (c) 2021 XOptimzer Team.
// All rights reserved.

// Standard libraries
#include <utility>                  // std::pair, std::make_pair
#include <chrono>                   // std::chrono::system_clock::now().time_since_epoch().count()
#include <random>                   // std::mt19937_64, std::bernoulli_distribution
#include <algorithm>                // std::shuffle

// External libraries
#include "../temp/graph.hpp"
#include "random_graph.hpp"

using EdgeWeight = long double;
/**
 * Initialize to a random undirected weighted graph, with given density and weight limit.
 * 
 * @param {int}         number_of_vertices  : Number of vertices.
 * @param {EdgeWeight}  weight_limit        : Upper limit for ranom weight. The lower bound is set by default to 0. Default set to be 6000.0
 * @param {double}      density             : Density of random graph from 0 to 1, e.g. 0 corresponds to a tree, and 1 corresponds to complete graph. Default set to be 0.5
 * @param {int}         seed                : Seed fed into random number generator. Default set to be the EPOCH time at runtime.
 */
void RandomGraph::random_graph(
    int number_of_vertices, 
    EdgeWeight weight_limit = 6000.0, 
    double density = 0.5, 
    int seed = -1)
{
    // Seeding the random number generator
    if (seed == -1)
    {
        seed = std::chrono::system_clock::now().time_since_epoch().count();
    }
    std::mt19937_64 rng(seed);
    std::uniform_real_distribution random_coordinate(-180.0, 180.0);
    std::uniform_real_distribution random_weight(0.0, weight_limit);

    // Generate random vertices and construct unordered_map
    num_vertices = number_of_vertices;
    vertices.resize(num_of_vertices);
    for (int i = 0; i < num_of_vertices; i++)
    {
        std::pair<double, double> vertex_data = {random_coordinate(rng), random_coordinate(rng)};
        vertices[i] = Vertex(
                        VertexData(vertex_data), 
                        i);
        vertex_position[vertex_data] = i;
    }

    // Resize adjacency list
    adjacency_list.resize(num_vertices);
    for (int i = 0; i < num_vertices; i++)
    {
        adjacency_list[i] = vector<Edge*>(nullptr, num_vertices);
    }

    // Build underlying random spanning tree
    // Ref: Alexey S. Rodionov and Hyunseung Choo, On Generating Random Network Structures: Trees, ICCS 2003, LNCS 2658, pp. 879-887, 2003.
    num_edges = 0;
    int temp[num_vertices],
        added[num_vertices],
        count = 0;
    for (int i = 0; i < num_vertices; i++) temp[i] = i;
    std::shuffle(temp, temp + num_vertices, rng);
    added[count] = temp[count++];
    for (int i = 0; i < num_vertices; i++)
    {
        int v = temp[count],
            u = added[rng()%count];
        added[count++] = v;
        // Passing vertices by address
        Edge* new_edge_ptr = new Edge(
                                    std::make_pair(
                                        &vertices[u], 
                                        &vertices[v]), 
                                    random_weight(rng), 
                                    new_edge);
        // Passing edge by reference
        edges[new_edge++] = (*new_edge_ptr);
        adjacency_list[u][v] = adjacency_list[v][u] = new_edge_ptr;
    }

    // Generate additional random edges
    std::bernoulli_distribution bern_dist(density);
    for (int i = 0; i < num_vertices; i++)
    {
        for (int j = i+1; j < num_vertices; j++)
        {
            if (bern_dist(rng)) && adjacency[i][j] == nullptr)
            {
                // Passing vertices by address
                Edge* new_edge_ptr = new Edge(
                                            std::make_pair(
                                                &vertices[i], 
                                                &vertices[j]), 
                                            random_weight(rng), 
                                            new_edge);
                // Passing edge by reference
                edges[new_edge++] = (*new_edge_ptr);
                adjacency_list[i][j] = adjacency_list[j][i] = new_edge_ptr;
            }
        }
    }
}