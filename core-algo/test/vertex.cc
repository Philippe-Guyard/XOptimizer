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
#include <utility> // std::pair, std::make_pair

// External libraries
#include "../lib/googletest/googletest/include/gtest/internal/gtest.h"

// Main files to be tested
#include "../temp/graph.hpp"

namespace
{
    int index-ecole_polytechnique = 1;
    int index-ens_ulm = 2;
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
        int vertex_index = vertex.index();
        EXPECT_EQ(vertex_index, index)
            << "Initial index and stored index do not match.\n";
    }

    TEST(Vertex, GetData)
    {
        Vertex vertex = Vertex(location_ecole_polytechnique, 
                               index_ecole_polytechnique);
        VertexData location = vertex.get_data();
        EXPECT_EQ(location_ecole_polytechnique, location)
            << "Initial location and stored location do not match.\n"; 
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

    
    TEST(Vertex, NotEqual)
    {
        Vertex vertex_ep = Vertex(location_ecole_polytechnique, 
                                  index_ecole_polytechnique);
        Vertex vertex_ens = Vertex(location_ens_ulm, 
                                   index_ens_ulm);
        EXPECT_EQ(vertex_ep, vertex_ens)
            << "Comparator fails to compare different object.\n";
    }
}
