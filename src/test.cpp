#include "gtest/gtest.h"
#include "Puzzle.hpp"
#include "PruningTable.hpp"
#include <vector>

#include "cereal/archives/binary.hpp"
#include <sstream>

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

TEST(PruningTableTest, PruningTableName) {
    auto name = pruning_table_name<Puzzle<4,4>>(4);
    EXPECT_EQ(name, std::string("4_4_4"));
}

// TODO: Write a test for get_depth_chart()

TEST(PruningTableTest, CrossDepth5CorrectHTM) {
    auto p = get_cross();
    std::vector<Move> moves = get_3x3_h_turns();
    auto pt = gen_pruning_table(p, 5, moves);
    auto depth_chart = get_depth_chart<Puzzle<4, 0> >(pt);
    EXPECT_EQ(1, depth_chart[0]);
    EXPECT_EQ(15, depth_chart[1]);
    EXPECT_EQ(158, depth_chart[2]);
    EXPECT_EQ(1394, depth_chart[3]);
    EXPECT_EQ(9809, depth_chart[4]);
    EXPECT_EQ(46381, depth_chart[5]);
}

// edges only
TEST(PruningTableTest, CrossDepth5CorrectQTM) {
    auto p = get_cross();
    std::vector<Move> moves = get_3x3_q_turns();
    auto pt = gen_pruning_table(p, 5, moves);
    auto depth_chart = get_depth_chart<Puzzle<4, 0> >(pt);
    EXPECT_EQ(1, depth_chart[0]);
    EXPECT_EQ(10, depth_chart[1]);
    EXPECT_EQ(73, depth_chart[2]);
    EXPECT_EQ(500, depth_chart[3]);
    EXPECT_EQ(3078, depth_chart[4]);
    EXPECT_EQ(15528, depth_chart[5]);
}

// corner and edge
TEST(PruningTableTest, 2x1TableSizeCorrect) {
    auto p = get_2x1();
    auto base_moves = get_3x3_h_turns();
    auto pt = gen_pruning_table(p, 6, base_moves);
    EXPECT_EQ(576, pt.size());
}

// corners only
TEST(PruningTableTest, 3CornerTableSizeCorrect) {
    Puzzle<0, 3> p;
    p.add_corner(0, Piece{ 0, { 0, 0 } });
    p.add_corner(1, Piece{ 1, { 1, 0 } });
    p.add_corner(2, Piece{ 2, { 2, 0 } });
    auto base_moves = get_3x3_h_turns();
    auto pt = gen_pruning_table(p, 6, base_moves);
    EXPECT_EQ(9072, pt.size());
}

TEST(PruningTableTest, Serialization) {
    auto p = get_cross();
    auto moves = get_3x3_q_turns();
    auto pt = gen_pruning_table(p, 3, moves);

    std::stringstream ss;
    {
        cereal::BinaryOutputArchive oarchive(ss);
        oarchive(pt);
    }

    decltype(p)::PruningTable loaded_pt;
    {
        cereal::BinaryInputArchive iarchive(ss);
        iarchive(loaded_pt);
    }

    EXPECT_EQ(pt, loaded_pt);
}