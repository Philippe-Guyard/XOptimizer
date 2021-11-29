#pragma once

#include "graph.hpp"
#include <list>
#include <vector>

class Matching{

public:
    Matching(std::vector<int> vertices, std::vector<std::pair<int,int>> solution);
    Matching(std::vector<int> vertices);
    void construct_tree(std::vector<int> blossom);
    void augment(int covered_vertex,  int exposed_vertex);
    void expand_tree(int covered_vectex, int exposed_vertex);
    void shrink_blossom(std::vector<int> blossom);
    void update_dual_cost();
    bool is_exposed(int vertex);
    //might happen that verteces are not adjecent due to dual problem constraint:
    bool is_adjacent(int u, int v);
    bool slack_edge(int u, int v);

    int n_vertices;
    int n_covered;
    std::vector<int> graph;
    std::vector<int> exposed;
    std::vector<int> forest;
    std::vector<int> root;
    std::vector<int> covered;
    std::vector<std::pair<int,int>> matching;
};


