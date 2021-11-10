#include<iostream>
#include<unordered_map>
#include<vector>
#include<cstdio>
#include<assert.h>

#include "graph.hpp"

// Vertex Class Implementaton

Vertex::Vertex(){
    this->v_data = VertexData();
    this->v_index = -1; //placeholder value for index
}

Vertex::Vertex(VertexData v_data, int v_index){
    this->v_data = v_data;
    this->v_index = v_index;
}

int Vertex::get_index() const{
    return this->v_index;
}

void Vertex::set_index(int new_index){
    this->v_index = new_index;
}

VertexData Vertex::get_data() const{
    return this->v_data;
}

bool Vertex::operator==(Vertex& v2){
    return v2.get_data() == this->v_data;
}
