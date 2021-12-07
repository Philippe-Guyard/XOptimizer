// Copyright (c) 2021 XOptimzer Team.
// All rights reserved.

// Standard libraries
#include <utility>                  // std::pair, std::make_pair
#include <chrono>                   // std::chrono::system_clock::now().time_since_epoch().count()
#include <random>                   // std::mt19937_64
#include <algorithm>                // std::random_shuffle, std::min
#include <vector>                   // std::vector
#include <limits>                   // std::numeric_limits
#include <queue>                    // std::priority_queue
#include <stdexcept>                // std::invalid_argument

// External libraries
#include "random_graph.hpp"
#include "../../lib/blossom5-v2_05/PerfectMatching.h"
#include "../../lib/blossom5-v2_05/GEOM/GeomPerfectMatching.h"

/**
 * Initialize to a random undirected weighted graph, with given density and weight limit.
 * 
 * @param {int}         number_of_vertices  : Number of vertices.
 * @param {EdgeWeight}  weight_limit        : Upper limit for ranom weight. The lower bound is set by default to 0. Default set to be 6000.0
 * @param {double}      density             : Density of random graph from 0 to 1, e.g. 0 corresponds to a tree, and 1 corresponds to complete graph. Default set to be 0.5
 * @param {int}         seed                : Seed fed into random number generator. Default set to be the EPOCH time at runtime.
 */
void RandomGraph::random_graph(
    int number_of_vertices, 
    EdgeWeight weight_limit = 6000.0, 
    double density = 0.5, 
    int seed = -1)
{
    // Seeding the random number generator
    if (seed == -1)
    {
        seed = std::chrono::system_clock::now().time_since_epoch().count();
    }
    std::mt19937_64 rng(seed);
    std::uniform_real_distribution<double> random_coordinate(-180.0, 180.0);
    std::uniform_real_distribution<long double> random_weight(0.0, weight_limit);

    // Generate random vertices
    VertexData* vertex_data_array = new VertexData[number_of_vertices];
    std::vector<std::vector<EdgeWeight> > distances(number_of_vertices);
    for (int i = 0; i < number_of_vertices; i++)
    {
        vertex_data_array[i] = VertexData({random_coordinate(rng), random_coordinate(rng)});
        distances[i].assign(number_of_vertices, std::numeric_limits<EdgeWeight>::max());
    }

    // Build underlying random spanning tree
    // Ref: Alexey S. Rodionov and Hyunseung Choo, On Generating Random Network Structures: Trees, ICCS 2003, LNCS 2658, pp. 879-887, 2003.
    std::vector<int> temp(number_of_vertices),  
        added(number_of_vertices);
    for (int i = 0; i < num_vertices; i++) temp[i] = i;
    std::shuffle(temp.begin(), temp.end(), rng);
    added[0] = temp[0];
    for (int count = 1; count < num_vertices; count++)
    {
        int index = rng()%count,
            v = temp[count],
            u = added[index];
        added[count] = v;
        distances[u][v] = distances[v][u] = random_weight(rng);
    }

    // Generate additional random edges
    std::bernoulli_distribution bern_dist(density);
    for (int i = 0; i < num_vertices; i++)
    {
        for (int j = i+1; j < num_vertices; j++)
        {
            if (bern_dist(rng) && adjacency_list[i][j] == nullptr)
            {
                distances[i][j] = distances[j][i] = random_weight(rng);
            }
        }
    }

    Graph(number_of_vertices, vertex_data_array, distances);
    delete vertex_data_array;
}

/**
 * Generate a random undirected weighted graph, and compute the cost of minimum 
 * spanning tree using Prim's algorithm. The result is then compared with official
 * method implemented and provided in Graph class.
 * 
 * Independent implementation of Minimum Spanning Tree algorithm, for testing purpose.
 * Here, Prim's algorithm is chosen.
 * 
 * @param {int}         number_of_vertices  : Number of vertices.
 * @param {EdgeWeight}  weight_limit        : Upper limit for ranom weight. The lower bound is set by default to 0. Default set to be 6000.0
 * @param {double}      density             : Density of random graph from 0 to 1, e.g. 0 corresponds to a tree, and 1 corresponds to complete graph. Default set to be 0.5
 * @param {int}         seed                : Seed fed into random number generator. Default set to be the EPOCH time at runtime.
 * 
 * @return {pair<EdgeWeight, EdgeWeight>} A pair of EdgeWeigt {expected_total_cost, computed_total_cost}, where expected_total_cost is computed by Prim's algorithm, and the computed_total_cost is computed by official method.
 */
