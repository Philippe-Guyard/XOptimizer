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
#include <utility>                  // std::pair, std::make_pair

// External libraries
#include "../lib/googletest/googletest/include/gtest/internal/gtest.h"

// Main files to be tested
#include "../temp/graph.hpp"

using EdgeWeight = long double;

namespace
{
    int index = 1;
    int new_index = 2;

    std::pair<double, double> coordinate_ecole_polytechnique = {48.71470768253242, 2.21150627670902};
    std::pair<double, double> coordinate_ens_ulm = {48.84234699954427, 2.345158168906672};
    VertexData location_ecole_polytechnique = VertexData(coordinate_ecole_polytechnique);
    VertexData location_ens_ulm = VertexData(coordinate_ens_ulm);

    std::pair<Vertex*, Vertex*>  vertices = {*coordinate_ecole_polytechnique, *coordinate_ens_ulm};
    std::pair<Vertex*, Vertex*>  new_vertices = {*coordinate_ens_ulm, *coordinate_ecole_polytechnique};
    
    EdgeWeight weight = 3.14159265358979;
    EdgeWeight new_weight = 2.71828182845904;

    TEST(Edge, Constructor)
    {
        Edge edge = Edge(index, vertices, weight);
    }
    
    TEST(Edge, DefaultConstructor)
    {
        Edge edge = Edge();
    }

    TEST(Edge, GetWeight)
    {
        Edge edge = Edge(index, vertices, weight);
        EdgeWeight get_weight = edge.get_weight();
        EXPECT_EQ(weight, get_weight)
            << "Initial weight and stored weight differ.\n";
    }

    TEST(Edge, GetVertices)
    {
        Edge edge = Edge(index, vertices, weight);
        std::pair<Vertex*, Vertex*>  get_vertices = edge.get_vertices();
        EXPECT_EQ(get_vertices.first, vertices.first)
            << "Initial vertices and stored vertices differ in the first component.\n";
        EXPECT_EQ(get_vertices.second, vertices.second)
            << "Initial vertices and stored vertices differ in the first component.\n";
    }

    TEST(Edge, GetIndex)
    {
        Edge edge = Edge(index, vertices, weight);
        int get_index = edge.get_index();
        EXPECT_EQ(index, get_index)
            << "Initial index and stored index differ.\n";
    }

    TEST(Edge, SetWeight)
    {
        Edge edge = Edge(index, vertices, weight);
        edge.set_weight(new_weight);
        EdgeWeight get_weight = edge.get_weight();
        EXPECT_EQ(new_weight, get_weight)
            << "Set weight and stored weight differ.\n";
    }

    TEST(Edge, SetVertices)
    {
        Edge edge = Edge(index, vertices, weight);
        edge.set_vertices(new_vertices);
        std::pair<Vertex*, Vertex*>  get_vertices = edge.get_vertices();
        EXPECT_EQ(get_vertices.first, new_vertices.first)
            << "Set vertices and stored vertices differ in the first component.\n";
        EXPECT_EQ(get_vertices.second, new_vertices.second)
            << "Set vertices and stored vertices differ in the first component.\n";
    }

    TEST(Edge, SetIndex)
    {
        Edge edge = Edge(index, vertices, weight);
        edge.set_index(new_index);
        int get_index = edge.get_index();
        EXPECT_EQ(new_index, get_index)
            << "Set index and stored index differ.\n";
    }
}