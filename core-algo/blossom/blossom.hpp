//#pragma once

#include "../temp/graph/graph.hpp"
#include <list>
#include <vector>

class Matching{

public:
    //Constructor
    Matching(Graph *G);
    // Solves the minimum cost perfect matching
     std::pair<std::vector<std::pair<int,int>>, double > solve(const std::vector<double> & weight);

    // Does a heuristic matching from the class Graph
    void initial_matching();
    //Grows an alternating forest
    void grow();
    //Augments the matching when we find two even nods on different trees
    void augment(int u,  int v);
    // Extends the existing forrest using the existing edge with one even end and other matched not in tree
    void extend(int u,int v);
    //Expand the tree when an even vertex is adjoint to an unmatched vertex
    void expand(int u, bool expandBlocked = false);
    //Updates dual cost when the equality graph is exhausted
    void update_dual_cost();
    //Resets the alternating forest
    void reset();
    //Resets the whole matching
    void clear();

    // Checks whether there exists a path from u to v
    bool check_path(int u, int v);
    // Checks whether u and v are adjacent in the sense of blocked edges
    bool is_adjacent(int u, int v);
    // Checks whether the vertex is in the current matching
    bool is_matched(int u);
    // Checks whether the edge is available because of the slackeness condition
    bool is_blocked(int u, int v);
    // Checks whether the vertex is in any existing tree
    bool in_forest(int u);


    // Return the path from u to root of the tree
    std::vector<int> path_to_root(int u);
    // Finds the first common element of two paths
    int first_common(std::vector<int> path_u,std::vector<int> path_v);
    // Returns the difference between the edge cost and sum of vertices slack
    double slack_edge(int u, int v);
    // For a tree starting with a root t0 and vertices u and v return the path containing all three
    std::vector<int> fork_path(int u, int v, int t0);
    // Alternates the path with respect to the matching
    void alternate_path(std::vector<int> path);

    // Returns the index of a free blossom
    int get_free_blossom();
    //Destroys the blossom that opposes dual cost or when reseting the matching
    void destroy_blossom(int u);
    // Adds u as a free blossom index
    void add_free_blossom_index(int u);
    // creates a blossom and return the index
    int create_blossom(int u, int v);
    // Clears the blossom indeces vector
    void clear_blossom_indices();


    Graph G;
    std::list<int> forest_list;// unmatched vertices that are initial roots in the forest

    std::vector<int> outer; // current blossom node of a node
    std::vector< std::list<int> > deep; // lists of all nodes in the blossom
    std::vector< std::list<int> > shallow; // lists of all the first level nodes in the blossom
    std::vector<double> slack; // the vector of slacks of edges

    std::vector<int>parity; // 0 if vertex is even in the forest, 1 if odd, -1 if not in forest
    std::vector<std::vector<int>> adjecent; // vector of adjecent vertices
    std::vector<int> forest; // parent of the vertex
    std::vector<int> root; // root of a tree of every node in the forest (-1 if not in forest)
    // Initialize them to -1
    std::vector<int> visited; // vector of visited vertices
    std::vector<int> match; // match of every vertex (-1 if not matched)


    std::vector<int> tip; // Tip of the blossom
    std::vector<bool> active; // True iff the blossom is active
    std::vector<int> blocked; //A blossom can be blocked due to dual costs (cannot be expanded)
    std::vector<double> dual; //dual multipliers associated to the blossoms
    std::list<int> free_blossom; //List of free blossom indeces

    int n_vertices,n_edges;
    bool perfect;// True iff the current matching is perfect (updated in the grow proccess)
    std::vector<std::pair<int,int>> matching;

};



