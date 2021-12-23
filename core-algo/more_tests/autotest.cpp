#include "graph.hpp"
#include "Vec3.hpp"
#include "graph_algorithms.hpp"

#include <bits/stdc++.h>

using namespace std;

#define TEST1 0 
#define TEST2 0
#define TEST3 0
#define TEST4 0
#define TEST5 0
#define TEST6 0
#define TEST7 0
#define TEST8 1

Graph random_graph(int N=9){

    srand(time(0));

    Graph g = Graph();

    for(int i=0; i<N; ++i){
        VertexData vdata = VertexData({i,i});

        vector< pair<VertexData, double> > dis(i);
        for(int j=0; j<i; ++j){
            dis[j] = {VertexData({j,j}), max(1, rand())/(double) 1000};
        }

        g.add_vertex(vdata, dis);
    }

    return g;
}

Graph graph_example(int N=15){

    Graph g = Graph();

    for(int i=0; i<N; ++i){
        VertexData vdata = VertexData({i,i});

        vector< pair<VertexData, double> > dis(i);
        for(int j=0; j<i; ++j){
            dis[j] = {VertexData({j,j}), i*j};
        }

        g.add_vertex(vdata, dis);
    }

    return g;
}

void test_add_vertex(){

    int N = 15;

    Graph g = graph_example(N);

    for(int i=3; i<=5; ++i){
        for(int j=6; j<=8; ++j){
            
            if( g.get_edge_weight(i,j) != i*j ){
                cout << i << ", " << j << ": " << g.get_edge_weight(i,j) << endl;
                throw 1;
            }
        }
    }
}

void test_delete_vertex(){

    int N = 15;

    Graph g = graph_example(N);

    if(g.get_num_vertices() != N){
        cout << "Wrong num vertices in 0th iteration" << endl;
        throw 1;
    }

    for(int i=0; i<N; ++i){

        VertexData vdata = VertexData({i,i});
        g.delete_vertex( vdata );

        if(g.get_num_vertices() != N-i-1){
            cout << "Wrong num vertices in " << i+1 << "th iteration" << endl;
        }

        for(int j=0; j <= i; ++j){
            VertexData vdata1 = VertexData({j,j});
            
            if(g.get_vertex_position(vdata1) != -1){
                cout << "Did not delete the vertex " << j << endl;
                throw 1;
            }

        }

        for(int j=i+1; j < N; ++j){
            VertexData vdata1 = VertexData({j,j});
            
            if(g.get_vertex_position(vdata1) == -1){
                cout << "Did not find the vertex " << j << endl;
                throw 1;
            }

        }
    }

}

void test_graph_destructor(){

    int N = 100;
    int k;

    for(int i=0; i < N; ++i){
        Graph g = graph_example();
        k = g.get_num_vertices();
    }

}

void test_TSP_approximation(){

    int N = 9;
    Graph g = graph_example(N);
    
    vector<int> res = g.TSP();

    for(auto i: res){
        cout << i <<" ";
    }

    cout << "Cost of path: " << g.cost_of_path(res) << endl;
    cout << endl;

}

// TEST 5
void test_brute_force_path(){

    int N = 11;

    //Graph g = graph_example(N);
    Graph g = random_graph(N);

    vector<int> arange;
    for(int i=0; i<N; ++i){
        arange.push_back(i);
    }

    vector<int> res = g.best_path_brute_force(arange);

    for(int i=0; i<N; ++i){
        cout << res[i] << " ";
    }

    cout << "Cost of path: " << g.cost_of_path(res) << endl;
    cout << endl;

}

void test_optimal_routing(){

    int N = 10;

    Graph g = random_graph(N);

    int inventory_index = 0;
    vector<int> client_indices;

    for(int i=1; i<N; ++i){
        client_indices.push_back(i);
    }

    vector<int> optimal_routing = g.optimal_routing(inventory_index, client_indices);

    for(int i=0; i<N; ++i){
        cout << optimal_routing[i] << " ";
    }


    cout << "Cost of path: " << g.cost_of_path(optimal_routing) << endl;
    
    if( N <= 10)
        cout << "Cost of best path: " << g.cost_of_path( g.best_path_brute_force(optimal_routing) );


}

//TEST 7
void test_improve_path_locally(){

    int N = 5000;
    Graph g = random_graph(N);

    vector<int> trivial_path;
    for(int i=0; i<N; ++i){
        trivial_path.push_back(i);
    }

    cout << "Cost trivial path: " << g.cost_of_path(trivial_path) << endl;

    trivial_path = g.TSP();
    cout << "Cost of TSP: " << g.cost_of_path(trivial_path) << endl;

    trivial_path = g.improve_path_locally(trivial_path);
    cout << "Cost after local improvement: " << g.cost_of_path(trivial_path) << endl;

    for(int j=0; j<5; ++j){
        for(int i=1; i<8; ++i){
            trivial_path = g.improve_path_locally(trivial_path, 8, 2*i); 
        }
    }
    cout << "Cost after extreme local improvement: " << g.cost_of_path(trivial_path) << endl;


}

int main(){

#if TEST1

try{

    cout << "Running Test1" << endl;
    test_add_vertex();
}
catch(int e){
    if(e==1){
        cout << "Invalid Result" << endl;
    }
}

#endif

#if TEST2

try{
    cout << "Running Test2" << endl;
    test_delete_vertex();
}

catch(int e){
    if(e==1){
        cout << "Invalid Result" << endl;
    }
}

#endif

#if TEST3

try{
    cout << "Running Test3" << endl;
    test_graph_destructor();
}
catch(int e){

}

#endif

#if TEST4

try{

    cout << "Running Test4" << endl;
    test_TSP_approximation();

}
catch(exception &e){
    cout << "Unkown Error" << endl;
}

#endif

#if TEST5

try{

    cout << "Running Test5" << endl;
    test_brute_force_path();

}
catch(exception &e){
    cout << "Unkown Error" << endl;
}


#endif

#if TEST6

cout << "Running Test6" << endl;
test_optimal_routing();

#endif

#if TEST7

test_improve_path_locally();

#endif
    

#if TEST8

cout << "Running Edge index" << endl;
Graph g = graph_example();


cout << "Edge Indices" << endl;

int index = g.get_edge_index(8, 13);
cout << index << endl;
cout << g.get_edge(index)->get_vertices().first->get_index() << " " << g.get_edge(index)->get_vertices().second->get_index() << endl;

/*
for(int i=0; i < g.get_num_vertices(); ++i){
    for(int j=0; j < g.get_num_vertices(); ++j){
        cout << g.get_edge_index(i,j) << " ";
    }
    cout << endl;
}
*/

#endif

return 0;

}