#include<iostream>
#include<algorithm>
#include<unordered_map>
#include<unordered_set>
#include<stack>

#include<vector>
#include<cstdio>
#include<assert.h>

#include "graph_algorithms_temp.cpp"

int main(){
    using namespace std;
    vector<vector<int>> adjacency_list;
    adjacency_list.resize(4);

    adjacency_list[0] = {1,3};
    adjacency_list[1] = {0,2};
    adjacency_list[2] = {1,3};
    adjacency_list[3] = {2,0};


    for(auto i : euler_tour(adjacency_list)){
        cout << i << "\n";
    }

}
