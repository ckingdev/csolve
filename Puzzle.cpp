#include <iostream>

#include "Puzzle.hpp"

// R U F L D B
// 0 1 2 3 4 5
int base_move_e_ids[6][4] = {{0, 11, 4, 8}, {3, 0, 1, 2}, {1, 8, 5, 9}, 
			     {2, 9, 6, 10}, {5, 4, 7, 6}, {3, 10, 7, 11}};

Location base_move_e_perms[6][4] = {{{11, 0}, {4, 0}, {8, 0}, {0, 0}},
				    {{0, 0}, {1, 1}, {2, 2}, {3, 3}},
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

Move base_moves[6];

void init_moves() 
{
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 4; j++) {
			base_moves[i].corners[base_move_c_ids[i][j]] = base_move_c_perms[i][j];
			base_moves[i].edges[base_move_e_ids[i][j]] = base_move_e_perms[i][j];
		}
	}
	return;
}

/*****************************************************************************/
void Puzzle::add_edge(Piece p)
/*****************************************************************************/
{
	edges.push_back(p);
}


/*****************************************************************************/
void Puzzle::add_corner(Piece p)
/*****************************************************************************/
{
	corners.push_back(p);
}


/*****************************************************************************/
Puzzle Puzzle::apply(Move m) const
/*****************************************************************************/
{	
	Puzzle new_puz;

	Location l = {0, 0}; // these are overwritten each loop. Temp variables.
	Piece p = {0, {0, 0}};

	for (int i = 0; i < corners.size(); i++) {
		if (m.corners.count(corners[i].loc.p)) {		
			l = m.corners[corners[i].loc.p];
			l.o = (l.o + corners[i].loc.o) % 3;
			p.id = corners[i].id;
			p.loc = l;
			new_puz.add_corner(p);
		} else {
			new_puz.add_corner(corners[i]);
		}
	}
	for (int i = 0; i < edges.size(); i++) {
		if (m.edges.count(edges[i].loc.p)) {
			l = m.edges[edges[i].loc.p];
			l.o = (l.o + edges[i].loc.o) % 2;
			p.id = edges[i].id;
			p.loc = l;
			new_puz.add_edge(p);
		} else {
			new_puz.add_edge(edges[i]);
		}
	}
	return new_puz;
}


/*****************************************************************************/
bool Puzzle::solved() const 
/*****************************************************************************/
{
	for (int i = 0; i < corners.size(); i++) {
		if (corners[i].id != corners[i].loc.p || corners[i].loc.o != 0)
			return false;
	}
	for (int i = 0; i < edges.size(); i++) {
		if (edges[i].id != edges[i].loc.p || edges[i].loc.o != 0)
			return false;
	}
	return true;
}

/*****************************************************************************/
void Puzzle::print() const
/*****************************************************************************/
{
	std::cout << "Corners:\n";
	for (int i = 0; i < corners.size(); i++) {
		printf("%i | %i %i\n", corners[i].id, corners[i].loc.p, corners[i].loc.o);
	}

	std::cout << "\nEdges:\n";
	for (int i = 0; i < edges.size(); i++) {
		printf("%i | %i %i\n", edges[i].id, edges[i].loc.p, edges[i].loc.o);
	}
	std::cout << "\n";
}

/*****************************************************************************/
Puzzle get_first_block()
/*****************************************************************************/
{
	Puzzle p;
	Piece c5 = {5, {5, 0}};
	Piece c6 = {6, {6, 0}};
	Piece e6 = {6, {6, 0}};
	Piece e9 = {9, {9, 0}};
	Piece e10 = {10, {10, 0}};
	p.add_corner(c5);
	p.add_corner(c6);
	p.add_edge(e6);
	p.add_edge(e9);
	p.add_edge(e10);
	return p;
}