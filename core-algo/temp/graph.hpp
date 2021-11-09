#include<iostream>
#include<unordered_map>
#include<vector>
#include<cstdio>

using EdgeWeight = long double;

class Graph{

public:

    Graph(int num_vertices, VertexData* vertex_data_array, std::vector<std::vector<EdgeWeight>> distances);
    Graph();

    void add_vertex(VertexData& data, std::vector<std::pair<VertexData, EdgeWeight>>& distances );
    void delete_vertex(VertexData& data);
    void update_vertex_data(VertexData& data);

private:

    int num_vertices;
    int num_edges;

    std::vector<Vertex> vertices; 
    std::vector<Edge> edges; 

    std::vector<std::vector<Edge*>> adjacency_list; 
    std::unordered_map<VertexData, int> vertex_position;

    void swap_vertex_indices(int pos1, int pos2);
    void swap_vertex_to_last(int pos);
};

class Edge{

public:
    Edge(std::pair<Vertex*, Vertex*> vertices, EdgeWeight weight, int index);
    Edge();
    void set_weight(EdgeWeight weight);
    void set_vertices(std::pair<Vertex*, Vertex*> vertices);
    std::pair<Vertex*, Vertex*> get_vertices();

    EdgeWeight get_weight();

    int get_index();
    void set_index(int new_index);

private:

    // we have to add an index to each edge too
    int e_index;
    std::pair<Vertex*, Vertex*> vertices;
    EdgeWeight weight;

};


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
        bool operator==(VertexData &v_data);


};

class Vertex{
    private:
        int v_index;
        VertexData v_data;

    public:
        Vertex(VertexData v_data, int v_index);
        Vertex();

        int get_index();
        void set_index(int new_index);

        VertexData get_data();
        bool operator==(Vertex& v2);    

};


