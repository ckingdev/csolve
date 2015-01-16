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

template<typename puzzle, int d>
std::vector<int> A_star_single(puzzle root, typename puzzle::PruningTable &pt, 
                               int pq_size, std::vector<Move> move_set) {
	int n_moves = move_set.size();
	MinHeap<SearchNode<puzzle>, d> pq(pq_size);
	SearchNode<puzzle> root_node = {root, {}};
	pq.insert(root_node, 0);
	while (!pq.is_empty()) {
		auto state = pq.pop();
		for (int i = 0; i < n_moves; i++) {
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