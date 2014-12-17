#include "PruningTable.hpp"
#include "Puzzle.hpp"
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

void DLS(PruningTable &pt, const Puzzle &puz, int depth, int max_depth, const std::vector<Move> &move_set)
{
	if (depth > 0) {
		auto new_puzs = puz.apply_moves(move_set);
		for (auto &i : new_puzs)
			DLS(pt, i, depth - 1, max_depth, move_set);
	} else {
		auto found = pt.find(puz);
		if (found == pt.end())
			pt[puz] = max_depth;
		return;
	}
}

/* 
gen_pruning_table generates a position->(moves from puz) mapping.

Iterative deepening depth first search is used in order to keep memory usage
low.
*/
PruningTable gen_pruning_table(const Puzzle &puz, int max_depth, const std::vector<Move> &move_set)
{
	PruningTable pt;
	for (int d = 1; d <= max_depth; d++)
		DLS(pt, puz, d, d, move_set);
	return pt;
}