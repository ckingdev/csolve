#include "gtest/gtest.h"
#include "Puzzle.hpp"
#include <vector>

TEST(MovesTest, FourMovesIsIdentity) {
    auto p = get_full();
    std::vector<Move> moves = get_3x3_h_turns();
    for (int i = 0; i < 6; i++) {
        p = p.apply(moves[i]);
        EXPECT_FALSE(p.solved());
        p = p.apply(moves[i]);
        EXPECT_FALSE(p.solved());
        p = p.apply(moves[i]);
        EXPECT_FALSE(p.solved());
        p = p.apply(moves[i]);
        EXPECT_TRUE(p.solved());
    }
}

TEST(MovesTest, HTMLen18) {
    std::vector<Move> moves = get_3x3_h_turns();
    EXPECT_EQ(18, moves.size());
}

TEST(MovesTest, QTMLen12) {
    std::vector<Move> moves = get_3x3_q_turns();
    EXPECT_EQ(12, moves.size());
}

TEST(PuzzleTest, IdentityIsSolved) {
    auto p = get_full();
    EXPECT_TRUE(p.solved());
}

TEST(PuzzleTest, CrossIsSolved) {
    auto p = get_cross();
    EXPECT_TRUE(p.solved());
}

// TEST(NSolveTest, SuneIsSevenHTM)
// {
// 	auto p = get_full();
// // Sune R U R' U R U2 R'
// //      0 1 7  1 0 8  7
// 	int sune_codes[7] = {0, 1, 7, 1, 0, 8, 7};
// 	std::vector<Move> sune_moves;
// 	for (int i = 0; i < 7; i++) {
// 		sune_moves.push_back(value_type &&__x)
// 	}
// }
