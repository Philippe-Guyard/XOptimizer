// Copyright (c) 2021 XOptimzer Team.
// All rights reserved.

// Standard libraries
#include <utility>                  // std::pair, std::make_pair

// External libraries
#include "gtest/gtest.h"

// Main files to be tested
#include "../temp/graph.hpp"

namespace
{
    std::pair<double, double> coordinate_ecole_polytechnique = {48.71470768253242, 2.21150627670902};
    std::pair<double, double> coordinate_ens_ulm = {48.84234699954427, 2.345158168906672};

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

        EXPECT_NE(location_ecole_polytechnique, location_ens_ulm)
            << "Comparator fails to compare different objects.\n";
    }
}