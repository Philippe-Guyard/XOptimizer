// Copyright (c) 2021 XOptimzer Team.
// All rights reserved.

// Standard libraries
#include <chrono>
#include <random>

// External libraries
#include "../temp/graph.hpp"
#include "random_graph.hpp"

#define random_coordinate() -180.0+360.0*rng()/rng.max()
#define random_double(weight_limit) weight_limit*rng()/rng.max()

void RandomGraph::random_graph(
    int number_of_vertices, 
    double weight_limit = 6000.0, 
    int seed = -1)
{
    // Seeding the random number generator
    if (seed == -1)
    {
        seed = std::chrono::system_clock::now().time_since_epoch().count();
    }
    std::mt19937_64 rng(seed);

    // Generate random vertices
    num_vertices = number_of_vertices;
    vertices.resize(num_of_vertices);
    for (int i = 0; i < num_of_vertices; i++)
    {
        vertices[i] = Vertex(
                        VertexData(
                            {random_coordinate(), 
                            random_coordinate()}), 
                        i);
    }

    // Resize adjacency list
    adjacency_list.resize(num_vertices);
    for (int i = 0; i < num_vertices; i++)
    {
        adjacency_list[i].resize(num_of_vertices);
    }

    // Generate random edges
    num_edges = 0;
    edges.resize(num_edges);
    for (int i = 0; i < num_vertices; i++)
    {
        for (int j = i+1; j < number_of_vertices; j++)
        {
            if (rng()&1)
            {
                // Passing vertices by address
                Edge* new_edge_ptr = new Edge(
                                            std::make_pair(
                                                &vertices[i], 
                                                &vertices[j]), 
                                            random_double(weight_limit), 
                                            new_edge);
                // Passing edge by reference
                edges[new_edge++] = (*new_edge_ptr);
                adjacency_list[i][j] = adjacency_list[j][i] = new_edge_ptr;
            }
        }
    }

    //unordered_map construction
    for(int i = 0; i < num_vertices; i++)
    {
        vertex_position[vertex_data_array[i]] = i;
    }
}

void RandomGraph::random_complete_graph(
    int number_of_vertices,
    double weight_limit = 6000.0,
    int seed = -1)
{
    // Seeding the random number generator
    if (seed == -1)
    {
        seed = std::chrono::system_clock::now().time_since_epoch().count();
    }
    std::mt19937_64 rng(seed);

    // Generate random vertices
    num_vertices = number_of_vertices;
    vertices.resize(num_of_vertices);
    for (int i = 0; i < num_of_vertices; i++)
    {
        vertices[i] = Vertex(
                        VertexData(
                            {random_coordinate(), 
                            random_coordinate()}), 
                        i);
    }

    // Resize adjacency list
    adjacency_list.resize(num_vertices);
    for (int i = 0; i < num_vertices; i++)
    {
        adjacency_list[i].resize(num_of_vertices);
    }

    // Generate random edgesnum_edges = 0;
    edges.resize(num_edges);
    for (int i = 0; i < num_vertices; i++)
    {
        for (int j = i+1; j < number_of_vertices; j++)
        {
            // Passing vertices by address
            Edge* new_edge_ptr = new Edge(
                                        std::make_pair(
                                            &vertices[i], 
                                            &vertices[j]), 
                                        random_double(weight_limit), 
                                        new_edge);
            // Passing edge by reference
            edges[new_edge++] = (*new_edge_ptr);
            adjacency_list[i][j] = adjacency_list[j][i] = new_edge_ptr;
        }
    }

    //unordered_map construction
    for(int i = 0; i < num_vertices; i++)
    {
        vertex_position[vertex_data_array[i]] = i;
    }
}