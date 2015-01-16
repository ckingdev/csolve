#include "Puzzle.hpp"
#include "PruningTable.hpp"
#include "cereal/archives/binary.hpp"
#include "Interface.hpp"
#include "PriorityQueue.hpp"
#include "Search.hpp"

#include <cstdlib>
#include <cstdio>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <boost/progress.hpp>

std::vector<int> get_rand_seq(int max, int len) {
    std::vector<int> seq;
    for (int i = 0; i < len; i++) {
        seq.push_back(rand() % max);
    }
    return seq;
}


Puzzle<0,8> get_random_2x2_scramble(int n_moves, int len_scramble, std::vector<Move> move_set) {
    Puzzle<0,8> tmp = get_corners();
    std::vector<int> scramble = get_rand_seq(n_moves, len_scramble);
    for (auto &i : scramble) {
        tmp = tmp.apply(move_set[i]);
    }
    return tmp;
}

int main() {
    auto p = get_corners();
    auto base_moves = get_2x2_h3gen_turns();
    decltype(p)::PruningTable pt = bfs_pruning_table(p, 11, base_moves);
    std::cout << "Pruning table generated.\n";
    boost::progress_timer timer;
    for (int i = 0; i < 100000; i++) {
        auto to_solve = get_random_2x2_scramble(9, 25, base_moves); 
        std::vector<int> sol = A_star_single<Puzzle<0, 8>, 9>(to_solve, pt, 1000, base_moves);
        sol.clear();
    }
    std::cout << "\n";
}