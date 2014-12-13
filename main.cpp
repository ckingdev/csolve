#include "Puzzle.hpp"

int main()
{
	Puzzle p;
	Piece c5 = {5, {5, 0}};
	Piece c6 = {6, {6, 0}};
	Piece c7 = {7, {7, 0}};
	Piece e6 = {6, {6, 0}};
	Piece e9 = {9, {9, 0}};
	Piece e10 = {10, {10, 0}};
	p.add_corner(c5);
	p.add_corner(c6);
	p.add_corner(c7);
	p.add_edge(e6);
	p.add_edge(e9);
	p.add_edge(e10);
	p.print();
	Move m;
	m.corners[5] = {6, 2};
	m.corners[6] = {2, 1};
	m.edges[6] = {10, 0};
	m.edges[9] = {6, 0};
	m.edges[10] = {2, 0};
	p = p.apply(m);
	p.print();
	return 0;
}