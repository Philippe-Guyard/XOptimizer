#include "graph.hpp"
#include "Vec3_temp.cpp"

// Vertex Class Implementaton

Vertex::Vertex(){
    v_data = VertexData();
    v_index = -1; //placeholder value for index
}

Vertex::~Vertex(){
    return;
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

bool Vertex::operator==(const Vertex &other) const{
    return other.get_data() == this->v_data;
}

bool Vertex::operator!=(const Vertex &other) const{
    return other.get_data() != this->v_data;
}

Vec3 Vertex::get_euclidean_coordinates()    const{
    return get_data().get_euclidean_coordinates();
}