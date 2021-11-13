// Copyright (c) 2021 XOptimzer Team.
// All rights reserved.

// Standard libraries
#include <vector>                   // std::vector
#include <random>                   // std::mt19937_64
#include <chrono>                   // std::chrono::system_clock::now().time_since_epoch().count()
#include <algorithm>                // std::swap

// External libraries
#include "gtest/gtest.h"

// Main files to be tested
#include "../temp/disjointset.hpp"

/**
 * Independent implementation of Disjoint Set (Union-Find), for testing purpose.
 */
class DisjointSetTest
{
        public:
        std::vector<int> parents;
        
        /**
         * Initialize DisjointSetTest
         * @param  {int}         number_of_elements : Number of elements.
         */
        DisjointSetTest(
            int number_of_elements = 0)
        {
            parents = std::vector<int>(number_of_elements, -1);
        }
        
        /**
         * Find the representation of the set containing an element.
         * @param  {int}                    element : Element to query.
         * 
         * @return {int} The representation of the set containing the queried element.
         */
        int find(
            int element)
        {
            return parents[element] < 0 ? element : parents[element] = find(parents[element]);
        }

        /**
         * Uniting two sets containing first and second, respectively
         * @param  {int}                      first : First element.
         * @param  {int}                     second : Second element. 
         */
        void union_set(
            int first,
            int second)
        {
            int first_root = find(first), 
                second_root = find(second);
            if (first_root != second_root)
            {
                if (parents[first_root] >= parents[second_root])
                {
                    std::swap(first_root, second_root);
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
        for (int test = 0; test < NUMBER_OF_TESTS; test++)
        {
            // Random number generator
            long long seed = random_seed();
            std::mt19937_64 rng(seed);

            DisjointSet dsu = DisjointSet(NUMBER_OF_NODES);
            DisjointSetTest dsu_test = DisjointSetTest(NUMBER_OF_NODES);

            for (int query_index = 0; query_index < NUMBER_OF_QUERIES; query_index++)
            {
                if (rng()&1)
                {
                    int u = rng()%NUMBER_OF_NODES,
                        v = rng()%NUMBER_OF_NODES;
                    dsu.Union(u, v);
                    dsu_test.union_set(u, v);
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