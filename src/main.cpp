#include "Puzzle.hpp"
#include "PruningTable.hpp"
#include "cereal/archives/binary.hpp"
#include "Interface.hpp"
#include "PriorityQueue.hpp"

#include <cstdlib>
#include <cstdio>
#include <string>
#include <fstream>
#include <iostream>

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
    MinHeap<int> mh(7);
    mh.insert(0, 5);
    mh.insert(0, 4);
    mh.insert(0, 3);
    mh.insert(0, 2);
    mh.insert(0, 1);
    mh.print();
    return 0;
}