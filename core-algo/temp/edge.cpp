#include<iostream>
#include<unordered_map>
#include<vector>
#include<cstdio>
#include<assert.h>

#include "graph.hpp"

// Edge Class implementation

Edge::Edge(std::pair<Vertex*, Vertex*> vertices, EdgeWeight weight){
    this->vertices = vertices;
    this->weight = weight;
}

Edge::Edge(){
    this->vertices.first = nullptr;
    this->vertices.second = nullptr;
    this->weight = -1; // placeholder value for weight
}

void Edge::set_weight(EdgeWeight weight){
    this->weight = weight;
}

void Edge::set_vertices(std::pair<Vertex*, Vertex*> vertices){
    this->vertices = vertices;
}

std::pair<Vertex*, Vertex*> Edge::get_vertices(){
    return this->vertices;
}

EdgeWeight Edge::get_weight(){
    return this->weight;
}
