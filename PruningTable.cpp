#include "PruningTable.hpp"
#include <queue>

std::size_t puzzle_hasher::operator()(Puzzle const &p) const
{
	std::size_t seed = 0;
	auto edges = p.get_edges();
	auto corners = p.get_corners();
	for(unsigned int i = 0; i < edges.size(); i++) {
		seed ^= edges[i].loc.p + 0x9e3779b9 + (seed << 6) + (seed >> 2);
		seed ^= edges[i].loc.o + 0x9e3779b9 + (seed << 6) + (seed >> 2);
	}
	for(unsigned int i = 0; i < corners.size(); i++) {
		seed ^= corners[i].loc.p + 0x9e3779b9 + (seed << 6) + (seed >> 2);
		seed ^= corners[i].loc.o + 0x9e3779b9 + (seed << 6) + (seed >> 2);
	}
	return seed;
}

struct Node {
	Puzzle puz;
	int dist;
};

class CompareNode {
	public:
		bool operator() (Node a, Node b) {
			return a.dist > b.dist;
		}
};

PruningTable gen_pruning_table(Puzzle start, int max_depth)
{
	PruningTable pt;
	std::priority_queue<Node, std::vector<Node>, CompareNode> queue;
	queue.push(Node{start, 0});
	while (queue.size() > 0) {
		Node current = queue.top();
		queue.pop();
		if(pt.count(current.puz)) {
			continue;
		}
	}
	return pt;
}