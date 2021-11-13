#include<iostream>
#include<unordered_map>
#include<vector>
#include<cstdio>
#include<assert.h>

#include "graph.hpp"

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