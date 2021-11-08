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
    pair<double, double> coordinate_ecole_polytechnique = {48.71470768253242, 2.21150627670902};
    pair<double, double> coordinate_ens_ulm = {48.84234699954427, 2.345158168906672};

    TEST(VertexData, Constructor)
    {
        VertexData location_ecole_polytechnique = VertexData(coordinate_ecole_polytechnique);
    }

    TEST(VertexData, DefaultConstructor)
    {
        VertexData empty_location = VertexData();
    }

    TEST(VertexData, GetGeolocation)
    {
        VertexData location_ecole_polytechnique = VertexData(coordinate_ecole_polytechnique);
        pair<double, double> get_ecole_polytechnique_location = location_ecole_polytechnique.get_geolocation();
        
        EXPECT_EQ(coordinate_ecole_polytechnique.first, get_ecole_polytechnique_location.first)
            << "Initial coordinates and stored coordinates differ at the x-component.\n";
        EXPECT_EQ(coordinate_ecole_polytechnique.second, get_ecole_polytechnique_location.second)
            << "Initial coordinates and stored coordinates differ at the y-component.\n";
    }

    TEST(VertexData, Equal)
    {
        VertexData first_location_ecole_polytechnique = VertexData(coordinate_ecole_polytechnique);
        VertexData second_location_ecole_polytechnique = VertexData(coordinate_ecole_polytechnique);

        EXPECT_EQ(first_location_ecole_polytechnique, second_location_ecole_polytechnique)
            << "Comparator fails to compare equal objects.\n";
    }

    
    TEST(VertexData, NotEqual)
    {
        VertexData location_ecole_polytechnique = VertexData(coordinate_ecole_polytechnique);
        VertexData location_ens_ulm = VertexData(coordinate_ens_ulm);

        EXPECT_EQ(location_ecole_polytechnique, location_ens_ulm)
            << "Comparator fails to compare different objects.\n";
    }
}