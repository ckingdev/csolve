#include "Puzzle.hpp"
#include "PruningTable.hpp"

int main()
{
	Puzzle p = get_first_block();
	auto base_moves = init_moves();
	PruningTable pt = gen_pruning_table(p, 8, base_moves);
	return 0;
}