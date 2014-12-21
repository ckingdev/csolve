#include "Puzzle.hpp"
#include "PruningTable.hpp"

#include <cstdlib>
#include <cstdio>

int main() {
    auto p = get_cross();
    auto base_moves = get_3x3_h_turns();
    auto pt = gen_pruning_table(p, 8, base_moves);
    return 0;
}