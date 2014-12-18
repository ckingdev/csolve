#ifndef PRUNINGTABLE_HPP
#define PRUNINGTABLE_HPP

#include <vector>
#include <unordered_map>
#include "Puzzle.hpp"
// from http://stackoverflow.com/questions/20511347/a-good-hash-function-for-a-vector
// std::size_t operator()(std::vector<uint32_t> const& vec) const {
//   std::size_t seed = 0;
//   for(auto& i : vec) {
//     seed ^= i + 0x9e3779b9 + (seed << 6) + (seed >> 2);
//   }
//   return seed;
// }

template<typename puzzle>
void DLS(typename puzzle::PruningTable &pt, const puzzle &puz, int depth, int max_depth, const std::vector<Move> &move_set)
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
template<typename puzzle>
typename puzzle::PruningTable gen_pruning_table(const puzzle &puz, int max_depth, const std::vector<Move> &move_set)
{
	typename puzzle::PruningTable pt;
	for (int d = 1; d <= max_depth; d++) {
		DLS(pt, puz, d, d, move_set);
		printf("Depth %i: %lu\n", d, pt.size());
	}
	return pt;
}

#endif