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

bool VertexData::operator==(const VertexData& other) const{
    return other.get_geolocation() == this->geolocation;
}

bool VertexData::operator!=(const VertexData& other) const{
    return other.get_geolocation() != this->geolocation;
}