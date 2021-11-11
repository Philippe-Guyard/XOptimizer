#include<iostream>

#include<unordered_map>
#include<vector>
#include<cstdio>

#include "graph.hpp"
#include "disjointset.hpp"

DisjointSet:: DisjointSet(int n){
    for (int i = 0; i < n; i++){
        parent[i] = i;
        rank[i] = 0;
    }
};

int DisjointSet::find(int x) {
    return parent[x] < 0 ? x : parent[x] = find(parent[x]); 
}

void DisjointSet::Union(int x, int y){
    x = find(x);
    y = find(y);
    if (x != y){
        if (rank[x] < rank[y]){
            std::swap(x, y);
        }
        parent[y] = x;
        if (rank[x] == rank[y]){
            rank[x]++
        }
    }
    return;
};