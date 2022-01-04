// Copyright (c) 2021 XOptimzer Team.
// All rights reserved.

// Standard libraries
#include <utility>                  // std::pair, std::make_pair

// External libraries
#include "gtest/gtest.h"

// Main files to be tested
#include "../../temp/graph/graph.hpp"

namespace
{
    int index = 1;
    int new_index = 2;

    std::pair<double, double> coordinate_ecole_polytechnique = {48.71470768253242, 2.21150627670902};
    std::pair<double, double> coordinate_ens_ulm = {48.84234699954427, 2.345158168906672};
    VertexData location_ecole_polytechnique = VertexData(coordinate_ecole_polytechnique);
    VertexData location_ens_ulm = VertexData(coordinate_ens_ulm);

    Vertex ecole_polytechnique = Vertex(location_ecole_polytechnique, 0);
    Vertex ens_ulm = Vertex(location_ens_ulm, 1);
    std::pair<Vertex*, Vertex*>  vertices = {&ecole_polytechnique, &ens_ulm};
    
    EdgeWeight weight = 3.14159265358979;
    EdgeWeight new_weight = 2.71828182845904;

    TEST(Edge, Constructor)
    {
        Edge edge = Edge(vertices, weight, index);
    }
    
    TEST(Edge, DefaultConstructor)
    {
        Edge edge = Edge();
    }

    TEST(Edge, GetWeight)
    {
        Edge edge = Edge(vertices, weight, index);
        EdgeWeight get_weight = edge.get_weight();
        EXPECT_EQ(weight, get_weight)
            << "Initial weight and stored weight differ.\n";
    }

    TEST(Edge, GetVertices)
    {
        Edge edge = Edge(vertices, weight, index);
        std::pair<Vertex*, Vertex*>  get_vertices = edge.get_vertices();
        EXPECT_EQ(get_vertices.first, vertices.first)
            << "Initial vertices and stored vertices differ in the first component.\n";
        EXPECT_EQ(get_vertices.second, vertices.second)
            << "Initial vertices and stored vertices differ in the first component.\n";
    }

    TEST(Edge, GetIndex)
    {
        Edge edge = Edge(vertices, weight, index);
        int get_index = edge.get_index();
        EXPECT_EQ(index, get_index)
            << "Initial index and stored index differ.\n";
    }

    TEST(Edge, SetWeight)
    {
        Edge edge = Edge(vertices, weight, index);
        edge.set_weight(new_weight);
        EdgeWeight get_weight = edge.get_weight();
        EXPECT_EQ(new_weight, get_weight)
            << "Set weight and stored weight differ.\n";
    }

    TEST(Edge, SetIndex)
    {
        Edge edge = Edge(vertices, weight, index);
        edge.set_index(new_index);
        int get_index = edge.get_index();
        EXPECT_EQ(new_index, get_index)
            << "Set index and stored index differ.\n";
    }
}