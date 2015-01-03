#include "Puzzle.hpp"
#include "PruningTable.hpp"
#include "cereal/archives/binary.hpp"
#include "Interface.hpp"
#include "Solve.hpp"
#include <cstdlib>
#include <cstdio>
#include <string>
#include <fstream>

int main() {
    Puzzle<0, 4> p = get_4_corners();
    auto base_moves = get_2x2_h3gen_turns();
    std::cout << base_moves.size() << std::endl;
    decltype(p)::PruningTable pt = gen_pruning_table(p, 6, base_moves);
    Puzzle<0, 8> full = get_corners();
    full = full.apply(base_moves[0]);
    full = full.apply(base_moves[1]);
    full = full.apply(base_moves[2]);
    Solution sol = IDAstar(full, base_moves, 8, pt);
    // Solution sol = IDDFS(full, base_moves, 4);
    std::cout << sol.status << std::endl;
    return 0;
}