#include "graph.hpp"
#include "Vec3.hpp"
#include "graph_algorithms.hpp"

using namespace std;

#define TEST1 true
#define TEST2 true

void test_add_vertex(){

    Graph g = Graph();
    
    int N = 15;
    for(int i=0; i<N; ++i){
        VertexData vdata = VertexData({i,i});

        vector< pair<VertexData, double> > dis(i);
        for(int j=0; j<i; ++j){
            dis[j] = {VertexData({j,j}), i*j};
        }

        g.add_vertex(vdata, dis);
    }

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

    Graph g = Graph();
    
    int N = 15;
    
    for(int i=0; i<N; ++i){
        VertexData vdata = VertexData({i,i});

        vector< pair<VertexData, double> > dis(i);
        for(int j=0; j<i; ++j){
            dis[j] = {VertexData({j,j}), i*j};
        }

        g.add_vertex(vdata, dis);
    }

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

    return 0;

}