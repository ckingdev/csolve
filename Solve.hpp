#include "Puzzle.hpp"
#include "PruningTable.hpp"
#include <vector>

enum Status { NO_SOLUTION, ALREADY_SOLVED, SOLVED };

struct Solution {
    Status status;
    std::vector<int> solution;
};

template <typename puzzle>
bool DLS(const puzzle &p, const std::vector<Move> &move_set, int depth,
         int max_depth, std::vector<int> &sol) {
    if (depth > 0) {
        auto new_ps = p.apply_moves(move_set);
        int len = move_set.size();
        for (int i = 0; i < len; i++) {
            sol[depth - 1] = i;
            bool found = DLS(new_ps[i], move_set, depth - 1, max_depth, sol);
            if (found) {
                return true;
            }
        }
    } else if (p.solved()) {
        return true;
    }
    return false;
}

template <typename puzzle>
Solution IDDFS(const puzzle &p, const std::vector<Move> &move_set,
               int max_depth) {
    if (p.solved()) {
        std::vector<int> empty;
        return Solution{ ALREADY_SOLVED, empty };
    }
    for (int i = 1; i <= max_depth; i++) {
        std::vector<int> sol;
        sol.resize(i);
        bool solved = DLS(p, move_set, i, i, sol);
        if (solved) {
            return Solution{ SOLVED, sol };
        }
    }
    std::vector<int> empty;
    return Solution{ NO_SOLUTION, empty };
}

bool IDAstar_DLS(const Puzzle<0, 8> &p, const std::vector<Move> &move_set,
                 int depth, int max_depth, std::vector<int> &sol,
                 const Puzzle<0, 4>::PruningTable &pt) {
    if (depth < max_depth) {
        auto new_ps = p.apply_moves(move_set);
        int len = move_set.size();
        for (int i = 0; i < len; i++) {
            auto four_c = extract_4_corners(new_ps[i]);
            int h = pt.at(four_c);
            if (h + depth > max_depth) {
                continue;
            }
            sol[depth] = i;
            bool found =
                IDAstar_DLS(new_ps[i], move_set, depth + 1, max_depth, sol, pt);
            if (found) {
                return true;
            }
        }
    } else if (p.solved()) {
        return true;
    }
    return false;
}

Solution IDAstar(const Puzzle<0, 8> &p, const std::vector<Move> &move_set,
                 int max_depth, const Puzzle<0, 4>::PruningTable &pt) {
    if (p.solved()) {
        std::vector<int> empty;
        return Solution{ ALREADY_SOLVED, empty };
    }
    for (int i = 1; i <= max_depth; i++) {
        std::vector<int> sol;
        sol.resize(i);
        bool solved = IDAstar_DLS(p, move_set, 0, i, sol, pt);
        if (solved) {
            return Solution{ SOLVED, sol };
        }
    }
    std::vector<int> empty;
    return Solution{ NO_SOLUTION, empty };
}