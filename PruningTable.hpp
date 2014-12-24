#ifndef PRUNINGTABLE_HPP
#define PRUNINGTABLE_HPP

#include <vector>
#include <unordered_map>
#include "Puzzle.hpp"

template <typename puzzle>
void DLS(typename puzzle::PruningTable &pt, const puzzle &puz, int depth,
         int max_depth, const std::vector<Move> &move_set) {
    if (depth > 0) {
        auto new_puzs = puz.apply_moves(move_set);
        for (auto &i : new_puzs)
            DLS(pt, i, depth - 1, max_depth, move_set);
    } else {
        auto found = pt.find(puz);
        if (found == pt.end())
            pt[puz] = max_depth;
        return;
    }
}

// gen_pruning_table() generates a position->(moves from puz) mapping.
//
// Iterative deepening depth first search is used in order to keep memory usage
// low.
template <typename puzzle>
typename puzzle::PruningTable
gen_pruning_table(const puzzle &puz, int max_depth,
                  const std::vector<Move> &move_set) {
    typename puzzle::PruningTable pt;
    for (int d = 0; d <= max_depth; d++) {
        DLS(pt, puz, d, d, move_set);
        // printf("Depth %i: %lu\n", d, pt.size());
    }
    return pt;
}

// get_depth_chart() processes a pruning table and creates a chart of the
// number of positions at each depth.
template <typename puzzle>
std::unordered_map<int, int> get_depth_chart(typename puzzle::PruningTable pt) {
    std::unordered_map<int, int> chart;
    for (auto &i : pt) {
        int depth = i.second;
        if (chart.count(depth)) {
            chart[depth]++;
        } else {
            chart[depth] = 1;
        }
    }
    return chart;
}

#endif