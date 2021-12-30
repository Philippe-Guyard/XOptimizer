#include "graph.hpp"
#include "../../lib/blossom5-v2_05/PerfectMatching.h"
#include "../../blossom/blossom.hpp"

std::vector<std::pair<int,int>> Graph::perfect_mincost_matching(std::vector<int> vertex_indices){

    std::vector<std::pair<int,int>> solution;
    int n_vertices = vertex_indices.size();
    // by the assumption that graph is complete
    int n_edges = (n_vertices*(n_vertices-1))/2;

    // we are going to number the vertices 0,1,2....,n-1 based on the order they appear in vertices

    int vertex_i_index, vertex_j_index;
    PerfectMatching *pm = new PerfectMatching(n_vertices, n_edges);
    struct PerfectMatching::Options options;

    for(int i = 0; i<n_vertices; i++){
        for(int j = i+1; j<n_vertices; j++){
            vertex_i_index = vertex_indices[i];
            vertex_j_index = vertex_indices[j];
            pm->AddEdge(i,j,this->adjacency_list[vertex_i_index][vertex_j_index]->get_weight());
        }
    }

    pm->options = options;
    pm->Solve();

    int index1, index2;
    int v_index1, v_index2;
    for(index1 = 0; index1<n_vertices; index1++){
        index2 = pm->GetMatch(index1);
        if(index1 < index2){
            v_index1 = vertex_indices[index1];
            v_index2 = vertex_indices[index2];
            solution.push_back(std::make_pair(v_index1, v_index2));
        }
    }

    delete pm;

    return solution;
}



std::vector<std::pair<int,int>> Graph::heuristic_perfect_mincost_matching(std::vector<int> vertex_indices){

std::vector<std::pair<int,int>> solution;
std::vector<int> exposed_vertices = vertex_indices; // Exposed = Not in the matching M
std::vector<int> weight_neigbours;

int n_exposed = exposed_vertices.size();
int vertex_j_index, vertex_i_index;
int weight_j;
int min_neigbour;
int min_neigbour_index;

for(int i = 0; i < n_exposed; i++){
    // We are looping over exposed vertices and match them greedily to their exposed neighbour with minimum edge cost
    vertex_i_index = exposed_vertices[i];
    exposed_vertices.erase(exposed_vertices.begin()+i-i);

    for(int j = 0; j< n_exposed; j++)
        { // We loop over neighbours of vertex i to create a vector with their weights

          vertex_j_index = exposed_vertices[j];
          weight_j = this->adjacency_list[vertex_i_index][vertex_j_index]->get_weight();
          weight_neigbours.push_back(weight_j);
        }
    // Define the minimum neighbour of i and add the pair (vertex i, neighbour i) to the solution vector
    min_neigbour = min_element(weight_neigbours.begin(), weight_neigbours.end()) - weight_neigbours.begin();
    min_neigbour_index = exposed_vertices[min_neigbour];
    solution.push_back(std::make_pair(vertex_i_index, min_neigbour_index));

    // Updating the exposed vertices vector
    n_exposed --;
    exposed_vertices.erase(exposed_vertices.begin() + min_neigbour - 1);
    }

return solution;
    }

std::vector<std::pair<int,int>> Graph::perfect_mincost_matching(){

    std::vector<int> vertex_indices;
    int num_vertices = vertex_indices.size();
    VertexData vertex_data_array[num_vertices];
    for(int i = 0; i<num_vertices; i++){
        vertex_data_array[i] = this->vertices[vertex_indices[i]]->get_data();
    }
    std::vector<std::vector<EdgeWeight>> distances;
    for(int i = 0; i<num_vertices; i++){
        distances[i].push_back({});
        for(int j = 0; j < num_vertices; j++){
            distances[i].push_back(this->get_edge_weight(i,j));
        }
    }

    Graph new_graph = Graph(num_vertices, vertex_data_array, distances);


    // Initialize the Matching
    Matching M = Matching(this);
    int n_edges= this->num_edges;
    std::vector<double> weight;
    int weight_i;
    // Create a vector of weights to pass to the solve method
    std::pair< std::vector<std::pair<int,int>>, double > solution;

    for(int i = 0; i < n_edges; i++)
    {
        weight_i = get_edge(i)->get_weight();
        weight.push_back(weight_i);
    }
    // Solve the matching
    solution = M.solve(weight);
    // Extract the edges
    std::vector<std::pair<int,int>> edges = solution.first;

    return edges;
}




