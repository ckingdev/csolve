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
    Puzzle<0, 8> p = get_corners();
    auto base_moves = get_2x2_h3gen_turns();
    std::cout<<base_moves.size()<<std::endl;
    // decltype(p)::PruningTable pt = gen_pruning_table(p, 8, base_moves);
    // save_pruning_table<decltype(p)>("test.prune", pt);
    std::cout << p.solved() << std::endl;
    p = p.apply(base_moves[0]);
    // p = p.apply(base_moves[4]);
    std::cout << p.solved() << std::endl;
    std::vector<int> sol = IDDFS(p, base_moves, 3);
    for (auto &i : sol) {
        std::cout << i << " ";
    }
    return 0;
}