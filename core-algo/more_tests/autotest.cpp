#include "graph.hpp"
#include "Vec3.hpp"
#include "graph_algorithms.hpp"

using namespace std;

#define TEST1 true
#define TEST2 true
#define TEST3 true
#define TEST4 true
#define TEST5 true

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

void test_brute_force_path(){

    int N = 9;

    Graph g = graph_example(N);

    vector<int> arange;
    for(int i=0; i<N; ++i){
        arange.push_back(i);
    }

    vector<int> res = g.best_path_brute_force(arange);

    for(auto i: res){
        cout << i << " ";
    }

    cout << "Cost of path: " << g.cost_of_path(res) << endl;
    cout << endl;

}


int main(){

#ifdef TEST1

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

#ifdef TEST2

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

#ifdef TEST3

try{
    cout << "Running Test3" << endl;
    test_graph_destructor();
}
catch(int e){

}

#endif

#ifdef TEST4

try{

    cout << "Running Test4" << endl;
    test_TSP_approximation();

}
catch(exception &e){
    cout << "Unkown Error" << endl;
}

#endif

#ifdef TEST5

try{

    cout << "Running Test5" << endl;
    test_brute_force_path();

}
catch(exception &e){
    cout << "Unkown Error" << endl;
}


#endif

    return 0;

}