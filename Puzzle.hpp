#ifndef PUZZLE_HPP
#define PUZZLE_HPP

#include <vector>
#include <unordered_map>

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

std::vector<Move> get_3x3_h_turns();
std::vector<Move> get_3x3_q_turns();
Move compose(const Move &a, const Move &b);

class Puzzle 
{
public:
	Puzzle(void) { edges.reserve(4); corners.reserve(0); }
	Puzzle(const Puzzle & copy) : edges(copy.edges), corners(copy.corners) { }
	Puzzle(Puzzle && tmp) : edges(std::move(tmp.edges)), corners(std::move(tmp.corners)) { }
	Puzzle &operator=(const Puzzle & assign_from) = default;

	void add_edge(Piece p); // These functions MUST sort on ID to ensure
	void add_corner(Piece p);
	Puzzle apply(const Move &m) const;
	std::vector<Puzzle> apply_moves(const std::vector<Move> &move_list) const;
	bool solved() const;
	void print() const;
	const std::vector<Piece> &get_edges() const;
	const std::vector<Piece> &get_corners() const;

private:
	std::vector<Piece> edges;
	std::vector<Piece> corners;
};

bool operator ==(const Puzzle &a, const Puzzle &b); // Needed for unordered_map

Puzzle get_first_block();
Puzzle get_cross();
Puzzle get_full();

#endif
