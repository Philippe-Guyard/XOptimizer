#include "../src/graph.hpp"

class Map{

    public:

        Map(int num_vertices, VertexData* vertex_data_array, std::vector<std::vector<std::pair<int, EdgeWeight>>> adjacency_list);
        int brute_force_closest_vertex_index(VertexData& vertex_data);
        


    protected:

        int num_vertices;
        int num_edges;

        std::vector<Vertex*> vertices;
        std::vector<Edge*> edges;
        std::vector<std::vector<Edge*>> adjacency_list;
        std::unordered_map< VertexData, int, std::hash<VertexData> > vertex_position;
        std::vector<std::unordered_map<int, EdgeWeight>> edge_weights;

        EdgeWeight get_edge_weight(Vertex* v1, Vertex* v2);
        EdgeWeight get_edge_weight(int i, int j);
        EdgeWeight get_edge_weight(Vertex* v1, int j);
        EdgeWeight get_edge_weight(int i, Vertex* v2);  

};