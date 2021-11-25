// Copyright (c) 2021 XOptimzer Team.
// All rights reserved.

// Standard libraries
#include <utility>                  // std::pair, std::make_pair
#include <chrono>                   // std::chrono::system_clock::now().time_since_epoch().count()
#include <random>                   // std::mt19937_64
#include <algorithm>                // std::random_shuffle, std::min
#include <vector>                   // std::vector
#include <limits>                   // std::numeric_limits

// External libraries
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
    std::uniform_real_distribution<double> random_coordinate(-180.0, 180.0);
    std::uniform_real_distribution<long double> random_weight(0.0, weight_limit);

    // Generate random vertices and construct unordered_map
    num_vertices = number_of_vertices;
    vertices.resize(num_vertices);
    for (int i = 0; i < num_vertices; i++)
    {
        VertexData vertex_data = VertexData({random_coordinate(rng), random_coordinate(rng)});
        vertices[i] = new Vertex(
                        vertex_data, 
                        i);
        vertex_position[vertex_data] = i;
    }

    // Resize adjacency list
    adjacency_list.resize(num_vertices);
    for (int i = 0; i < num_vertices; i++)
    {
        adjacency_list[i].resize(num_vertices, nullptr);
    }

    // Build underlying random spanning tree
    // Ref: Alexey S. Rodionov and Hyunseung Choo, On Generating Random Network Structures: Trees, ICCS 2003, LNCS 2658, pp. 879-887, 2003.
    num_edges = 0;
    std::vector<int> temp(num_vertices),  
        added(num_vertices);
    for (int i = 0; i < num_vertices; i++) temp[i] = i;
    std::shuffle(temp.begin(), temp.end(), rng);
    added[0] = temp[0];
    for (int count = 1; count < num_vertices; count++)
    {
        int index = rng()%count,
            v = temp[count],
            u = added[index];
        added[count] = v;
        // Passing vertices by address
        Edge* new_edge_ptr = new Edge(
                                    {vertices[u], 
                                    vertices[v]}, 
                                    random_weight(rng), 
                                    num_edges++);
        // Passing edge by reference
        edges.push_back(new_edge_ptr);
        adjacency_list[u][v] = adjacency_list[v][u] = new_edge_ptr;
    }

    // Generate additional random edges
    std::bernoulli_distribution bern_dist(density);
    for (int i = 0; i < num_vertices; i++)
    {
        for (int j = i+1; j < num_vertices; j++)
        {
            if (bern_dist(rng) && adjacency_list[i][j] == nullptr)
            {
                // Passing vertices by address
                Edge* new_edge_ptr = new Edge(
                                            {vertices[i], 
                                            vertices[j]}, 
                                            random_weight(rng), 
                                            num_edges++);
                // Passing edge by reference
                edges.push_back(new_edge_ptr);
                adjacency_list[i][j] = adjacency_list[j][i] = new_edge_ptr;
            }
        }
    }
}

void RandomTSP::random_tsp(
    int number_of_vertices,
    EdgeWeight weight_limit = 6000.0,
    int seed = -1, 
    bool symmetric = True)
{   
    // Seeding the random number generator
    if (seed == -1)
    {
        seed = std::chrono::system_clock::now().time_since_epoch().count();
    }
    std::mt19937_64 rng(seed);
    std::uniform_real_distribution<double> random_coordinate(-180.0, 180.0);
    std::uniform_real_distribution<EdgeWeight> random_weight(0.0, weight_limit);

    // Generate random data for random graph
    std::vector<VertexData> vertex_data_array(number_of_vertices);
    std::vector<std::vector<EdgeWeight> > distances(number_of_vertices * number_of_vertices);
    for (int i = 0; i < number_of_vertices; i++)
    {
        vertex_data_array[i] = VertexData({random_coordinate(), random_coordinate()});
    }

    // Generate random_permutation
    std::vector<int> permu(number_of_vertices);
    std::vector<EdgeWeight> alpha(number_of_vertices);
    EdgeWeight gamma = std::numeric_limits<EdgeWeight>::max(), optimal_cost = 0, d;
    int u, v;
    for (int i = 0; i < number_of_vertices; i++)
    {
        permu[i] = i;
        alpha[i] = random_weight();
        gamma = min(gamma, 2*alpha[i]);
    }
    std::random_shuffle(permu.begin(), permu.end());
    
    std::uniform_real_distribution<EdgeWeight> random_pertubation(0.0, gamma);
    for (int u : permu)
    {
        for (int v : permu)
        {
            if (u < v)
            {
                distances[u][w] = distances[w][u] = alpha[u] + alpha[w] + random_pertubation();
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

    Graph(number_of_vertices, &vertex_data_array, distances);
    return optimal_cost;
}