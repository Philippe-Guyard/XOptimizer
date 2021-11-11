// Copyright 2020, XOptimzer Team.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

// Standard libraries


// External libraries
#include "../lib/googletest/googletest/include/gtest/internal/gtest.h"

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