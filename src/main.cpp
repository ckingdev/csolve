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

int main() {
    // auto p = get_corners();
    // auto base_moves = get_2x2_h3gen_turns();
    // decltype(p)::PruningTable pt = gen_pruning_table(p, 11, base_moves);
    // std::cout << pt.size() << std::endl;
    // save_pruning_table<decltype(p)>("test.prune", pt);
    // std::string s = "R U F R' F2";
    // auto moves = parse_move_string(s, get_2x2_3gen_parse_table());
    // for (auto &i : moves) {
    //     std::cout << i << std::endl;
    // }
    // 
    // int n = 100;
    // MinHeap<int, 50> mh(n);
    // for (int i = 0; i < n; i++) {
    //     mh.insert(n-i, n-i);
    // }
    // for (int i = 0; i < n; i++) {
    //     std::cout<< mh.pop() << " ";
    // }
    // mh.print();
    // return 0;
    // 
    auto p = get_corners();
    auto base_moves = get_2x2_h3gen_turns();
    decltype(p)::PruningTable pt = bfs_pruning_table(p, 11, base_moves);
    p = p.apply(base_moves[0]);
    p = p.apply(base_moves[1]);
    std::vector<int> sol = A_star_single<Puzzle<0, 8>, 2>(p, pt, 100, base_moves);
    std::cout << sol[0] << std::endl;
}