// Copyright (c) 2021 XOptimzer Team.
// All rights reserved.

// Standard libraries
#include <vector>                   // std::vector
#include <random>                   // std::mt19937_64
#include <chrono>                   // std::chrono::system_clock::now().time_since_epoch().count()

// External libraries
#include "gtest/gtest.h"

// Main files to be tested
#include "../temp/graph.hpp"

// Independent implementation of Disjoint Set (Union-Find), for testing purpose.
class DisjointSetTest
{
    std::vector<int> parents;

    DisjointSetUnion(
        int number_of_element = 0)
    {
        parents = std::vector<int>(number_of_element, -1);
    }

    // Find the representation of set containing the element
    int find(
        int element)
    {
        return parents[element] < 0 ? element : parents[element] = find(parents[element]);
    }

    // Uniting two sets containing first and second, respectively
    void union(
        int first,
        int second)
    {
        int first_root = find(first), 
            second_root = find(second);
        if (first_root != second_root)
        {
            if (parents[first_root] >= parents[second_root])
            {
                swap(first_root, second_root);
            }
            parents[first_root] += parents[second_root];
            parents[second_root] = first_root;
        }
    }
};

namespace
{
    const int NUMBER_OF_NODES = 500, 
              NUMBER_OF_QUERIES = 750,
              NUMBER_OF_TESTS = 20;
    std::mt19937_64 random_seed(std::chrono::system_clock::now().time_since_epoch().count());

    TEST(DisjointSet, constructor)
    {
        DisjointSet dsu = DisjointSet(NUMBER_OF_NODES);
    }

    TEST(DisjointSet, maintest)
    {
        for (int test = 0; test < NUMBER_OF_TEST; test++)
        {
            // Random number generator
            long long seed = random_seed();
            std::mt19937_64 rng(seed);

            DisjointSet dsu = DisjointSet(NUMBER_OF_NODES);
            DisjointSetTest dsu_test = DisjointSetTest(NUMBER_OF_TEST);

            for (int query_index = 0; query_index < NUMBER_OF_QUERIES; query_index++)
            {
                if (rng()&1)
                {
                    int u = rng()%NUMBER_OF_NODES,
                        v = rng()%NUMBER_OF_NODES;
                    dsu.union(u, v);
                    dsu_test.union(u, v);
                }
                else
                {
                    int u = rng()%NUMBER_OF_NODES;
                    EXPECT_EQ(dsu.find(u), dsu_test.find(u))
                        << "With seed = "
                        << seed 
                        << ", query_index = "
                        << query_index
                        << ", expected answer and computed answer differ.";
                }
            }
        }
    }
}