
// EDGES[i][j] = *Edge[Vertex indiced i] and

using EdgeWeight unsigned long double

class Edge{
    private:
        std::pair<Vertex*, Vertex*> vertices;
        EdgeWeight weight;

    public:
        Edge(Vertex &v1; Vertex &v2, EdgeWeight weight);
        Edge();
        void set_weight(EdgeWeight weight);
        void set_vertices(std::pair<Vertex* v1, Vertex* v2>);
        std::pair<Vertex*, Vertex*> get_vertices();
        EdgeWeight get_weight();
}

class VertexData{}

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


