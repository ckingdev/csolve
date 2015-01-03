#include "Puzzle.hpp"
#include <vector>

// int iddfs_n(Puzzle pos, std::vector<Move> move_set, int max_depth);

// std::vector<int> IDA_star(Puzzle p, std::vector<Move> move_set, int max_depth)
// {
//         std::vector<int> sol;

// }
template <typename puzzle>
bool DLS(const puzzle &p, std::vector<Move> &move_set, int depth, int max_depth, std::vector<int> &sol) {
        if (depth > 0) {
                auto new_ps = p.apply_moves(move_set);
                int len = move_set.size();
                for (int i = 0; i < len; i++) {
                        sol[depth] = i;
                        bool found = DLS(new_ps[i], move_set, depth-1, max_depth, sol);
                        if (found) {
                                std::cout << "I'm a dumbass!" << std::endl;
                                return true;
                        }
                }
        } else if (p.solved()) {
                return true;
        }
        return false;
}

template <typename puzzle>
std::vector<int> IDDFS(puzzle &p, std::vector<Move> &move_set, int max_depth) {
        for(int i = 1; i <= max_depth; i++) {
                std::vector<int> sol;
                sol.resize(i);
                bool solved = DLS(p, move_set, max_depth, max_depth, sol);
                if (solved) {
                        return sol;
                }
        }
        std::vector<int> sol;
        sol.push_back(-1);
        return sol;
}