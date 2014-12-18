#include <iostream>
#include <vector>
#include "Puzzle.hpp"

// R U F L D B
// 0 1 2 3 4 5
int base_move_e_ids[6][4] = {{0, 11, 4, 8}, {3, 0, 1, 2}, {1, 8, 5, 9}, 
			     {2, 9, 6, 10}, {5, 4, 7, 6}, {3, 10, 7, 11}};

Location base_move_e_perms[6][4] = {{{11, 0}, {4, 0}, {8, 0}, {0, 0}},
				    {{0, 0}, {1, 0}, {2, 0}, {3, 0}},
				    {{8, 1}, {5, 1}, {9, 1}, {1, 1}},
				    {{9, 0}, {6, 0}, {10, 0}, {2, 0}},
				    {{4, 0}, {7, 0}, {6, 0}, {5, 0}},
				    {{10, 1}, {7, 1}, {11, 1}, {3, 1}}};

int base_move_c_ids[6][4] = {{0, 3, 7, 4}, {2, 3, 0, 1}, {1, 0, 4, 5}, 
			     {2, 1, 5, 6}, {5, 4, 7, 6}, {3, 2, 6, 7}};

Location base_move_c_perms[6][4] = {{{3, 1}, {7, 2}, {4, 1}, {0, 2}},
				    {{3, 0}, {0, 0}, {1, 0}, {2, 0}},
				    {{0, 1}, {4, 2}, {5, 1}, {1, 2}},
				    {{1, 1}, {5, 2}, {6, 1}, {2, 2}},
				    {{4, 0}, {7, 0}, {6, 0}, {5, 0}},
				    {{2, 1}, {6, 2}, {7, 1}, {3, 2}}};


Move compose(const Move &a, const Move &b)
{
	Move ab;
	for (int i = 0; i < 12; i++) {
		if (a.edges.count(i)) {
			Location tmp = a.edges.at(i);
			if (b.edges.count(tmp.p)) {
				tmp = b.edges.at(tmp.p);
				tmp.o = (tmp.o + a.edges.at(i).o) % 2;
				ab.edges[i] = tmp;
			} else {
				ab.edges[i] = tmp;
			}
		} else if (b.edges.count(i)) {
			ab.edges[i] = b.edges.at(i);
		}
	}

	for (int i = 0; i < 8; i++) {
		if (a.corners.count(i)) {
			Location tmp = a.corners.at(i);
			if (b.corners.count(tmp.p)) {
				tmp = b.corners.at(tmp.p);
				tmp.o = (tmp.o + a.corners.at(i).o) % 3;
				ab.corners[i] = tmp;
			} else {
				ab.corners[i] = tmp;
			}
		} else if (b.corners.count(i)) {
			ab.corners[i] = b.corners.at(i);
		}
	}	
	return ab;
}

std::vector<Move> init_three_moves() 
{
	std::vector<Move> base_moves;
	for (int i = 0; i < 6; i++) {
		Move tmp;
		for (int j = 0; j < 4; j++) {
			tmp.corners[base_move_c_ids[i][j]] = base_move_c_perms[i][j];
			tmp.edges[base_move_e_ids[i][j]] = base_move_e_perms[i][j];
		}
		base_moves.push_back(tmp);
	}

	for (int i = 0; i < 6; i++) {
		Move two = compose(base_moves[i], base_moves[i]);
		Move prime = compose(two, base_moves[i]);
		//base_moves.push_back(two);
		base_moves.push_back(prime);
	}
	return base_moves;
}

/*****************************************************************************/
Puzzle<3,2> get_first_block()
/*****************************************************************************/
{
	Puzzle<3,2> p;
	Piece c5 = {5, {5, 0}};
	Piece c6 = {6, {6, 0}};
	Piece e6 = {6, {6, 0}};
	Piece e9 = {9, {9, 0}};
	Piece e10 = {10, {10, 0}};
	p.add_corner(0, c5);
	p.add_corner(1, c6);
	p.add_edge(0, e6);
	p.add_edge(1, e9);
	p.add_edge(2, e10);
	return p;
}

Puzzle<4,0> get_cross()
{
	Puzzle<4,0> p;
	Piece e4 = {4, {4, 0}};
	Piece e5 = {5, {5, 0}};
	Piece e6 = {6, {6, 0}};
	Piece e7 = {7, {7, 0}};
	p.add_edge(0, e4);
	p.add_edge(1, e5);
	p.add_edge(2, e6);
	p.add_edge(3, e7);
	return p;
}

Puzzle<12,8> get_full()
{
	Puzzle<12,8> p;
	for (char i = 0; i < 12; i++) {
		p.add_edge(i, Piece{i, {i, 0}});
	}
	for (char i = 0; i < 8; i++) {
		p.add_corner(i, Piece{i, {i, 0}});
	}
	return p;
}

bool operator != (const Piece a, const Piece b)
{
	return !(a.id == b.id && a.loc.o == b.loc.o && a.loc.p == b.loc.p);
}
