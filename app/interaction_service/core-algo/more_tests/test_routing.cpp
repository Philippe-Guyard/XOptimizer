#include <bits/stdc++.h>
#include "./graph/graph.hpp"

using namespace std;

void cout_vector(vector<int> vec){
    for(auto x : vec){
        cout << x << " ";
    }
    cout<<endl;
}


Graph random_graph(int N=9)
{

Graph g = Graph();

for(int i=0; i<N; ++i){
    
    //cout << "Creating Graph loop "<< i << endl;

    int type = (i >= N-4);

    VertexData vdata = VertexData({i,i}, type);

    vector< pair<VertexData, double> > dis(i);
    for(int j=0; j<i; ++j){
        dis[j] = {VertexData({j,j}), max(1, rand())/(double) 1000};
    }

    g.add_vertex(vdata, dis);
}

return g;

}

void test_1(){

    int N = 15;
    vector<int> clients;
    for(int i=0; i<N-1; ++i)
        clients.push_back(i);

    Graph g = random_graph(N);

    cout_vector( g.optimal_routing_optimized( 7, {1,4,8}) );

}

void test_2(){

    int N = 15;
    vector<int> clients;

    for(int i=0; i<N-3; ++i)
        clients.push_back(i);

    Graph g = random_graph(N);

    for(auto v : g.optimal_routing({N-3, N-2, N-1}, {}))
        cout_vector(v);


}

void test_3(){

    int N = 15;

    vector<int> to_cluster = {1,3,5,7,9,10,11,12};

    Graph g = random_graph(N);
    for(auto v : g.cluster_vertices(to_cluster, 3) )
        cout_vector(v);

}

void test_4(){

    int N = 15;
    Graph g = random_graph(N);

    for(auto v : g.optimal_routing_all())
        cout_vector(v);   

}

void test_5(int N){

    Graph g = random_graph(N);

    cout << "Not optimized" << endl;
    for(auto v : g.optimal_routing_all())
        cout_vector(v);

    cout << "Optimized" << endl;
    for(auto v : g.optimal_routing_all_optimized())
        cout_vector(v);   

}

void test_6(int d){

    int N = 30;
    Graph g = random_graph(N);

    std::vector<int> path;

    for(int i=0; i <= d; ++i){
        path.push_back(i);
    }

    cout_vector( g.best_path_held_karp(path));
    //cout_vector( g.best_path_brute_force(path));
    
}


int main(){
    
    srand(time(0));

    int N;
    cin>>N;
    test_5(N);
}