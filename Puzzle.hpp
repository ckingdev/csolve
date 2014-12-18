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

// Move base_moves[6];
std::vector<Move> init_three_moves();

class Puzzle 
{
public:
	Puzzle(void) { edges.reserve(3); corners.reserve(2); }
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

#endif
