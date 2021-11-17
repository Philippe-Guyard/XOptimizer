#include "graph.hpp"

// Edge Class implementation

Edge::Edge(std::pair<Vertex*, Vertex*> vertices, EdgeWeight weight, int index){
    this->vertices = vertices;
    this->weight = weight;
    this->e_index = index;
}

Edge::Edge(){
    this->vertices.first = nullptr;
    this->vertices.second = nullptr;
    this->weight = -1; // placeholder value for weight
    this->e_index = -1;
}

Edge::~Edge(){
    return;
}

void Edge::set_weight(EdgeWeight weight){
    this->weight = weight;
}

void Edge::set_vertices(std::pair<Vertex*, Vertex*> vertices){
    this->vertices = vertices;
}

std::pair<Vertex*, Vertex*> Edge::get_vertices() const{
    return this->vertices;
}

EdgeWeight Edge::get_weight() const{
    return this->weight;
}

int Edge::get_index() const{
    return this->e_index;
}

void Edge::set_index(int new_index){
    this->e_index = new_index;
}

bool Edge::operator<(const Edge& e2){
    return get_weight() < e2.get_weight();

}

bool compare_edge_pointers(Edge *ptr1, Edge *ptr2){
/**
 * Returns true if and only if the weight of the edge *ptr1 is smaller than that of *ptr2.
 * 
 */


    return ptr1->get_weight() < ptr2->get_weight();
}