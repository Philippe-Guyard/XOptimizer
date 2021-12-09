#include<iostream>
#include<unordered_map>
#include<set>
#include<vector>
#include<cstdio>
#include<assert.h>

#include "graph.hpp"

// Graph Class Implementation

Graph::Graph(){
    num_vertices = 0;
    num_edges = 0;

    // Add default constructor to vertex_position
}

Graph::Graph(int num_vertices, VertexData* vertex_data_array, std::vector<std::vector<EdgeWeight>> distances){

/**
 * Constructor of Graph.
 * 
 * PARAMETERS:
 * 
 * int num_vertices : Number of vertices in the graph
 * 
 * VertexData* vertex_data_array : An array of size num_vertices that contains the data of the vertices to be added.
 * 
 * vector<vector<EdgeWeight> distances : An num_vertices x num_vertices matrix with the distances between the vertices.
 * 
 * 
 * ASSUMPTIONS:
 * All data in vertex_data_array correspond to different locations.
 * 
 * The size of vertex_data_array is num_vertices.
 * 
 * Distances is ideally an num_vertices x num_vertices symmetric matrix.
 * 
 */

    this->num_vertices = num_vertices;
    num_edges = 0;

    for(int i=0; i<num_vertices; ++i){
        vertices.push_back(new Vertex(vertex_data_array[i], i));
    }

    // Resizing adjacency_list
    adjacency_list.resize(num_vertices);
    for(int i=0; i<num_vertices; ++i){
        adjacency_list[i].resize(num_vertices);
    }

    // we are ignoring the edge that goes from i to i
    for(int i=0; i<num_vertices; ++i){
        for(int j=i+1; j<num_vertices; ++j){

            // Passing vertices by address
            Edge* new_edge_ptr = new Edge(std::make_pair(vertices[i], vertices[j]), distances[i][j], num_edges);

            // Passing edge by reference
            edges.push_back( new_edge_ptr ); 
            num_edges++;

            adjacency_list[i][j] = adjacency_list[j][i] = new_edge_ptr;
        }
    }

    //unordered_map construction
    for(int i=0; i<num_vertices; ++i){
        vertex_position[vertex_data_array[i]] = i;
    }
}


Graph::~Graph(){

/**
 * Default Destructor
 * 
 */

    adjacency_list.clear();

    while( edges.size() > 0 ){
        Edge* edge_to_delete = edges.back();
        edges.pop_back();

        delete edge_to_delete;
    }

    while( vertices.size() > 0 ){
        Vertex* vertex_to_delete = vertices.back();
        vertices.pop_back();

        delete vertex_to_delete;
    }

}


void Graph::update_vertex_data(VertexData& data){
    return;
}

void Graph::add_vertex(VertexData& data, std::vector<std::pair<VertexData, EdgeWeight>>& distances){

/**
 * Adds a vertex to the graph with the corresponding edges.
 * 
 * PARAMETERS:
 * VertexData& data :
 * The data that should be stored in the vertex.
 * 
 * 
 * std::vector<std::pair<VertexData, EdgeWeight>>& distances : 
 * Contains the distances from this new vertex to all vertices already in the graph. The structure of pair<VertexData, EdgeWeight>
 * means distances[i].second is the distance of the new vertex to the vertex with data distances[i].first
 * 
 *  
 * RETURN:
 * void
 * 
 */

    // It is necessary to try to update the vertex before just adding it
    // e.g. repeated vertices


    /*== Maybe unecessary ==*/
    if( vertex_position.count(data) ){
        // repeated vertex
        this->update_vertex_data(data);
        return;
    }

    // Main code

    Vertex *new_vertex = new Vertex(data, num_vertices);
    
    vertices.push_back( new_vertex );

    adjacency_list.emplace_back();
    adjacency_list[num_vertices].resize(num_vertices);

    for(int i=0; i<num_vertices; ++i){
        int j = vertex_position[ distances[i].first ];
        Edge *new_edge = new Edge(std::make_pair(new_vertex, vertices[j]), distances[i].second, num_edges);

        adjacency_list[j].push_back( new_edge );
        adjacency_list[num_vertices][j] = new_edge;

        edges.push_back( new_edge );
        num_edges++;
    }

    Edge *trivial_edge = new Edge(std::pair<Vertex*, Vertex*> {new_vertex, new_vertex}, 0, num_edges);
    adjacency_list[num_vertices].push_back( trivial_edge );
    edges.push_back( trivial_edge );
    num_edges++;

    vertex_position[data] = num_vertices;
    num_vertices++;
}


int Graph::get_vertex_position(VertexData &d) const{

/**
 * A const member function to get the position of the vertex that has data d.
 * It will raise an error if d is not a valid data.
 * 
 * PARAMETERS:
 * VertexData &d : The data corresponding to the vertex that we want to find.
 * 
 * RETURN:
 * int : The position of the vertex with data d in vertices.
 * 
 */

    assert( vertex_position.count(d) );
    return vertex_position.at(d);
}

