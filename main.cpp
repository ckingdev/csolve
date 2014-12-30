#include "Puzzle.hpp"
#include "PruningTable.hpp"
#include "cereal/archives/binary.hpp"

#include <cstdlib>
#include <cstdio>
#include <fstream>

int main() {
    auto p = get_4_corners();
    auto base_moves = get_2x2_h3gen_turns();
    auto pt = gen_pruning_table(p, 11, base_moves);
    std::ofstream outfile;
    outfile.open("2x2_4corner.prune");
    cereal::BinaryOutputArchive oarchive(outfile);
    oarchive(pt);
    return 0;
}