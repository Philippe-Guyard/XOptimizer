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
#include "../../lib/blossom5-v2_05/PerfectMatching.h"
#include "../../lib/blossom5-v2_05/GEOM/GeomPerfectMatching.h"

std::pair<EdgeWeight, EdgeWeight> RandomGraph::maximal_mincost_matching_test(
    std::vector<int>& vertex_indices)
{
    EdgeWeight computed_solution = 0, 
                expected_solution = 0;
    
    bool odd_num_vertices = false;
    std::vector<std::pair<VertexData, EdgeWeight> > distances(num_vertices);
    for (int i = 0; i < num_vertices; i++)
    {
        distances[i] = {vertices[i]->get_data(), std::numeric_limits<EdgeWeight>::max()};
    }
    VertexData dummy = VertexData();

    if (vertex_indices.size() & 1)
    /* 
    If the number of vertices is odd, we add another dummy vertex with weight of edges to
    other vertices to be infinity.
    */
    {
        odd_num_vertices = true;
        add_vertex(dummy, distances);
        vertex_indices.push_back(num_vertices - 1);
    }
    int number_of_vertices = vertex_indices.size(),
        number_of_edges = number_of_vertices * (number_of_vertices - 1) >> 1;
    
    PerfectMatching* perfect_matching = new PerfectMatching(number_of_vertices, number_of_edges);
    for (int i = 0; i < number_of_vertices; i++)
    {
        for (int j = i+1; j < number_of_vertices; j++)
        {
            perfect_matching->AddEdge(i, j, get_edge_weight(vertex_indices[i], vertex_indices[j]));
        }
    }
    
    struct PerfectMatching::Options options;
    perfect_matching->options = options;
    perfect_matching->Solve();

    for (int ind1 = 0; ind1 < number_of_vertices; ind1++)
    {
        int ind2 = perfect_matching->GetMatch(ind1);
        if (ind1 < ind2 && 
                (!odd_num_vertices || 
                ind2 < num_vertices - 1)
            )
        {
            expected_solution += get_edge_weight(vertex_indices[ind1], vertex_indices[ind2]);
        }
    }
    delete perfect_matching;
    
    if (odd_num_vertices)
    {
        delete_vertex(dummy);
        vertex_indices.pop_back();
    }
    
    std::vector<std::pair<int, int> > computed_solution_edges = 
        perfect_mincost_matching(vertex_indices);
    for (std::pair<int, int> e : computed_solution_edges)
    {
        computed_solution += get_edge_weight(e.first, e.second);
    }
    
    return {expected_solution, computed_solution};
}