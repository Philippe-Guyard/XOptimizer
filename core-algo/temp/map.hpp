#include "../src/graph.hpp"

class Map{

    public:

        Map(int num_vertices, VertexData* vertex_data_array, std::vector<std::vector<std::pair<int, EdgeWeight>>> adjacency_list);

    protected:

        int num_vertices;
        int num_edges;

        std::vector<Vertex*> vertices;
        std::vector<Edge*> edges;
        std::vector<std::vector<Edge*>> adjacency_list;
        std::unordered_map< VertexData, int, std::hash<VertexData> > vertex_position;
        std::vector<std::unordered_map<VertexData, EdgeWeight, std::hash<VertexData>>> edge_weights;




};