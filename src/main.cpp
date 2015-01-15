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
    Node<int> n1 = Node<int>(3, 4);
    Node<int> n2 = Node<int>(3, 3);
    std::cout << (n1 <= n2) << std::endl;
    std::cout << (n1 >= n2) << std::endl;
    return 0;
}