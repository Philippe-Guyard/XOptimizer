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
#include <cstring>                  // std::memset
#include <unordered_set>            // std::unordered_set
#include <iostream>
#include <assert.h>

// External libraries
#include "random_graph.hpp"

/**
 * Initialize to a random undirected weighted graph, with given density and weight limit, and guaranteed to have Eulerian circuits.
 * 
 * @param {int}         number_of_vertices  : Number of vertices.
 * @param {EdgeWeight}  weight_limit        : Upper limit for ranom weight. The lower bound is set by default to 0. Default set to be 6000.0
 * @param {double}      density             : Density of random graph from 0 to 1, e.g. 0 corresponds to a tree, and 1 corresponds to complete graph. Default set to be 0.5
 * @param {int}         seed                : Seed fed into random number generator. Default set to be the EPOCH time at runtime.
 */
void RandomGraph::random_graph_with_eulerian_circuits(
    int number_of_vertices, 
    EdgeWeight weight_limit = 6000.0, 
    double density = 0.5, 
    int seed = -1)
{
    if (number_of_vertices < 2)
    {
        throw std::invalid_argument("Number of vertices is insufficient.");
    }
    
    // Seeding the random number generator
    if (seed == -1)
    {
        seed = std::chrono::system_clock::now().time_since_epoch().count();
    }
    std::mt19937_64 rng(seed);
    std::uniform_real_distribution<double> random_coordinate(-180.0, 180.0);
    std::uniform_real_distribution<long double> random_weight(0.0, weight_limit);

    // Generate random vertices
    VertexData vertex_data_array[number_of_vertices];
    std::vector<std::vector<EdgeWeight> > distances(number_of_vertices);
    for (int i = 0; i < number_of_vertices; i++)
    {
        vertex_data_array[i] = VertexData({random_coordinate(rng), random_coordinate(rng)});
        distances[i].assign(number_of_vertices, std::numeric_limits<EdgeWeight>::max());
    }

    // Build underlying random spanning tree
    // Ref: Alexey S. Rodionov and Hyunseung Choo, On Generating Random Network Structures: Trees, ICCS 2003, LNCS 2658, pp. 879-887, 2003.
    int temp[number_of_vertices],  
        added[number_of_vertices],  
        deg[number_of_vertices], 
        odd_deg_vertices[number_of_vertices];
    memset(deg, 0, sizeof(deg));
    int cnt = 0;
    for (int i = 0; i < number_of_vertices; i++) 
    {
        temp[i] = i;
    }
    std::shuffle(temp, temp + number_of_vertices, rng);
    added[0] = temp[0];
    for (int count = 1; count < number_of_vertices; count++)
    {
        int index = rng()%count,
            v = temp[count],
            u = added[index];
        added[count] = v;
        deg[u]++, deg[v]++;
        distances[u][v] = distances[v][u] = random_weight(rng);
    }

    // Generate additional random edges
    std::bernoulli_distribution bern_dist(density);
    for (int i = 0; i < number_of_vertices; i++)
    {
        for (int j = i+1; j < num_vertices; j++)
        {
            if (distances[i][j] == std::numeric_limits<EdgeWeight>::max() && bern_dist(rng))
            {
                distances[i][j] = distances[j][i] = random_weight(rng);
                deg[i]++, deg[j]++;
            }
        }
    }
    
    // Make degrees of all vertices even
    for (int i = 0; i < number_of_vertices; i++)
    {
        if (deg[i] & 1)
        {
            odd_deg_vertices[cnt++] = i;
        }
    }
    // check that vertices of odd degrees do come in pairs as expected by Handshake lemma.
    if (cnt & 1)
    {
        throw std::runtime_error("Vertices of odd degress do not come in pairs.");
    }
    while (cnt)
    {
        std::uniform_int_distribution<int> random_vertices_i(0, cnt-1);
        std::uniform_int_distribution<int> random_vertices_j(0, cnt-2);
        int i = random_vertices_i(rng), j = random_vertices_j(rng);
        if (i <= j)
        {
            j++;
        }
        if (i > j)
        {
            std::swap(i, j);
        }

        int &u = odd_deg_vertices[i], &v = odd_deg_vertices[j];
        if (distances[u][v] == std::numeric_limits<EdgeWeight>::max())
        {
            distances[u][v] = distances[v][u] = random_weight(rng);
            deg[u]++, deg[v]++;
        }
        else
        {
            distances[u][v] = distances[v][u] = std::numeric_limits<EdgeWeight>::max();
            deg[u]--, deg[v]--;
        }

        std::swap(v, odd_deg_vertices[cnt-1]);
        cnt--;
        std::swap(u, odd_deg_vertices[cnt-1]);
        cnt--;
    }
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
}

/**
 * Checking if the the result returned from method finding eulerian circuits is correct
 */
bool RandomGraph::eulerian_circuit_check()
{
    std::vector<Edge*> existing_edges;
    std::unordered_set<int> to_visit_edges;
    int u, v;
    for (Edge* e : edges)
    {
        if (e->get_weight() < std::numeric_limits<EdgeWeight>::max())
        {
            existing_edges.push_back(e);
            u = (e->get_vertices()).first->get_index();
            v = (e->get_vertices()).second->get_index();
            if (u > v)
            {
                std::swap(u, v);
            }
            to_visit_edges.insert(u * num_edges + v);
        }
    }
    std::vector<int> result = euler_tour(existing_edges);
    
    for (int i = 1; i < result.size(); i++)
    {
        u = result[i-1], v = result[i];
        if (u > v)
        {
            std::swap(u, v);
        }
        if (to_visit_edges.find(u * num_edges + v) == to_visit_edges.end())
        {
            return false;
        }
        else
        {
            to_visit_edges.erase(u * num_edges + v);
        }
    }
    return true;
}