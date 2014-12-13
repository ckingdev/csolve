#include <vector>
#include <utility>
#include <unordered_map>

struct Location {
	int p;
	int o;
};

struct Piece {
	int id;
	Location loc;
};

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
	bool solved() const;
	void print() const;
private:
	std::vector<Piece> edges;
	std::vector<Piece> corners;
};

Puzzle get_first_block();

