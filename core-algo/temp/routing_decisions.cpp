#include<iostream>
#include<algorithm>
#include<unordered_map>
#include<unordered_set>
#include<stack>

#include<vector>
#include<cstdio>
#include<assert.h>

#include "graph.hpp"

std::vector< std::vector<int> > Graph::find_optimal_routing(
        const std::vector<Vertex*> &inventories_to_use,
        const std::vector<Vertex*> &clients_to_visit
    ){
    

    if(clients_to_visit.size() > inventories_to_use.size()){
        assert(false); // send some warning message

    }
    
    int num_clusters = inventories_to_use.size();

    std::vector< std::vector<Vertex*> > client_clusters = cluster_vertices(clients_to_visit, num_clusters);
    std::vector< std::pair<EdgeWeight, EdgeWeight> > centers = find_clusters_centers(client_clusters);

    std::vector< std::pair<int, int> > matching = match_inventories_to_clusters(inventories_to_use, centers); 

    std::vector< std::vector<int> > all_tours;
    for(auto& p : matching){

        client_clusters[p.second].push_back(inventories_to_use[p.first]);
        all_tours.push_back( TSP(client_clusters[p.second]) );

    }

    return all_tours;

}