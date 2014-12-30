#ifndef PUZZLE_HPP
#define PUZZLE_HPP

#include <array>
#include <vector>
#include <cassert>
#include <unordered_map>
#include <iostream>
#include "include/cereal/types/array.hpp"
#include "include/cereal/types/unordered_map.hpp"

// Location stores a place on the puzzle and a twist.
struct Location {
    char p;
    char o;

    template <class Archive> void serialize(Archive &ar) { ar(p, o); }
};

// Piece stores an identifier (i.e. color combination) and a location.
struct Piece {
    char id;
    Location loc;

    template <class Archive> void serialize(Archive &ar) { ar(id, loc); }
};

bool operator!=(const Piece a, const Piece b);

// Move is a mapping between a place on the puzzle and its transformation.a
struct Move {
    std::array<Location, 12> edges;
    std::array<Location, 8> corners;
};

Move new_move();

// get_3x3_h_turns() gives a vector of unit moves in the 3x3 half turn metric.
std::vector<Move> get_3x3_h_turns();

// get_3x3_h_turns() gives a vector of unit moves in the 3x3 quarter turn
// metric.
std::vector<Move> get_3x3_q_turns();

// Returns a vector of the moves in <R, U, F> in htm.
std::vector<Move> get_2x2_h3gen_turns();

// compose() returns a new Move that is the composition of a and b.
Move compose(const Move &a, const Move &b);

// compose_seq() returns a new Move that is the composition of a vector of Move.
Move compose_seq(const std::vector<Move> &seq);

// hashes a Puzzle object.
template <typename puzzle> class PuzzleHasher {
  public:
    std::size_t operator()(puzzle const &p) const;
};

// Represents a bag of edges and a bag of corners, each of which is a Piece.
template <std::size_t edges_num, std::size_t corners_num> class Puzzle {
  public:
    typedef std::unordered_map<Puzzle, int, PuzzleHasher<Puzzle> > PruningTable;

    // Adds an edge p to the puzzle in position i of the array.
    void add_edge(int i, Piece p);

    // Adds a corner p to the puzzle in position i of the array.
    void add_corner(int i, Piece p);

    // Applies a move m to the puzzle and returns the result.
    Puzzle apply(const Move &m) const;

    // Equivalent to using apply() with each move in the list and putting the
    // results in a vector.
    std::vector<Puzzle> apply_moves(const std::vector<Move> &move_list) const;

    bool solved() const;
    bool operator==(const Puzzle &b) const;

    void print() const;

    // Returns an array of the edges stored in the puzzle.
    const std::array<Piece, edges_num> &get_edges() const { return edges; }

    // Returns an array of the corners stored in the puzzle.
    const std::array<Piece, corners_num> &get_corners() const {
        return corners;
    }

    // Enables the serialization and saving to disk of the PruningTable.
    template <class Archive> void serialize(Archive &ar) { ar(edges, corners); }

  private:
    std::array<Piece, edges_num> edges;
    std::array<Piece, corners_num> corners;
};

// Returns a puzzle with only the pieces corresponding to a fixed Roux f.b.
Puzzle<3, 2> get_first_block();

// Returns a puzzle with only the pieces corresponding to a Fridrich cross.
Puzzle<4, 0> get_cross();

// Returns a puzzle with all 3x3 cube pieces.
Puzzle<12, 8> get_full();

// Returns a puzzle with only one corner and one edge.
Puzzle<1, 1> get_2x1();

// Returns a puzzle with only corners.
Puzzle<0, 8> get_corners();

Puzzle<0, 4> get_4_corners();

#include "PuzzleImpl.hpp"

#endif
