#include<iostream>

#include<unordered_map>
#include<vector>
#include<cstdio>


class DisjointSet{
public:
    DisjointSet(int n);
    int find(int x);
    void Union(int x, int y);
private:
    std::unordered_map<int, int> parent;
    std::unordered_map<int, int> rank;
};