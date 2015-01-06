#include <string>
#include "Puzzle.hpp"
#include <fstream>
#include <unordered_map>

std::unordered_map<std::string, int> get_2x2_3gen_parse_table() {
    std::unordered_map<std::string, int> tbl;
    tbl["R"] = 0;
    tbl["U"] = 1;
    tbl["F"] = 2;
    tbl["R'"] = 3;
    tbl["R2"] = 4;
    tbl["U2"] = 5;
    tbl["U'"] = 6;
    tbl["F2"] = 7;
    tbl["F'"] = 8;
    return tbl;
}

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


std::vector<std::string> str_split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

std::vector<int> parse_move_string(std::string s, std::unordered_map<std::string, int> tbl) {
    auto tokens = str_split(s, ' ');
    std::vector<int> moves;
    for (auto &i : tokens) {
        moves.push_back(tbl[i]);
    }
    return moves;
}

template <typename puzzle>
void save_pruning_table(std::string f_name, typename puzzle::PruningTable &pt) {
    std::ofstream outfile;
    outfile.open(f_name);
    cereal::BinaryOutputArchive oarchive(outfile);
    oarchive(pt);
}
