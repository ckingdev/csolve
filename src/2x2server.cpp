#include "Puzzle.hpp"
#include "PruningTable.hpp"
#include "cereal/archives/binary.hpp"
#include "Interface.hpp"
 
#include <cstdlib>
#include <cstdio>
#include <string>
#include <fstream>
#include <iostream>
 
int main(int argc, char *argv[]) {
    assert(argc > 1);
    auto p = get_corners();
    auto base_moves = get_2x2_h3gen_turns();
    decltype(p)::PruningTable pt = gen_pruning_table(p, int(argv[1][0]-'0'), base_moves);
    if (argc >= 3) {
        save_pruning_table<decltype(p)>(argv[2], pt);
    }
    return 0;
}