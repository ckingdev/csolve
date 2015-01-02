#include "Puzzle.hpp"
#include "PruningTable.hpp"
#include "cereal/archives/binary.hpp"
#include "Interface.hpp"

#include <cstdlib>
#include <cstdio>
#include <string>
#include <fstream>

int main() {
    auto p = get_4_corners();
    auto base_moves = get_2x2_h3gen_turns();
    decltype(p)::PruningTable pt = gen_pruning_table(p, 8, base_moves);
    save_pruning_table<decltype(p)>("test.prune", pt);
    return 0;
}