std::pair<EdgeWeight, EdgeWeight> RandomGraph::minimum_spanning_tree_test(
    int number_of_vertices,
    EdgeWeight weight_limit = 6000.0, 
    double density = 0.5, 
    int seed = -1)
{
    // Seeding the random number generator
    if (seed == -1)
    {
        seed = std::chrono::system_clock::now().time_since_epoch().count();
    }

    if (density < 0.0 || density > 1.0)
    {
        density = 0.5;
    }

    // randomly initialize the graph
    random_graph(number_of_vertices, 
                    weight_limit, 
                    density, 
                    seed);
    
    // Actual Prim's algorithm implementation
    std::vector<bool> added(number_of_vertices);
    std::vector<EdgeWeight> final_cost(number_of_vertices, std::numeric_limits<EdgeWeight>::max());
    final_cost[0] = 0;

    std::priority_queue<std::pair<EdgeWeight, int>,
                        std::vector<std::pair<EdgeWeight, int> >,
                        std::greater<std::pair<EdgeWeight, int> >
                        > queue;
    queue.push({0, 0});

    EdgeWeight expected_total_cost = 0.0,
                computed_total_cost = 0.0;
    
    // If the node is node not yet added to the minimum spanning tree add it, and increment the cost.
    while(!queue.empty())
    {
        std::pair<EdgeWeight, int> u = queue.top();
        queue.pop();
        int index = u.second;

        if(!added[index])
        {
            final_cost[index] = u.first;
            expected_total_cost += u.first;
            added[index] = true;

            // Iterate through all the nodes adjacent to the node taken out of priority queue.
            // Push only those nodes (weight,node) that are not yet present in the minumum spanning tree.
            for(int i = 0; i < number_of_vertices; i++)
            {
                if(adjacency_list[index][i] != nullptr && 
                    !added[i] && 
                    u.first + (*adjacency_list[index][i]).get_weight() < final_cost[i])
                {
                    queue.push({(*adjacency_list[index][i]).get_weight(),
                                i});
                }
            }
        }
    }

    std::vector<Edge*> minimum_spanning_tree_kruskal = min_spanning();
    for (Edge* e : minimum_spanning_tree_kruskal)
    {
        computed_total_cost += e->get_weight();
    }

    return {expected_total_cost, computed_total_cost};
}

std::pair<EdgeWeight, EdgeWeight> RandomGraph::maximal_mincost_matching_test(
    std::vector<int>& vertex_indices)
{
    EdgeWeight computed_solution = 0, 
                expected_solution = 0;
    
    bool odd_num_vertices = false;
    std::vector<std::pair<VertexData, EdgeWeight> > distances(num_vertices);
    for (int i = 0; i < num_vertices; i++)
    {
        distances[i] = {vertices[i]->get_data(), std::numeric_limits<EdgeWeight>::max()};
    }
    VertexData dummy = VertexData();

    if (vertex_indices.size() & 1)
    /* 
    If the number of vertices is odd, we add another dummy vertex with weight of edges to
    other vertices to be infinity.
    */
    {
        odd_num_vertices = true;
        add_vertex(dummy, distances);
        vertex_indices.push_back(num_vertices - 1);
    }
    int number_of_vertices = vertex_indices.size(),
        number_of_edges = number_of_vertices * (number_of_vertices - 1) >> 1;
    
    PerfectMatching* perfect_matching = new PerfectMatching(number_of_vertices, number_of_edges);
    for (int i = 0; i < number_of_vertices; i++)
    {
        for (int j = i+1; j < number_of_vertices; j++)
        {
            perfect_matching->AddEdge(i, j, get_edge_weight(vertex_indices[i], vertex_indices[j]));
        }
    }
    
    struct PerfectMatching::Options options;
    perfect_matching->options = options;
    perfect_matching->Solve();

    for (int ind1 = 0; ind1 < number_of_vertices; ind1++)
    {
        int ind2 = perfect_matching->GetMatch(ind1);
        if (ind1 < ind2 && 
                (!odd_num_vertices || 
                ind2 < num_vertices - 1)
            )
        {
            expected_solution += get_edge_weight(vertex_indices[ind1], vertex_indices[ind2]);
        }
    }
    delete perfect_matching;
    
    if (odd_num_vertices)
    {
        delete_vertex(dummy);
        vertex_indices.pop_back();
    }
    
    std::vector<std::pair<int, int> > computed_solution_edges = 
        perfect_mincost_matching(vertex_indices);
    for (std::pair<int, int> e : computed_solution_edges)
    {
        computed_solution += get_edge_weight(e.first, e.second);
    }
    
    return {expected_solution, computed_solution};
}

