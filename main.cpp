#include "Puzzle.hpp"
#include "PruningTable.hpp"

#include <cstdlib>
#include <cstdio>


int main()
{
	// ptr = (char*)malloc(max);
	auto p = get_cross();
	auto base_moves = get_3x3_h_turns();
	// for (int move_no = 0; move_no < 6; move_no++) {
	// 	Move R2 = compose(base_moves[move_no], base_moves[move_no]);
	// 	Move Ri = compose(R2, base_moves[move_no]);
	// 	Move identity = compose(Ri, base_moves[move_no]);
	// 	for (int i = 0; i < 8; i++) {
	// 		if (identity.corners.count(i)) {
	// 			printf("%i : %i %i\n", i, identity.corners[i].p, identity.corners[i].o);
	// 		}
	// 	}
	// 	for (int i = 0; i < 12; i++) {
	// 		if (identity.edges.count(i)) {
	// 			printf("%i : %i %i\n", i, identity.edges[i].p, identity.edges[i].o);
	// 		}
	// 	}
		
	// }
	auto pt = gen_pruning_table(p, 8, base_moves);
	// printf("%lu\n", pt.size());
	// printf("%lu\n", allocated);
	return 0;
}