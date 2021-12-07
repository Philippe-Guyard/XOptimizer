#include "graph.hpp"
#include <math.h>

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

double VertexData::get_distance(const VertexData& other) const{
    double phi1 = geolocation.first * (M_PI/180.0);
    double lambda1 = geolocation.second * (M_PI/180.0);
    double phi2 = other.get_geolocation().first * (M_PI/180.0);
    double lambda2 = other.get_geolocation().second * (M_PI/180.0);
    int R = 6371000;
    
    double deltaphi = phi2 - phi1;
    double deltalambda = lambda2 - lambda1;

    double a = sin(deltaphi/2) * sin(deltaphi/2) + cos(phi1) * cos(phi2) * sin(deltalambda/2) * sin(deltalambda/2);
    double c = 2 * atan2(sqrt(a), sqrt(1-a));
    
    return R * c;
};