#include<iostream>
#include<unordered_map>
#include<vector>
#include<cstdio>
#include<assert.h>

#include "graph.hpp"

// Vertex Class Implementaton

Vertex::Vertex(){
    v_data = VertexData();
    v_index = -1; //placeholder value for index
}

Vertex::Vertex(VertexData v_data, int v_index){
    this->v_data = v_data;
    this->v_index = v_index;
}

int Vertex::get_index() const{
    return v_index;
}

void Vertex::set_index(int new_index){
    v_index = new_index;
}

VertexData Vertex::get_data() const{
    return v_data;
}

bool Vertex::operator==(const Vertex &other) const{
    return other.get_data() == v_data;
}
