#include "Puzzle.hpp"
#include "PruningTable.hpp"

int main()
{
	Puzzle p = get_first_block();
	auto base_moves = init_three_moves();
	PruningTable pt = gen_pruning_table(p, 4, base_moves);
	printf("%lu\n", pt.size());
	return 0;
}