std::EdgeWeight RandomGraph::random_tsp(
    int number_of_vertices,
    EdgeWeight weight_limit = 6000.0,
    int seed = -1, 
    bool symmetric = true)
{   
    // Seeding the random number generator
    if (seed == -1)
    {
        seed = std::chrono::system_clock::now().time_since_epoch().count();
    }
    std::mt19937_64 rng(seed);
    std::uniform_real_distribution<EdgeWeight> random_coordinate(-180.0, 180.0);
    std::uniform_real_distribution<EdgeWeight> random_weight(0.0, weight_limit);

    // Generate random data for random graph
    VertexData* vertex_data_array = new VertexData[number_of_vertices];
    std::vector<std::vector<EdgeWeight> > distances(number_of_vertices * number_of_vertices);
    for (int i = 0; i < number_of_vertices; i++)
    {
        vertex_data_array[i] = VertexData({random_coordinate(rng), random_coordinate(rng)});
    }

    // Generate random_permutation
    std::vector<int> permu(number_of_vertices);
    std::vector<EdgeWeight> alpha(number_of_vertices);
    EdgeWeight gamma = std::numeric_limits<EdgeWeight>::max(), optimal_cost = 0, d;
    int u, v;
    for (int i = 0; i < number_of_vertices; i++)
    {
        permu[i] = i;
        alpha[i] = random_weight(rng);
        gamma = std::min(gamma, 2*alpha[i]);
    }
    std::random_shuffle(permu.begin(), permu.end());
    
    std::uniform_real_distribution<EdgeWeight> random_pertubation(0.0, gamma);
    for (int u : permu)
    {
        for (int v : permu)
        {
            if (u < v)
            {
                distances[u][v] = distances[v][u] = alpha[u] + alpha[v] + random_pertubation(rng);
            }
        }
    }
    for (int i = 0; i < number_of_vertices - 1; i++)
    {
        u = permu[i], v = permu[i+1], d = alpha[u] + alpha[v];
        distances[u][v] = distances[v][u] = d;
        optimal_cost += d;
    }
    u = permu[0], v = permu[number_of_vertices - 1], d = alpha[u] + alpha[v];
    distances[u][v] = distances[v][u] = d;
    optimal_cost += d; 

    Graph(number_of_vertices, vertex_data_array, distances);
    delete vertex_data_array;

    return optimal_cost;
}

void RandomGraph::random_graph_with_eulerian_circuits(
    int number_of_vertices, 
    EdgeWeight weight_limit = 6000.0, 
    double density = 0.5, 
    int seed = -1)
{
    if (number_of_vertices < 2)
    {
        throw std::invalid_argument("Number of vertices is insufficient.");
    }
    
    // Seeding the random number generator
    if (seed == -1)
    {
        seed = std::chrono::system_clock::now().time_since_epoch().count();
    }
    std::mt19937_64 rng(seed);
    std::uniform_real_distribution<double> random_coordinate(-180.0, 180.0);
    std::uniform_real_distribution<long double> random_weight(0.0, weight_limit);

    // Generate random vertices
    VertexData* vertex_data_array = new VertexData[number_of_vertices];
    std::vector<std::vector<EdgeWeight> > distances(number_of_vertices);
    for (int i = 0; i < number_of_vertices; i++)
    {
        vertex_data_array[i] = VertexData({random_coordinate(rng), random_coordinate(rng)});
        distances[i].assign(number_of_vertices, std::numeric_limits<EdgeWeight>::max());
    }

    // Build underlying random spanning tree
    // Ref: Alexey S. Rodionov and Hyunseung Choo, On Generating Random Network Structures: Trees, ICCS 2003, LNCS 2658, pp. 879-887, 2003.
    std::vector<int>
        temp(number_of_vertices),  
        added(number_of_vertices),  
        deg(number_of_vertices), 
        odd_deg_vertices(number_of_vertices);
    int cnt = 0;
    for (int i = 0; i < num_vertices; i++) temp[i] = i;
    std::shuffle(temp.begin(), temp.end(), rng);
    added[0] = temp[0];
    for (int count = 1; count < num_vertices; count++)
    {
        int index = rng()%count,
            v = temp[count],
            u = added[index];
        added[count] = v;
        deg[u]++, deg[v]++;
        distances[u][v] = distances[v][u] = random_weight(rng);
    }

    for (int i = 0; i < number_of_vertices; i++)
    {
        if (deg[i] & i)
        {
            odd_deg_vertices[cnt++] = i;
        }
    }

    // Generate additional random edges
    std::bernoulli_distribution bern_dist(density);
    while (cnt)
    {
        std::uniform_int_distribution<int> random_vertices(0, cnt-1);
        int u = random_vertices(rng), v = random_vertices(rng);
        while (u == v)
        {
            v = random_vertices(rng);
        }

        u = odd_deg_vertices[u],
        v = odd_deg_vertices[v];

        if (distances[u][v] == std::numeric_limits<EdgeWeight>::max())
        {
            distances[u][v] = distances[v][u] = random_weight(rng);
            deg[u]++, deg[v]++;
        }
        else
        {
            distances[u][v] = distances[v][u] = random_weight(rng);
            deg[u]--, deg[v]--;
        }

        std::swap(odd_deg_vertices[u], odd_deg_vertices[cnt-1]);
        cnt--;
        std::swap(odd_deg_vertices[v], odd_deg_vertices[cnt-1]);
        cnt--;
    }

    Graph(number_of_vertices, vertex_data_array, distances);
    delete vertex_data_array;
}