#include<iostream>
#include<unordered_map>
#include<set>
#include<vector>
#include "blossom.hpp"


Matching::Matching(std::vector<int> vertices, std::vector<std::pair<int,int>> solution){

    n_covered = solution.size();
    n_vertices = vertices.size();
    matching = solution;
    graph = vertices ;
    for(int i = 0; i<n_covered; i++)
    {
        this->covered.push_back(solution[i].first);
        this->covered.push_back(solution[i].second);
    }

};
Matching::Matching(std::vector<int> vertices){

    n_covered = 0;
    n_vertices = vertices.size();
    graph = vertices ;

};

bool Matching::is_adjacent(int u, int v){

    return (not slack_edge(u, v));
}

