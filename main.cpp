#include "Puzzle.hpp"
#include "PruningTable.hpp"

#include <cstdlib>
#include <cstdio>


int main()
{
	Puzzle p = get_corners();
	auto base_moves = get_3x3_h_turns();
	PruningTable pt = gen_pruning_table(p, 11, base_moves);
	return 0;
}