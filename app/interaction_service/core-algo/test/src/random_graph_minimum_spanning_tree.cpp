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
 * Generate a random undirected weighted graph, and compute the cost of minimum 
 * spanning tree using Prim's algorithm. The result is then compared with official
 * method implemented and provided in Graph class.
 * 
 * Independent implementation of Minimum Spanning Tree algorithm, for testing purpose.
 * Here, Prim's algorithm is chosen.
 * 
 * @param {int}         number_of_vertices  : Number of vertices.
 * @param {EdgeWeight}  weight_limit        : Upper limit for ranom weight. The lower bound is set by default to 0. Default set to be 6000.0
 * @param {double}      density             : Density of random graph from 0 to 1, e.g. 0 corresponds to a tree, and 1 corresponds to complete graph. Default set to be 0.5
 * @param {int}         seed                : Seed fed into random number generator. Default set to be the EPOCH time at runtime.
 * 
 * @return {pair<EdgeWeight, EdgeWeight>} A pair of EdgeWeigt {expected_total_cost, computed_total_cost}, where expected_total_cost is computed by Prim's algorithm, and the computed_total_cost is computed by official method.
 */
std::pair<EdgeWeight, EdgeWeight> RandomGraph::minimum_spanning_tree_test(
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

    if (density < 0.0 || density > 1.0)
    {
        density = 0.5;
    }

    // randomly initialize the graph
    random_graph(number_of_vertices, 
                    weight_limit, 
                    density, 
                    seed);
    
    // Actual Prim's algorithm implementation
    std::vector<bool> added(number_of_vertices);
    std::vector<EdgeWeight> final_cost(number_of_vertices, std::numeric_limits<EdgeWeight>::max());
    final_cost[0] = 0;

    std::priority_queue<std::pair<EdgeWeight, int>,
                        std::vector<std::pair<EdgeWeight, int> >,
                        std::greater<std::pair<EdgeWeight, int> >
                        > queue;
    queue.push({0, 0});

    EdgeWeight expected_total_cost = 0.0,
                computed_total_cost = 0.0;
    
    // If the node is node not yet added to the minimum spanning tree add it, and increment the cost.
    while(!queue.empty())
    {
        std::pair<EdgeWeight, int> u = queue.top();
        queue.pop();
        int index = u.second;

        if(!added[index])
        {
            final_cost[index] = u.first;
            expected_total_cost += u.first;
            added[index] = true;

            // Iterate through all the nodes adjacent to the node taken out of priority queue.
            // Push only those nodes (weight,node) that are not yet present in the minumum spanning tree.
            for(int i = 0; i < number_of_vertices; i++)
            {
                if(get_edge_weight(index, i) < std::numeric_limits<EdgeWeight>::max() &&
                    !added[i] && 
                    u.first + get_edge_weight(index, i) < final_cost[i])
                {
                    queue.push({get_edge_weight(index, i), i});
                }
            }
        }
    }

    std::vector<Edge*> minimum_spanning_tree_kruskal = min_spanning();
    for (Edge* e : minimum_spanning_tree_kruskal)
    {
        computed_total_cost += e->get_weight();
    }

    return {expected_total_cost, computed_total_cost};
}