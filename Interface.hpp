#include <string>
#include "Puzzle.hpp"
#include <fstream>

template <typename puzzle>
void save_pruning_table(std::string f_name, typename puzzle::PruningTable &pt) {
    std::ofstream outfile;
    outfile.open(f_name);
    cereal::BinaryOutputArchive oarchive(outfile);
    oarchive(pt);
}
