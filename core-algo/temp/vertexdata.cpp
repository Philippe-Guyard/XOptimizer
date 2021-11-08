#include<iostream>
#include<unordered_map>
#include<vector>
#include<cstdio>
#include<assert.h>

#include "graph.hpp"

//overriding stds hash function for the VertexData class

namespace std {
  template <>
  struct hash<VertexData>
  {
    std::size_t operator()(const VertexData& v_data) const
    {
        using std::size_t;
        using std::hash;
        // Compute individual hash values for first,
        // second and combine them using XOR and bit shifting:
        pair<double, double> geolocation = v_data.get_geolocation();
        return (hash<double>()(geolocation.first) ^ (hash<double>()(geolocation.second) << 1));
    }
  };

}

// VertexData Class Implementation

VertexData::VertexData(){
    this->geolocation = std::make_pair(-1,-1); //placeholder values 
}

VertexData::VertexData(std::pair<double, double> geolocation){
    this->geolocation = geolocation;
}

std::pair<double, double> VertexData::get_geolocation() const{
    return this->geolocation;
}

bool VertexData::operator==(VertexData& v_data){
    return v_data.get_geolocation() == this->geolocation;
}