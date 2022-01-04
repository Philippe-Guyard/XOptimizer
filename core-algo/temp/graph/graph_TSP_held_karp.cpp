#include "graph.hpp"
#include <climits>
#include <cstring>
#include <iostream>

std::vector<int> Graph::TSP_held_karp(){
    std::vector<int> path;
    std::pair<EdgeWeight, int> min_costs[1<<(num_vertices-1)][num_vertices];
    for (int mask = 0; mask < (1<<(num_vertices-1)); mask++)
    {
        for (int last = 0; last < num_vertices; last++)
        {
            min_costs[mask][last] = {
                std::numeric_limits<EdgeWeight>::max(), 
                -1};
        }
    }

    for (int visited = 1; visited < (1<<(num_vertices-1)); visited++)
    {
        for (int last = 0; last < num_vertices-1; last++)
        {
            if (!((visited>>last)&1)) continue;
            if (visited == 1 << last)
            {
                min_costs[visited][last] = {
                    get_edge_weight(num_vertices-1, last), 
                    num_vertices-1
                };
            }
            else
            {
                int prev_visited = visited ^ 1<<last;
                for (int prev = 0; prev < num_vertices-1; prev++)
                {
                    if (!((visited>>prev)&1)) continue;
                    EdgeWeight possible_cost = 
                        min_costs[prev_visited][prev].first + 
                        get_edge_weight(last, prev);
                    if (possible_cost < min_costs[visited][last].first)
                    {
                        min_costs[visited][last] = {possible_cost, prev};
                    }
                }
            }
        }
    }
    EdgeWeight min_total_cost = std::numeric_limits<EdgeWeight>::max();
    int last_vertex, mask = (1<<(num_vertices-1))-1;
    for (int last = 0; last < num_vertices-1; last++)
    {
        EdgeWeight possible_cost = 
            min_costs[mask][last].first + 
            get_edge_weight(last, num_vertices-1);
        if (possible_cost < min_total_cost)
        {
            last_vertex = last;
            min_total_cost = possible_cost;
        }
    }
    while (mask)
    {
        int prev_vertex = min_costs[mask][last_vertex].second;
        mask ^= 1<<last_vertex;
        path.push_back(last_vertex);
        last_vertex = prev_vertex;
    }
    path.push_back(num_vertices-1);
    return path;
}