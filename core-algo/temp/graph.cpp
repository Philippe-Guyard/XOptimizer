#include<iostream>

#include<unordered_map>
#include<vector>
#include<cstdio>

#include "graph.hpp"

/*
For quick reference:

class Graph{
    Graph(VertexData[], std::vector<std::vector<EdgeWeight>> distances);
    Graph();
    void add_vertex(VertexData& data, std::vector<std::pair<VertexData, EdgeWeight>>& distances );
    void delete_vertex(VertexData& data);
    void update_vertex_data(VertexData& data);
    int num_vertices;
    std::vector<Vertex> vertices; 
    std::vector<Edge> edges; 
    std::vector<std::vector<Edge*>> adjacency_list; 
    std::unordered_map<VertexData, int> vertex_position;
};

class Edge{
    private:
        std::pair<Vertex*, Vertex*> vertices;
        EdgeWeight weight;

    public:
        Edge(std::pair<Vertex*, Vertex*> vertices, EdgeWeight weight);
        Edge();
        void set_weight(EdgeWeight weight);
        void set_vertices(std::pair<Vertex*, Vertex*> vertices);
        std::pair<Vertex*, Vertex*> get_vertices();
        EdgeWeight get_weight();
};

class VertexData{};

class Vertex{
    private:
        int v_index;
        VertexData v_data;
    public:
        Vertex(VertexData v_data, int v_index);
        int get_index();
        VertexData get_data();
};
*/

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
/*
class VertexData{
    private:
        std::pair<double, double> geolocation;

        // the geolocation uniquely defines a vertex, i.e. two vertices with the same geolocations has to be equal
        // TODO: think about the information we might want to hold in a vertex such as 
        // order ids, address information, etc.

    public:
        VertexData(std::pair<double, double> geolocation);
        VertexData();
        std::pair<double, double> get_geolocation() const;
        bool operator==(VertexData v_data);


};
*/
std::pair<Vertex*, Vertex*> Edge::get_vertices(){
    return this->vertices;
}

EdgeWeight Edge::get_weight(){
    return this->weight;
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


// Vertex Class Implementaton

Vertex::Vertex(){
    this->v_data = VertexData();
    this->v_index = -1; //placeholder value for index
}

Vertex::Vertex(VertexData v_data, int v_index){
    this->v_data = v_data;
    this->v_index = v_index;
}

int Vertex::get_index(){
    return this->v_index;
}

VertexData Vertex::get_data(){
    return this->v_data;
}

bool Vertex::operator==(Vertex& v2){
    return v2.get_data() == this->v_data;
}


// Graph Class Implementation

Graph::Graph(int num_vertices, VertexData* vertex_data_array, std::vector<std::vector<EdgeWeight>> distances){

    /*
        Remarks:
            It is ignoring the possibility that some vertices are equivalent (as vertices in the same location).

    */

    this->num_vertices = num_vertices;
    for(int i=0; i<num_vertices; ++i){
        vertices.push_back(Vertex(vertex_data_array[i], i));
    }

    // Resizing adjacency_list
    adjacency_list.resize(num_vertices);
    for(int i=0; i<num_vertices; ++i){ adjacency_list[i].resize(num_vertices); }

    // we are ignoring the edge that goes from i to i
    for(int i=0; i<num_vertices; ++i){
        for(int j=i+1; j<num_vertices; ++j){

            // Passing vertices by address
            Edge* new_edge_ptr = new Edge(std::make_pair(&vertices[i], &vertices[j]), distances[i][j]);

            // Passing edge by reference
            edges.push_back(*new_edge_ptr); 

            adjacency_list[i][j] = adjacency_list[j][i] = new_edge_ptr;
        }
    }

    //unordered_map construction
    for(int i=0; i<num_vertices; ++i){
        vertex_position[vertex_data_array[i]] = i;
    }
}