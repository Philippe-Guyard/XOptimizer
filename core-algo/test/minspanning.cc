// Copyright (c) 2021 XOptimzer Team.
// All rights reserved.

// Standard libraries
#include <utility>                  // std::pair, std::make_pair
#include <vector>                   // std::vector
#include <limits>                   // std::numeric_limits
#include <queue>                    // std::priority_queue
#include <random>                   // std::mt19937_64
#include <chrono>                   // std::chrono::system_clock::now().time_since_epoch().count()

// External libraries
#include "gtest/gtest.h"
#include "random_graph.hpp"

// Main files to be tested
#include "../temp/graph.hpp"

using EdgeWeight = long double;

// Independent implementation of Minimum Spanning Tree algorithm, for testing purpose.
// Here, Prim's algorithm is chosen.
class MinimumSpanningTreeTest : public RandomGraph
{
    public:
        pair<EdgeWeight, EdgeWeight> minimum_spanning_tree_test
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

            // randomly initialize the graph
            random_graph(number_of_vertices, 
                         weight_limit, 
                         density, 
                         seed);
            
            // Actual Prim's algorithm implementation
            bool added[num_vertices];
            memset(added, false, sizeof(added));

            std::priority_queue<pair<EdgeWeight, int>,
                                vector<pair<EdgeWeight, int> >,
                                greater<pair<EdgeWeight, int> >
                                > queue;
            queue.push({0, 0});

            EdgeWeight expected_total_cost = 0.0,
                       computed_total_cost = 0.0;
            
            // If the node is node not yet added to the minimum spanning tree add it, and increment the cost.
            while(not queue.empty())
            {
                pair<EdgeWeight, int> u = q.top();
                q.pop();
                EdgeWeight cost = u.first;
                int index = u.second;

                if(not added[index])
                {
                    expected_total_cost += cost;
                    added[index] = true;

                    // Iterate through all the nodes adjacent to the node taken out of priority queue.
                    // Push only those nodes (weight,node) that are not yet present in the minumum spanning tree.
                    for(int i = 0; i < num_vertices; i++)
                    {
                        if(adjacency_list[index][i] != nullptr && not added[i])
                        {
                            q.push({(*adjacency_list[index][i]).get_weight(),
                                     i});
                        }
                    }
                }
            }

            vector<Edge> minimum_spanning_tree_kruskal = min_spanning();
            for (Edge e : minimum_spanning_tree_kruskal)
            {
                computed_total_cost += e.get_weight();
            }

            return {expected_total_cost, computed_total_cost};
        }
};

namespace
{
    const int NUMBER_OF_TEST = 20;
    std::mt19937_64 rng(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_real_distribution density(0.0, 1.0);

    TEST(MinimumSpanningTree, Kruskal)
    {
        MinimumSpanningTreeTests graph = Graph();
        for (int i = 0; i < NUMBER_OF_TEST; i++)
        {
            int number_of_vertices = rng() % 1000 + 1;
            EdgeWeight weight_limit = 6000.0;
            double density = density(rng);
            long long seed = rng();

            pair<EdgeWeight, EdgeWeight> result = 
                graph.minimum_spanning_tree_test(
                    number_of_vertices,
                    weight_limit,
                    density,
                    seed);
            
            EXPECT_DOUBLE_EQ(result.first, result.second)
                << "For number_of_vertices = " 
                << number_of_vertices
                << ", weight_limit = "
                << weight_limit
                << ", density = "
                << density
                << ", seed = "
                << seed
                << ", the expected and computed minimum cost differ.\n"; 
        }
    }
}