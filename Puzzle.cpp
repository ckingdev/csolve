#include <iostream>

#include "Puzzle.hpp"

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
Puzzle Puzzle::apply(Move m) const {
/*****************************************************************************/

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