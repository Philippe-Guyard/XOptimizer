#include<iostream>

#include<unordered_map>
#include<vector>
#include<cstdio>

// EDGES[i][j] = *Edge[Vertex indiced i] and

using EdgeWeight = long double;

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

    std::unordered_map<VertexData, int> order_to_index;
};

class Edge{
    private:
        std::pair<Vertex*, Vertex*> vertices;
        EdgeWeight weight;

    public:
        Edge(Vertex &v1, Vertex &v2, EdgeWeight weight);
        Edge();

        void set_weight(EdgeWeight weight);
        void set_vertices(std::pair<Vertex*, Vertex*> pair_vertices);

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
        // TODO: add an overloaded equal function
        // TODO: add an overloaded hash function


};


