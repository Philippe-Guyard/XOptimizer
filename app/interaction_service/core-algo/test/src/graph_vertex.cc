// Copyright (c) 2021 XOptimzer Team.
// All rights reserved.

// Standard libraries
#include <utility>                  // std::pair, std::make_pair

// External libraries
#include "gtest/gtest.h"

// Main files to be tested
#include "../../src/graph/graph.hpp"

namespace
{
    int index_ecole_polytechnique = 1;
    int index_ens_ulm = 2;
    std::pair<double, double> coordinate_ecole_polytechnique = {48.71470768253242, 2.21150627670902};
    std::pair<double, double> coordinate_ens_ulm = {48.84234699954427, 2.345158168906672};
    VertexData location_ecole_polytechnique = VertexData(coordinate_ecole_polytechnique);
    VertexData location_ens_ulm = VertexData(coordinate_ens_ulm);

    TEST(Vertex, Constructor)
    {
        Vertex vertex = Vertex(location_ecole_polytechnique, 
                               index_ecole_polytechnique);
    }

    
    TEST(Vertex, DefaultConstructor)
    {
        Vertex vertex = Vertex();
    }

    TEST(Vertex, GetIndex)
    {
        Vertex vertex = Vertex(location_ecole_polytechnique, 
                               index_ecole_polytechnique);
        int vertex_index = vertex.get_index();
        EXPECT_EQ(vertex_index, index_ecole_polytechnique)
            << "Initial index and stored index differ.\n";
    }

    TEST(Vertex, GetData)
    {
        Vertex vertex = Vertex(location_ecole_polytechnique, 
                               index_ecole_polytechnique);
        VertexData location = vertex.get_data();
        EXPECT_EQ(location_ecole_polytechnique, location)
            << "Initial location and stored location differ.\n"; 
    }

    TEST(Vertex, Equal)
    {
        Vertex first_vertex = Vertex(location_ecole_polytechnique, 
                                     index_ecole_polytechnique);
        Vertex second_vertex = Vertex(location_ecole_polytechnique, 
                                      index_ecole_polytechnique);
        EXPECT_EQ(first_vertex, second_vertex)
            << "Comparator fails to compare equal object.\n";
    }
}
