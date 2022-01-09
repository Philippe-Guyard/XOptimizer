#include "map.hpp"
#include <set>

EdgeWeight Map::find_distances_astar(int start, int end){

	/*
	Finds the cost to go from vertice i to vertice j.

	PARAMETERS:
	int i, int j:
	Indexes of the start and finish vertices, respectively.

	RETURN:
	EdgeWeight:
	The (approximate) lowest cost to go from i to j.
	The heuristic function is the haversine distance implemented in the VertexData class.

	*/

	VertexData end_data = vertices.at(end)->get_data();
	std::vector<EdgeWeight> gScore(this->num_vertices, std::numeric_limits<EdgeWeight>::max());
	std::vector<EdgeWeight> fScore(this->num_vertices, std::numeric_limits<EdgeWeight>::max());
	gScore[start] = 0;
	fScore[start] = gScore[start] + vertices.at(start)->get_data().get_distance(end_data);

	auto compare = [&start, &gScore](const int &a, const int &b){
					return gScore[a] < gScore[b];
			};

	std::set<int, decltype(compare)> OpenSet(compare);
	OpenSet.insert(start);

	int cur;

	while (!OpenSet.empty()){
		cur = *OpenSet.begin();
		if (cur == end){
			return fScore[end];
		}
		OpenSet.erase(cur);
		for (Edge* ptr_edge : adjacency_list[cur]){
			int to = ptr_edge->get_vertices().second->get_index();
			EdgeWeight length = ptr_edge->get_weight();

			if (gScore[to] > gScore[cur] + length){
				gScore[to] = gScore[cur] + length;
				fScore[to] = gScore[to] + vertices.at(to)->get_data().get_distance(end_data);
				if (OpenSet.count(to) > 0){
					OpenSet.erase(to);
				}
				OpenSet.insert(to);
			}
		}
	}
	return std::numeric_limits<EdgeWeight>::max();  //in case there's no path
}
