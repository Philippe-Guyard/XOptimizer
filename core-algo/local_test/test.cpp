
#include "../temp/map.hpp"
#include<iostream>
#include<iomanip>

int main(){
    
    int n = 9;
	VertexData arr[n];
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i){
		arr[i] = VertexData({i,i});
	}
	std::vector<std::vector<std::pair<int, EdgeWeight>>> adjacency_list = {
		{{1,4}, {7,8}},
		{{2, 8}, {7, 11}, {0,4}},
        {{3, 7}, {8, 2}, {5, 4}, {1,8}},
        {{4, 9}, {5, 14}, {2,7}},
		{{5, 10}, {3,9}},
		{{6, 2}, {2,4}, {3,14}, {4,10}},
		{{7, 1}, {8, 6}, {5,2}},
		{{8, 7}, {0, 8}, {1,11}, {6,1}},
        {{2,2}, {6,6}, {7,7}}
	};

	Map map(n, arr, adjacency_list);
    std::vector<std::vector<EdgeWeight>> distances = map.find_distances();
	for(int i = 0; i<distances.size(); i++){
        std::cout << std::setprecision(4) << distances[0][i] << " ";
    }
	return 0;
    
}