void Graph::swap_vertex_indices(int pos1, int pos2){

/**
 * Swap the indices of the vertices vertices[pos1] and vertices[pos2] and the corresponding graph structure.
 * 
 * PARAMETERS:
 * int pos1
 * 
 * int pos2
 * 
 * RETURN:
 * void
 * 
 */

    if(pos1==pos2) return;

    Vertex *vertex_1 = vertices[pos1];
    Vertex *vertex_2 = vertices[pos2];

    vertex_1->set_index(pos2);
    vertex_2->set_index(pos1);

    vertices[pos1] = vertex_2;
    vertices[pos2] = vertex_1;

    // Fixing adjacency list

    for(int i=0; i<num_vertices; ++i){

        if(i==pos1 || i==pos2) continue;

        Edge *edge1 = adjacency_list[i][pos1];
        Edge *edge2 = adjacency_list[i][pos2];

        adjacency_list[i][pos1] = adjacency_list[pos1][i] = edge2;
        adjacency_list[i][pos2] = adjacency_list[pos2][i] = edge1;

    }
}

void Graph::swap_vertex_to_last(int pos){
    /**
     * Swaps vertex vertices[pos] with the vertex in the last position of vertices.
     * 
     * PARAMETERS:
     * int pos
     * 
     * RETURN:
     * void
     */
    swap_vertex_indices(pos, num_vertices-1);
}

void Graph::delete_vertex(VertexData& data){

    /**
     * Deletes the vertex that carries the data given as parameter. Also delete the edges connected to this vertex and
     * mantains the graph structure.
     * 
     * PARAMETERS:
     * VertexData& data :
     * Data that specifies which vertex will be deleted.
     * 
     * RETURN:
     * void
     * 
     */

    // prevent deletion of vertices that don't exist
    assert( vertex_position.count(data) );

    int pos = vertex_position[data];
    swap_vertex_to_last(pos);

    std::vector<Edge*> edges_to_delete;

    // Fixing adjacency_list

    adjacency_list.pop_back();

    for(int i=0; i<num_vertices-1; ++i){
        edges_to_delete.push_back(adjacency_list[i][num_vertices-1]);
        adjacency_list[i].pop_back();
    }

    // removing the edges from edges

    for(int i=0; i<edges_to_delete.size(); ++i){

        Edge *edge_to_delete = edges_to_delete[i];
        int position_edge_to_delete = edge_to_delete->get_index();

        std::swap(edges[position_edge_to_delete], edges[num_edges-edges_to_delete.size()+i]);
    }
    
    for(int i=0; i<edges_to_delete.size(); ++i){
        edges.pop_back();
    }

    for(int i=0; i<edges_to_delete.size(); ++i){
        Edge *edge_to_delete = edges_to_delete[edges_to_delete.size()-1];
    
        edges_to_delete.pop_back();

        delete edge_to_delete;
    }

    num_edges -= edges_to_delete.size();
    num_vertices--;

}


// get edge member functions

EdgeWeight Graph::get_edge_weight(int i, int j) const{
/**
 * Returns the weight of the edge between i and j.
 * 
 * PARAMETERS:
 * int i
 * 
 * int j
 * 
 * RETURN:
 * 
 * EdgeWeight : distance between i and j
 * 
 */

    if( !(i>=0 && i<num_vertices) ){
        throw std::exception();
    }
    if( !(j>=0 && j<num_vertices)){
        throw std::exception();
    }

    if(i==j){
        return (EdgeWeight) 0;
    }

    return adjacency_list[i][j]->get_weight();

}

EdgeWeight Graph::get_edge_weight(VertexData di, int j) const{
/**
 * Returns the weight of the edge between i and j. Here, i corresponds to the
 * vertex with data di.
 * 
 * PARAMETERS:
 * VertexData di
 * 
 * int j
 * 
 * RETURN:
 * 
 * EdgeWeight : distance between i and j
 * 
 */

    return get_edge_weight( get_vertex_position(di), j);
}

EdgeWeight Graph::get_edge_weight(int i, VertexData dj) const{
/**
 * Returns the weight of the edge between i and j. Here, j corresponds to the
 * vertex with data dj.
 * 
 * PARAMETERS:
 * int i
 * 
 * VertexData dj
 * 
 * RETURN:
 * 
 * EdgeWeight : distance between i and j
 * 
 */

    return get_edge_weight(i, get_vertex_position(dj));
}

EdgeWeight Graph::get_edge_weight(VertexData di, VertexData dj) const{
/**
 * Returns the weight of the edge between i and j. Here, i,j correspond to the
 * vertices with data di,dj.
 * 
 * PARAMETERS:
 * VertexData di
 * 
 * VertexData dj
 * 
 * RETURN:
 * 
 * EdgeWeight : distance between i and j
 * 
 */

    return get_edge_weight(get_vertex_position(di), get_vertex_position(dj));
}

// sort edges member function

void Graph::sort_edges(){
/**
 * Sorts the edges inside the edges data attribute in ascending weight. It makes
 * sure that the indices of vertices are adjusted accordingly.
 * 
 * PARAMETERS:
 * void
 * 
 * RETURN:
 * void
 * 
 */

    std::sort(edges.begin(), edges.end(), [](Edge* ptr1, Edge* ptr2) {return ptr1->get_weight() < ptr2->get_weight();});
    for(int i=0; i<num_edges; ++i){
        edges[i]->set_index(i);
    }

}


std::vector<std::vector<double>> Graph::build_adjacency_matrix()    const{

    std::vector< std::vector<double> > adjacency_matrix_return(num_vertices);

    for(int i=0; i < num_vertices; ++i){
        adjacency_matrix_return[i].resize(num_vertices);
    }

    for(int i=0; i<num_vertices; ++i){
        for(int j=i; j<num_vertices; ++j){
            
            adjacency_matrix_return[i][j] = adjacency_matrix_return[j][i] = get_edge_weight(i, j);
            
        }
    }

    return adjacency_matrix_return;

}
