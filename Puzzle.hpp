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

void init_moves();

class Puzzle 
{
public:
	void add_edge(Piece p);
	void add_corner(Piece p);
	Puzzle apply(Move m) const;
	std::vector<Puzzle> apply_moves(std::vector<Move> move_list);
	bool solved() const;
	void print() const;
	std::vector<Piece> get_edges() const;
	std::vector<Piece> get_corners() const;

private:
	std::vector<Piece> edges;
	std::vector<Piece> corners;
};

bool operator ==(const Puzzle a, const Puzzle b);

Puzzle get_first_block();

#endif