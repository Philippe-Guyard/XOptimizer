#include<iostream>
#include<unordered_map>
#include<vector>
#include<cstdio>
#include<assert.h>

#include "graph.hpp"

// VertexData Class Implementation

VertexData::VertexData(){
    geolocation = std::make_pair(-1,-1); //placeholder values 
}

VertexData::VertexData(std::pair<double, double> geolocation){
    geolocation = geolocation;
}

std::pair<double, double> VertexData::get_geolocation() const{
    return geolocation;
}

bool VertexData::operator==(const VertexData& other) const{
    return other.get_geolocation() == geolocation;
}

bool VertexData::operator!=(const VertexData& other) const{
    return other.get_geolocation() != geolocation;
}