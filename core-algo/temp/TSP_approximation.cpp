#include<iostream>
#include<algorithm>
#include<unordered_map>
#include<unordered_set>
#include<stack>

#include<vector>
#include<cstdio>
#include<assert.h>

#include "graph.hpp"

std::vector<int> Graph::euler_tour(const std::vector<Edge*>& smaller_graph) const{
/**
 * Returns an Eulerian Cycle passing through all edges in smaller_graph.
 * 
 * Implementation inspired by:
 * https://cp-algorithms.com/graph/euler_path.html
 * 
 */


    int n = num_vertices;


    // Make Adjacency List for the smaller graph
    std::vector< std::vector<int> > smaller_graph_adjacency_list(n);
    for(int i=0; i<n; ++i){
        smaller_graph_adjacency_list.resize(n);
    }

    for(const auto &e : smaller_graph){
        int x1 = (e->get_vertices()).first->get_index();
        int x2 = (e->get_vertices()).second->get_index();

        smaller_graph_adjacency_list[x1][x2]++;
        smaller_graph_adjacency_list[x2][x1]++;
    }

    std::stack<int> st;
    st.push(0);

    std::vector<int> eulerian_cycle;

    while( !st.empty() ){
        int v = st.top();
        int u;

        for(u=0; u<n; ++u){
            if(smaller_graph_adjacency_list[v][u]){

                smaller_graph_adjacency_list[v][u]--;
                smaller_graph_adjacency_list[u][v]--;

                st.push(u);
                break;
            }
        }

        if(u==n){
            eulerian_cycle.push_back(v);
            st.pop();
        }
    }

    return eulerian_cycle;
}

std::vector<int> Graph::TSP(){

    std::vector<Edge*> MST = min_spanning();

    int n = num_vertices;

    // Vector with the degrees of vertices in MST
    std::vector<int> deg(n, 0);

    for(const auto &e : MST){
        deg[ (e->get_vertices()).first->get_index() ]++;
        deg[ (e->get_vertices()).second->get_index() ]++;
    }


    // We get the vertices with odd degrees
    std::vector<int> odd_degree_vertices;

    for(int i=0; i<n; ++i){
        if( deg[i]%2 == 1 ){
            odd_degree_vertices.push_back(i);
        }
    }

    std::vector< std::pair<int,int> > min_cost_matching = perfect_mincost_matching(odd_degree_vertices);

    // Tactical renaming
    std::vector<Edge*> &christofidesGraph = MST;

    for(const auto &match : min_cost_matching){
        christofidesGraph.push_back( adjacency_list[match.first][match.second] );
    }

    std::vector<int> eulerPath = euler_tour(christofidesGraph);

    std::vector<bool> chosen(n, false);
    std::vector<int> finalPath;

    for(const auto& v : eulerPath){
        if( chosen[v] ){
            continue;
        }

        chosen[v] = true;
        finalPath.push_back(v);
    }

    return finalPath;
}