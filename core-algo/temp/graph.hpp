#include<iostream>
#include<algorithm>
#include<unordered_map>
#include<unordered_set>

#include<vector>
#include<stack>
#include<cstdio>
#include<assert.h>

#include "Vec3_temp.cpp"

using EdgeWeight = double;

class VertexData{

protected:
    std::pair<double, double> geolocation;

    // Is 1 if is inventory, 0 otherwise
    int is_inventory = 0;

public:
    VertexData(std::pair<double, double> geolocation);
    VertexData();
    std::pair<double, double> get_geolocation() const;
    bool operator==(const VertexData &other) const;
    bool operator!=(const VertexData &other) const;
    double get_distance(const VertexData &other) const;
    std::vector<double> get_coordinates() const;

    Vec3 get_euclidean_coordinates() const;
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
    bool operator!=(const Vertex &other) const;

    Vec3 get_euclidean_coordinates() const;

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


    // get edge weight functions
    EdgeWeight get_edge_weight(int i, int j) const;
    EdgeWeight get_edge_weight(VertexData di, int j) const;
    EdgeWeight get_edge_weight(int i, VertexData dj) const;
    EdgeWeight get_edge_weight(VertexData di, VertexData dj) const;


    std::vector<std::vector<double>> build_adjacency_matrix()    const;

    // minimum spanning tree functions
    std::vector<Edge*> min_spanning();
    std::vector<Edge*> min_spanning(const std::vector<int> &vertices_in_tree);


    // mincost matching functions
    std::vector<std::pair<int,int>> perfect_mincost_matching(std::vector<int> vertex_indices);
    std::vector<std::pair<int,int>> heuristic_perfect_mincost_matching(std::vector<int> vertex_indices);


    // vertex clustering functions
    // File clustering_vertices.cpp
    std::vector< std::vector<int> >cluster_vertices(const std::vector<int> &vertices_to_cluster, int num_clusters);


    // Functions for path analysis
    // File path_analysis.cpp

    double cost_of_path(const std::vector<int>& path) const;
    std::vector<int> best_path_brute_force(const std::vector<int>& path_vertices) const;


    // File TSP_approximation.cpp
    // Eulerian Path
    std::vector<int> euler_tour(const std::vector<Edge*>& smaller_graph) const;

    std::vector<int> shortcut_path(const std::vector<int> &path) const;

    // TSP = Travelling Salesman Problem
    std::vector<int> TSP();
    std::vector<int> TSP(std::vector<int> &vertices_in_tour);
    std::vector<int> TSP(const std::vector<Vertex*> &vertices_in_tour);
    std::vector<int> TSP_held_karp(); //only works in 1 inventory case

    // Functions for optimal routing
    // File algo_interface.cpp
    std::vector<int> optimal_routing(int inventory_index, std::vector<int> client_indices); //one inventory
    std::vector<int> optimal_routing(std::vector<int> inventory_indices, std::vector<int> client_indices); //multiple inventories




protected:

    int num_vertices;
    int num_inventory_vertices;
    int num_edges;

    std::vector<Vertex*> vertices;
    std::vector<Edge*> edges;

    std::vector<std::vector<Edge*>> adjacency_list;
    std::unordered_map< VertexData, int, std::hash<VertexData> > vertex_position;

    void swap_vertex_indices(int pos1, int pos2);
    void swap_vertex_to_last(int pos);
    void sort_edges();    

};



