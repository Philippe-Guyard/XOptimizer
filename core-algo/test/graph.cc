// Copyright (c) 2021 XOptimzer Team.
// All rights reserved.

// Standard libraries
#include <utility>                  // std::pair, std::make_pair
#include <vector>                   // std::vector  

// External libraries
#include "gtest/gtest.h"

// Main files to be tested
#include "../temp/graph.hpp"

namespace
{
    int number_of_vertices = 2;

    int index-ecole_polytechnique = 1;
    int index-ens_ulm = 2;
    std::pair<double, double> coordinate_ecole_polytechnique = {48.71470768253242, 2.21150627670902};
    std::pair<double, double> coordinate_ens_ulm = {48.84234699954427, 2.345158168906672};
    std::pair<double, double> coordinate_ens_saclay = {48.71321687547235, 2.166206918679105};
    VertexData locations[2] = {VertexData(coordinate_ecole_polytechnique), 
                                VertexData(coordinate_ens_ulm)};
    
    std::vector<std::vector<EdgeWeight> > distances(2);
    distances[0] = {0.0, 24.8};
    distances[1] = {22.9, 0.0};

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
        graph.add_vertex(coordinate_ens_saclay, additional_distances);
    }

    TEST(Graph, DeleteVertex)
    {
        Graph graph = Graph(number_of_vertices,
                            locations, 
                            distances);
        graph.delete_vertex(coordinate_ens_ulm);
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
                EXPECT_EQ(distances[i][j], graph.get_edge_weight(VertexData[i], j))
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
                EXPECT_EQ(distances[i][j], graph.get_edge_weight(VertexData[i], j))
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
                EXPECT_EQ(distances[i][j], graph.get_edge_weight(VertexData[i], VertexData[j]))
                    << "Initial distance and stored distance between Node " 
                    << i 
                    << " and Node " 
                    << j 
                    << " differ.\n";
            }
        }
    }
}