#include "gtest/gtest.h"
#include "Puzzle.hpp"
#include <vector>

TEST(MovesTest, FourMovesIsIdentity)
{
	Puzzle p = get_full();
	std::vector<Move> moves = init_three_moves();
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

TEST(MovesTest, MovesLen18)
{
	std::vector<Move> moves = init_three_moves();
	EXPECT_EQ(18, moves.size());
}

TEST(PuzzleTest, IdentityIsSolved)
{
	auto p = get_full();
	EXPECT_TRUE(p.solved());
}

TEST(PuzzleTest, CrossIsSolved)
{
	auto p = get_cross();
	EXPECT_TRUE(p.solved());
}