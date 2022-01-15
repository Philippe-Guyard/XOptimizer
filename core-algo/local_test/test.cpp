#include "../src/map/map.hpp"
#include <fstream>
#include <string>

void Map::save(std::fstream& savefile){
	savefile << this->num_vertices << std::endl;
	for (auto i : this->distance_matrix){
		for (auto j : i){
			savefile << j << std::endl;
		}
	}
};

void Map::load(std::fstream& savefile){
	std::string c;
	getline(savefile, c, '\n');
	int n = stoi(c);
	std::vector<std::vector<double>> dist;
	std::vector<double> row;
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			getline(savefile, c, '\n');
			row.push_back(stod(c));
		}
		dist.push_back(row);
		row.clear();
	}
	this->distance_matrix = dist;
}

int main()
{
	VertexData arr[6];
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i){
		arr[i] = VertexData({i,i});
	}
	std::vector<std::vector<std::pair<int, EdgeWeight>>> adjacency_list = {
		{{1, 10}},
		{{0, 10}, {2, 2}, {3, 1}, {4, 3}},
		{{1, 2}, {4, 0}, {5, 6}},
		{{1, 1}},
		{{1, 3}, {2, 0}, {5, 1}},
		{{2, 6}, {4, 1}}
	};

	Map map(6, arr, adjacency_list);
	Map map2(6, arr, adjacency_list);
	map.distance_matrix = map.find_distances();

	std::fstream savefile;
	savefile.open ("savefile.txt", std::fstream::in | std::fstream::out);
	map.save(savefile);
	savefile.close();
	savefile.open ("savefile.txt", std::fstream::in | std::fstream::out);
	map2.load(savefile);
	savefile.close();

	std::cout << bool(map.distance_matrix == map2.distance_matrix) << std::endl;
}
