#ifndef PUZZLE_HPP
#define PUZZLE_HPP

#include <array>
#include <vector>
#include <cassert>
#include <unordered_map>
#include <iostream>

struct Location {
	int p;
	int o;
};

struct Piece {
	int id;
	Location loc;
};

bool operator != (const Piece a, const Piece b);

struct Move {
	std::unordered_map<int, Location> edges;
	std::unordered_map<int, Location> corners;
};

std::vector<Move> init_three_moves();
Move compose(const Move &a, const Move &b);

template<typename puzzle>
class puzzle_hasher {
public:
	std::size_t operator()(puzzle const &p) const;
};

template<typename puzzle>
std::size_t puzzle_hasher<puzzle>::operator()(puzzle const &p) const
{
	std::size_t seed = 0;
	const auto &edges = p.get_edges();
	const auto &corners = p.get_corners();
	for(unsigned int i = 0; i < edges.size(); i++) {
		seed ^= edges[i].loc.p + 0x9e3779b9 + (seed << 6) + (seed >> 2);
		seed ^= edges[i].loc.o + 0x9e3779b9 + (seed << 6) + (seed >> 2);
	}
	for(unsigned int i = 0; i < corners.size(); i++) {
		seed ^= corners[i].loc.p + 0x9e3779b9 + (seed << 6) + (seed >> 2);
		seed ^= corners[i].loc.o + 0x9e3779b9 + (seed << 6) + (seed >> 2);
	}
	return seed;
}

template<std::size_t edges_num, std::size_t corners_num>
class Puzzle 
{
public:
	typedef std::unordered_map<Puzzle, int, puzzle_hasher<Puzzle>> PruningTable;

	Puzzle(void) : added_edges(0), added_corners(0) { }

	void add_edge(Piece p) {
		assert(added_edges < edges_num);
		edges[added_edges] = p;
		added_edges++;
	}
	void add_corner(Piece p) {
		assert(added_corners < corners_num);
		corners[added_corners] = p;
		added_corners++;
	}
	Puzzle apply(const Move &m) const { 	
		Puzzle new_puz;

		Location l = {0, 0}; // these are overwritten each loop. Temp variables.
		Piece p = {0, {0, 0}};

		auto corners_end = m.corners.end();
		auto edges_end = m.edges.end();

		for (auto & corner : corners) {
			auto corner_iter = m.corners.find(corner.loc.p);
			if (corner_iter != corners_end) {
				l = corner_iter->second;
				l.o = (l.o + corner.loc.o) % 3;
				p.id = corner.id;
				p.loc = l;
				new_puz.add_corner(p);
			} else {
				new_puz.add_corner(corner);
			}
		}
		for (auto & edge : edges) {
			auto edge_iter = m.edges.find(edge.loc.p);
			if (edge_iter != edges_end) {
				l = edge_iter->second;
				l.o = (l.o + edge.loc.o) % 2;
				p.id = edge.id;
				p.loc = l;
				new_puz.add_edge(p);
			} else {
				new_puz.add_edge(edge);
			}
		}
		return new_puz;
	}

	std::vector<Puzzle> apply_moves(const std::vector<Move> &move_list) const {
		std::vector<Puzzle> applied;
		applied.reserve(20);
		std::size_t len = move_list.size();
		for (std::size_t i = 0; i < len; i++) { // iterator
			applied.emplace_back(apply(move_list[i]));
		}
		return applied;
	}

	bool solved() const {
		std::size_t len = corners.size();
		for (unsigned int i = 0; i < len; i++) { // change these to auto &i : whatever
			if (corners[i].id != corners[i].loc.p || corners[i].loc.o != 0)
				return false;
		}
		len = edges.size();
		for (unsigned int i = 0; i < len; i++) {
			if (edges[i].id != edges[i].loc.p || edges[i].loc.o != 0)
				return false;
		}
		return true;
	}

	bool operator ==(const Puzzle &b) const
	{
		auto &a_edges = get_edges();
		auto &a_corners = get_corners();
		auto &b_edges = b.get_edges();
		auto &b_corners = b.get_corners();
		if (a_edges.size() != b_edges.size() || a_corners.size() != b_corners.size())
			return false;

		auto len = a_edges.size();
		for (unsigned int i = 0; i < len; i++) {
			if(a_edges[i] != b_edges[i])
				return false;
		}

		len = a_corners.size();
		for (unsigned int i = 0; i < len; i++) {
			if(a_corners[i] != b_corners[i])
				return false;
		}
		return true;
	}

	void print() const {
		std::cout << "Corners:\n";
		for (uint i = 0; i < corners.size(); i++) { // iterator again
			printf("%i | %i %i\n", corners[i].id, corners[i].loc.p, corners[i].loc.o);
		}

		std::cout << "\nEdges:\n";
		for (uint i = 0; i < edges.size(); i++) {
			printf("%i | %i %i\n", edges[i].id, edges[i].loc.p, edges[i].loc.o);
		}
		std::cout << "\n";
	}

	const std::array<Piece, edges_num> &get_edges() const { return edges; }
	const std::array<Piece, corners_num> &get_corners() const { return corners; }

private:
	int added_edges;
	int added_corners;
	std::array<Piece, edges_num> edges;
	std::array<Piece, corners_num> corners;
};

Puzzle<3,2> get_first_block();
Puzzle<4,0> get_cross();
Puzzle<12,8> get_full();

#endif
