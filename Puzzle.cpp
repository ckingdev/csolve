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
		// base_moves.push_back(two);
		base_moves.push_back(prime);
	}
	printf("Using %lu moves...\n", base_moves.size());
	return base_moves;
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
Puzzle Puzzle::apply(const Move &m) const
/*****************************************************************************/
{	
	Puzzle new_puz;

	Location l = {0, 0}; // these are overwritten each loop. Temp variables.
	Piece p = {0, {0, 0}};

	for (auto & corner : corners) {

		if (m.corners.count(corner.loc.p)) {		
			l = m.corners.at(corner.loc.p);
			l.o = (l.o + corner.loc.o) % 3;
			p.id = corner.id;
			p.loc = l;
			new_puz.add_corner(p);
		} else {
			new_puz.add_corner(corner);
		}
	}
	for (auto & edge : edges) {
		if (m.edges.count(edge.loc.p)) {
			l = m.edges.at(edge.loc.p);
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


/*****************************************************************************/
bool Puzzle::solved() const 
/*****************************************************************************/
{
	std::size_t len = corners.size();
	for (uint i = 0; i < len; i++) { // change these to auto &i : whatever
		if (corners[i].id != corners[i].loc.p || corners[i].loc.o != 0)
			return false;
	}
	len = edges.size();
	for (uint i = 0; i < len; i++) {
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
	for (uint i = 0; i < corners.size(); i++) { // iterator again
		printf("%i | %i %i\n", corners[i].id, corners[i].loc.p, corners[i].loc.o);
	}

	std::cout << "\nEdges:\n";
	for (uint i = 0; i < edges.size(); i++) {
		printf("%i | %i %i\n", edges[i].id, edges[i].loc.p, edges[i].loc.o);
	}
	std::cout << "\n";
}

const std::vector<Piece> &Puzzle::get_edges() const
{
	return edges;
}

const std::vector<Piece> &Puzzle::get_corners() const
{
	return corners;
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

Puzzle get_cross()
{
	Puzzle p;
	Piece e4 = {4, {4, 0}};
	Piece e5 = {5, {5, 0}};
	Piece e6 = {6, {6, 0}};
	Piece e7 = {7, {7, 0}};
	p.add_edge(e4);
	p.add_edge(e5);
	p.add_edge(e6);
	p.add_edge(e7);
	return p;
}

bool operator != (const Piece a, const Piece b)
{
	return !(a.id == b.id && a.loc.o == b.loc.o && a.loc.p == b.loc.p);
}

bool operator ==(const Puzzle &a, const Puzzle &b)
{
	auto &a_edges = a.get_edges();
	auto &a_corners = a.get_corners();
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

std::vector<Puzzle> Puzzle::apply_moves(const std::vector<Move> &move_list) const
{
	std::vector<Puzzle> applied;
	for (std::size_t i = 0; i < move_list.size(); i++) { // iterator
		applied.emplace_back(apply(move_list[i]));
	}
	return applied;
}