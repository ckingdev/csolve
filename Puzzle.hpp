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

// Move moves[18];

class Puzzle 
{
public:
	// Puzzle();
	void add_edge(Piece p);
	void add_corner(Piece p);
	Puzzle apply(Move m) const;
	bool solved() const;
	void print() const;
private:
	std::vector<Piece> edges;
	std::vector<Piece> corners;
};


