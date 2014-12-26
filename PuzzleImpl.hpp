#ifndef PUZZLE_HPP
#error "this file is included by Puzzle.hpp, don't include this directly."
#endif

#ifndef PUZZLE_IMPL_HPP
#define PUZZLE_IMPL_HPP

template <typename puzzle>
std::size_t PuzzleHasher<puzzle>::operator()(puzzle const &p) const {
    std::size_t seed = 0;
    const auto &edges = p.get_edges();
    const auto &corners = p.get_corners();
    for (unsigned int i = 0; i < edges.size(); i++) {
        seed ^= edges[i].loc.p + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        seed ^= edges[i].loc.o + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }
    for (unsigned int i = 0; i < corners.size(); i++) {
        seed ^= corners[i].loc.p + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        seed ^= corners[i].loc.o + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }
    return seed;
}

template <std::size_t edges_num, std::size_t corners_num>
void Puzzle<edges_num, corners_num>::add_edge(int i, Piece p) {
    edges[i] = p;
}

template <std::size_t edges_num, std::size_t corners_num>
void Puzzle<edges_num, corners_num>::add_corner(int i, Piece p) {
    corners[i] = p;
}

// template <std::size_t edges_num, std::size_t corners_num>
// Puzzle<edges_num, corners_num>
// Puzzle<edges_num, corners_num>::apply(const Move &m) const {
//     Puzzle new_puz;

//     Location l = { 0, 0 }; // these are overwritten each loop. Temp variables.
//     Piece p = { 0, { 0, 0 } };

//     auto corners_end = m.corners.end();
//     auto edges_end = m.edges.end();

//     int i = 0;
//     for (auto &corner : corners) {
//         auto corner_iter = m.corners.find(corner.loc.p);
//         if (corner_iter != corners_end) {
//             l = corner_iter->second;
//             l.o = (l.o + corner.loc.o) % 3;
//             p.id = corner.id;
//             p.loc = l;
//             new_puz.add_corner(i, p);
//         } else {
//             new_puz.add_corner(i, corner);
//         }
//         i++;
//     }

//     i = 0;
//     for (auto &edge : edges) {
//         auto edge_iter = m.edges.find(edge.loc.p);
//         if (edge_iter != edges_end) {
//             l = edge_iter->second;
//             l.o = (l.o + edge.loc.o) % 2;
//             p.id = edge.id;
//             p.loc = l;
//             new_puz.add_edge(i, p);
//         } else {
//             new_puz.add_edge(i, edge);
//         }
//         i++;
//     }
//     return new_puz;
// }

template <std::size_t edges_num, std::size_t corners_num>
Puzzle<edges_num, corners_num>
Puzzle<edges_num, corners_num>::apply(const Move &m) const {
    Puzzle new_puz;

    Piece p = { 0, { 0, 0 } };
    int i = 0;
    for (auto &edge : edges) {
        p.loc.p = m.edges[edge.loc.p].p;
        p.loc.o = (m.edges[edge.loc.p].o + edge.loc.o) % 2;
        p.id = edge.id;
        new_puz.add_edge(i, p);
        i++;
    }
    i = 0;
    for (auto &corner : corners) {
        p.loc.p = m.corners[corner.loc.p].p;
        p.loc.o = (m.corners[corner.loc.p].o + corner.loc.o) % 3;
        p.id = corner.id;
        new_puz.add_corner(i, p);
        i++;
    }
    return new_puz;
}


template <std::size_t edges_num, std::size_t corners_num>
std::vector<Puzzle<edges_num, corners_num> >
Puzzle<edges_num, corners_num>::apply_moves(
    const std::vector<Move> &move_list) const {
    std::vector<Puzzle> applied;
    applied.reserve(20);
    std::size_t len = move_list.size();
    for (std::size_t i = 0; i < len; i++) {
        applied.emplace_back(apply(move_list[i]));
    }
    return applied;
}

template <std::size_t edges_num, std::size_t corners_num>
bool Puzzle<edges_num, corners_num>::solved() const {

    std::size_t len = corners.size();
    for (unsigned int i = 0; i < len; i++) {
        if (corners[i].id != corners[i].loc.p || corners[i].loc.o != 0)
            return false;
    }
    len = edges.size();
    for (unsigned int i = 0; i < len; i++) {
        if (edges[i].id != edges[i].loc.p || edges[i].loc.o != 0)
            return false;
    }
    return true;
}

template <std::size_t edges_num, std::size_t corners_num>
bool Puzzle<edges_num, corners_num>::
operator==(const Puzzle<edges_num, corners_num> &b) const {
    auto &a_edges = get_edges();
    auto &a_corners = get_corners();
    auto &b_edges = b.get_edges();
    auto &b_corners = b.get_corners();

    auto len = a_edges.size();
    for (unsigned int i = 0; i < len; i++) {
        if (a_edges[i] != b_edges[i])
            return false;
    }

    len = a_corners.size();
    for (unsigned int i = 0; i < len; i++) {
        if (a_corners[i] != b_corners[i])
            return false;
    }
    return true;
}

template <std::size_t edges_num, std::size_t corners_num>
void Puzzle<edges_num, corners_num>::print() const {
    std::cout << "Corners:\n";
    for (uint i = 0; i < corners.size(); i++) {
        printf("%i | %i %i\n", corners[i].id, corners[i].loc.p,
               corners[i].loc.o);
    }

    std::cout << "\nEdges:\n";
    for (uint i = 0; i < edges.size(); i++) {
        printf("%i | %i %i\n", edges[i].id, edges[i].loc.p, edges[i].loc.o);
    }
    std::cout << "\n";
}

#endif
