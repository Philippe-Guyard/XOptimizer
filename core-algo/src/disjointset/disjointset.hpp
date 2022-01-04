#include<vector>
#include<cstdio>

class DisjointSet{
public:
    DisjointSet(int n);
    int find(int x);
    void Union(int x, int y);
private:
    std::vector<int> parent;
};