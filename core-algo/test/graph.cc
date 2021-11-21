// Copyright (c) 2021 XOptimzer Team.
// All rights reserved.

// Standard libraries
#include <utility>                  // std::pair, std::make_pair
#include <vector>                   // std::vector  

// External libraries
#include "gtest/gtest.h"

// Main files to be tested
#include "../src/graph.hpp"

namespace
{
    int number_of_vertices = 2;

    int index_ecole_polytechnique = 1;
    int index_ens_ulm = 2;
    std::pair<double, double> coordinate_ecole_polytechnique = {48.71470768253242, 2.21150627670902};
    std::pair<double, double> coordinate_ens_ulm = {48.84234699954427, 2.345158168906672};
    std::pair<double, double> coordinate_ens_saclay = {48.71321687547235, 2.166206918679105};
    VertexData ecole_polytechnique = VertexData(coordinate_ecole_polytechnique),
               ens_ulm = VertexData(coordinate_ens_ulm), 
               ens_saclay = VertexData(coordinate_ens_saclay);
    VertexData locations[2] = {ecole_polytechnique,
                               ens_ulm};
    
    std::vector<std::vector<EdgeWeight> > distances = 
        {
            {0.0, 22.9}, // Use 24.8 for directed graph 
            {22.9, 0.0}
        };

    std::vector<std::pair<VertexData, EdgeWeight> > additional_distances = 
        {
            {coordinate_ecole_polytechnique, 3.2},
            {coordinate_ens_ulm, 30.2}
        };

    TEST(Graph, Constructor)
    {
        Graph graph = Graph(number_of_vertices,
                            locations, 
                            distances);
    }

    TEST(Graph, DefaultConstructor)
    {
        Graph graph = Graph();
    }

    TEST(Graph, AddVertex)
    {
        Graph graph = Graph(number_of_vertices,
                            locations, 
                            distances);
        graph.add_vertex(ens_saclay, additional_distances);
        for (int i = 0; i < number_of_vertices; i++)
        {
            EXPECT_EQ(additional_distances[i].second, graph.get_edge_weight(i, number_of_vertices))
                << "Initial distance and stored distance between Node " 
                << i 
                << " and the new node differ.\n";
        }
    }

    TEST(Graph, DeleteVertex)
    {
        Graph graph = Graph(number_of_vertices,
                            locations, 
                            distances);
        graph.delete_vertex(ens_ulm);
    }

    TEST(Graph, GetEdgeWeightIndexAndIndex)
    {
        Graph graph = Graph(number_of_vertices,
                            locations, 
                            distances);
        for (int i = 0; i < number_of_vertices; i++)
        {
            for (int j = 0; j < number_of_vertices; j++)
            {
                EXPECT_EQ(distances[i][j], graph.get_edge_weight(i, j))
                    << "Initial distance and stored distance between Node " 
                    << i 
                    << " and Node " 
                    << j 
                    << " differ.\n";
            }
        }
    }

    TEST(Graph, GetEdgeWeightVertexDataAndIndex)
    {
        Graph graph = Graph(number_of_vertices,
                            locations, 
                            distances);
        for (int i = 0; i < number_of_vertices; i++)
        {
            for (int j = 0; j < number_of_vertices; j++)
            {
                EXPECT_EQ(distances[i][j], graph.get_edge_weight(locations[i], j))
                    << "Initial distance and stored distance between Node " 
                    << i 
                    << " and Node " 
                    << j 
                    << " differ.\n";
            }
        }
    }

    TEST(Graph, GetEdgeWeightIndexAndVertexData)
    {
        Graph graph = Graph(number_of_vertices,
                            locations, 
                            distances);
        for (int i = 0; i < number_of_vertices; i++)
        {
            for (int j = 0; j < number_of_vertices; j++)
            {
                EXPECT_EQ(distances[i][j], graph.get_edge_weight(i, locations[j]))
                    << "Initial distance and stored distance between Node " 
                    << i 
                    << " and Node " 
                    << j 
                    << " differ.\n";
            }
        }
    }

    TEST(Graph, GetEdgeWeightVertexDataAndVertexData)
    {
        Graph graph = Graph(number_of_vertices,
                            locations, 
                            distances);
        for (int i = 0; i < number_of_vertices; i++)
        {
            for (int j = 0; j < number_of_vertices; j++)
            {
                EXPECT_EQ(distances[i][j], graph.get_edge_weight(locations[i], locations[j]))
                    << "Initial distance and stored distance between Node " 
                    << i 
                    << " and Node " 
                    << j 
                    << " differ.\n";
            }
        }
    }
}