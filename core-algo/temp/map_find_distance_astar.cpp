#include "map.hpp"

EdgeWeight Map::find_distances_astar(int start, int end){
	VertexData end_data = vertices.at(end)->get_data();
	std::vector<EdgeWeight> gScore(this->num_vertices, std::numeric_limits<EdgeWeight>::max());
	std::vector<EdgeWeight> fScore(this->num_vertices, std::numeric_limits<EdgeWeight>::max());
	gScore[start] = 0;
	fScore[start] = gScore[start] + vertices.at(start)->get_data().get_distance(end_data);

	std::unordered_set<int> OpenSet;
	OpenSet.insert(start);
	int cur;
	int best_cand;
	EdgeWeight best_cand_dist;

	while (!OpenSet.empty()){
		best_cand_dist = std::numeric_limits<EdgeWeight>::max();
		for (int node : OpenSet){
			if (fScore[node] < best_cand_dist){
				best_cand = node;
			}
		}
		cur = best_cand;
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
				if (OpenSet.count(to) == 0){
					OpenSet.insert(to);
				}
			}
		}
	}
	return std::numeric_limits<EdgeWeight>::max();  //in case there's no path
}
