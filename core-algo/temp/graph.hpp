#include<iostream>
#include<algorithm>
#include<unordered_map>
#include<vector>
#include<cstdio>
#include<assert.h>

using EdgeWeight = long double;

class VertexData{

protected:
    std::pair<double, double> geolocation;

    // the geolocation uniquely defines a vertex, i.e. two vertices with the same geolocations have to be equal
    // TODO: think about the information we might want to hold in a vertex such as 
    // order ids, address information, etc.

public:
    VertexData(std::pair<double, double> geolocation);
    VertexData();
    std::pair<double, double> get_geolocation() const;
    bool operator==(const VertexData &other) const;
    bool operator!=(const VertexData &other) const;
};

//overriding stds hash function for the VertexData class

namespace std {

template <>
struct hash<VertexData>{
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

// Vertex should only be used through the Graph Class
class Vertex{

protected:
    int v_index;
    VertexData v_data;

public:
    Vertex(VertexData v_data, int v_index);
    Vertex();
    ~Vertex();

    int get_index() const;
    void set_index(int new_index);

    VertexData get_data() const;
    bool operator==(const Vertex& other) const;    

};

// Edge should only be used through the Graph Class
class Edge{

public:
    Edge(std::pair<Vertex*, Vertex*> vertices, EdgeWeight weight, int index);
    Edge();
    ~Edge();

    void set_vertices(std::pair<Vertex*, Vertex*> vertices);
    std::pair<Vertex*, Vertex*> get_vertices() const;

    EdgeWeight get_weight() const;
    void set_weight(EdgeWeight weight);

    int get_index() const;
    void set_index(int new_index);

    bool operator<(const Edge& e2);

protected:

    int e_index;
    std::pair<Vertex*, Vertex*> vertices;
    EdgeWeight weight;

};

class Graph{

public:

    Graph(int num_vertices, VertexData* vertex_data_array, std::vector<std::vector<EdgeWeight>> distances);
    Graph();
    ~Graph();

    void add_vertex(VertexData& data, std::vector<std::pair<VertexData, EdgeWeight>>& distances );
    void delete_vertex(VertexData& data);
    void update_vertex_data(VertexData& data);

    int get_vertex_position(VertexData &d) const;

    EdgeWeight get_edge_weight(int i, int j) const;
    EdgeWeight get_edge_weight(VertexData di, int j) const;
    EdgeWeight get_edge_weight(int i, VertexData dj) const;
    EdgeWeight get_edge_weight(VertexData di, VertexData dj) const;

    std::vector<Edge> min_spanning();

protected:

    int num_vertices;
    int num_edges;

    std::vector<Vertex*> vertices; 
    std::vector<Edge*> edges; 

    std::vector<std::vector<Edge*>> adjacency_list; 
    std::unordered_map< VertexData, int, std::hash<VertexData> > vertex_position;

    void swap_vertex_indices(int pos1, int pos2);
    void swap_vertex_to_last(int pos);

    void sort_edges();
};



