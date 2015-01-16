#ifndef SEARCH_HPP
#define SEARCH_HPP

#include "Puzzle.hpp"
#include "PriorityQueue.hpp"
#include <vector>

template<typename puzzle>
struct SearchNode {
	puzzle state;
	std::vector<int> moves_taken;
};

int get_axis(int move) {
	if (move < 3) {
		return move;
	} else {
		return (move - 1) / 3;
	}
}

template<typename puzzle, int d>
std::vector<int> A_star_single(puzzle root, typename puzzle::PruningTable &pt, 
                               int pq_size, std::vector<Move> move_set) {
	int n_moves = move_set.size();
	MinHeap<SearchNode<puzzle>, d> pq(pq_size);
	SearchNode<puzzle> root_node = {root, {}};
	pq.insert(root_node, 0);
	while (!pq.is_empty()) {
		auto state = pq.pop();
		// int prev_axis;
		// if (state.moves_taken.size() > 0) {
		// 	int prev_move = state.moves_taken.back();
		// 	prev_axis = get_axis(prev_move);
		// } else {
		// 	prev_axis = -1;
		// }
		for (int i = 0; i < n_moves; i++) {
			// if (get_axis(i) == prev_axis) {
			// 	continue;
			// }
			std::vector<int> new_moves_taken = state.moves_taken;
			new_moves_taken.push_back(i);
			puzzle new_state = state.state.apply(move_set[i]);
			if (new_state.solved()) {
				return new_moves_taken;
			}
			SearchNode<puzzle> new_node = {new_state, new_moves_taken};
			int new_p = pt[new_state] + new_moves_taken.size();
			pq.insert(new_node, new_p);
		}
	}
	return {};
}

#endif