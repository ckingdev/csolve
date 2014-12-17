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

class puzzle_hasher {
public:
	std::size_t operator()(Puzzle const &p) const;
};


typedef std::unordered_map<Puzzle, int, puzzle_hasher> PruningTable;

PruningTable gen_pruning_table(const Puzzle &puz, int max_depth, const std::vector<Move> &move_set);

#endif