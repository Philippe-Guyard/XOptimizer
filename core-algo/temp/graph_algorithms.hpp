#pragma once 

#include<iostream>
#include<algorithm>
#include<unordered_map>
#include<unordered_set>
#include<stack>

#include<vector>
#include<cstdio>
#include<assert.h>

namespace graph_algorithms{

std::vector<int> euler_tour(const std::vector<std::vector<int>> &adjacency_list );

double cost_of_path(const std::vector<std::vector<double>> &adjacency_matrix, std::vector<int> path);

std::vector<int> best_path_brute_force(const std::vector<std::vector<double>> &adjacency_matrix, std::vector<int> path);

std::vector<int> improve_path_locally(const std::vector<std::vector<double>> &adjacency_matrix, const std::vector<int> &path, int improvement_radius=8, int shift=0);

std::vector<int> best_path_held_karp(const std::vector<std::vector<double>> &adjacency_matrix, std::vector<int> path);
}