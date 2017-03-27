/**
 * Unit Tests for Piezas
**/

#include <gtest/gtest.h>
#include "Piezas.h"
 
class PiezasTest : public ::testing::Test
{
	protected:
		PiezasTest(){} //constructor runs before each test
		virtual ~PiezasTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor) 
};

TEST(PiezasTest, sanityCheck)
{
	ASSERT_TRUE(true);
}

TEST(PiezasTest, BoardIsClear)
{
	Piezas p;
	ASSERT_EQ(p.pieceAt(0,0), Blank);
}

TEST(PiezasTest, OoBTopLeftPiece)
{
	Piezas p;
	ASSERT_EQ(p.pieceAt(3,0), Invalid);
}

TEST(PiezasTest, OoBTopRightPiece)
{
	Piezas p;
	ASSERT_EQ(p.pieceAt(3,4), Invalid);
}

TEST(PiezasTest, OoBBottomLeftPiece)
{
	Piezas p;
	ASSERT_EQ(p.pieceAt(-1,0), Invalid);
}

TEST(PiezasTest, OoBBottomRightPiece)
{
	Piezas p;
	ASSERT_EQ(p.pieceAt(0,4), Invalid);
}

TEST(PiezasTest, DropPiece)
{
	Piezas p;
	p.dropPiece(0);
	ASSERT_EQ(p.pieceAt(0,0), X);
}

TEST(PiezasTest, DropPieceSameCol)
{
	Piezas p;
	p.dropPiece(0);
	p.dropPiece(0);
	ASSERT_EQ(p.pieceAt(1,0), O);
}

TEST(PiezasTest, DropPieceSameColx4)
{
	Piezas p;
	p.dropPiece(0);
	p.dropPiece(0);
	p.dropPiece(0);
	ASSERT_EQ(p.dropPiece(0), Blank);
}

TEST(PiezasTest, DropPieceOoBLeft)
{
	Piezas p;
	ASSERT_EQ(p.dropPiece(-1), Invalid);
}

TEST(PiezasTest, DropPieceOobRight)
{
	Piezas p;
	ASSERT_EQ(p.dropPiece(4), Invalid);
}

TEST(PiezasTest, BoardClears)
{
	Piezas p;
	p.dropPiece(1);
	p.reset();
	ASSERT_EQ(p.pieceAt(0,1), Blank);
}

TEST(PiezasTest, FillBoard)
{
	Piezas p;
	p.dropPiece(0);
	p.dropPiece(1);
	p.dropPiece(2);
	ASSERT_EQ(p.dropPiece(3), O);
}

TEST(PiezasTest, GameStateBoardNotFilled)
{
	Piezas p;
	ASSERT_EQ(p.gameState(), Invalid);
}

TEST(PiezasTest, XWinsByRow)
{
	Piezas p;
	p.dropPiece(0);
	p.dropPiece(0);
	p.dropPiece(1);
	p.dropPiece(1);
	p.dropPiece(2);
	p.dropPiece(2);
	p.dropPiece(3);
	p.dropPiece(1);
	p.dropPiece(3);
	p.dropPiece(3);
	p.dropPiece(0);
	p.dropPiece(2);
	ASSERT_EQ(p.gameState(), X);
}

TEST(PiezasTest, TieGameRowandColE3)
{
	Piezas p;
	p.dropPiece(0);
	p.dropPiece(1);
	p.dropPiece(0);
	p.dropPiece(1);
	p.dropPiece(0);
	p.dropPiece(3);
	p.dropPiece(2);
	p.dropPiece(2);
	p.dropPiece(1);
	p.dropPiece(3);
	p.dropPiece(3);
	p.dropPiece(2);
	ASSERT_EQ(p.gameState(), Blank);
}

TEST(PiezasTest, OWinsWith3)
{
	Piezas p;
	p.dropPiece(0);
	p.dropPiece(1);
	p.dropPiece(0);
	p.dropPiece(1);
	p.dropPiece(1);
	p.dropPiece(2);
	p.dropPiece(2);
	p.dropPiece(3);
	p.dropPiece(3);
	p.dropPiece(3);
	p.dropPiece(2);
	p.dropPiece(0);
	ASSERT_EQ(p.gameState(), O);
}

TEST(PiezasTest, GameStateOnlyOneRowandColFilled)
{
	Piezas p;
	p.dropPiece(0);
	p.dropPiece(0);
	p.dropPiece(0);
	p.dropPiece(1);
	p.dropPiece(2);
	p.dropPiece(3);
	ASSERT_EQ(p.gameState(), Invalid);
}

TEST(PiezasTest, GameStateLastSpotEmpty)
{
	Piezas p;
	p.dropPiece(0);
	p.dropPiece(0);
	p.dropPiece(0);
	p.dropPiece(1);
	p.dropPiece(1);
	p.dropPiece(1);
	p.dropPiece(2);
	p.dropPiece(2);
	p.dropPiece(2);
	p.dropPiece(3);
	p.dropPiece(3);
	ASSERT_EQ(p.gameState(), Invalid);
}

// The tests past this point are intended to get more code coverage
TEST(PiezasTest, GameStateLastThreeO)
{
	Piezas p;
	p.dropPiece(0);
	p.dropPiece(1);
	p.dropPiece(0);
	p.dropPiece(2);
	p.dropPiece(0);
	p.dropPiece(3);
	ASSERT_EQ(p.gameState(), Invalid);
}

TEST(PiezasTest, GameStateLastTwoO)
{
	Piezas p;
	p.dropPiece(0);
	p.dropPiece(3);
	p.dropPiece(0);
	p.dropPiece(2);
	ASSERT_EQ(p.gameState(), Invalid);
}

TEST(PiezasTest, GameStateMiddleTwoO)
{
	Piezas p;
	p.dropPiece(0);
	p.dropPiece(1);
	p.dropPiece(3);
	p.dropPiece(2);
	ASSERT_EQ(p.gameState(), Invalid);
}

TEST(PiezasTest, GameStateMoreCov)
{
	Piezas p;
	p.dropPiece(0);
	p.dropPiece(0);
	p.dropPiece(1);
	p.dropPiece(1);
	p.dropPiece(2);
	p.dropPiece(3);
	p.dropPiece(3);
	ASSERT_EQ(p.gameState(), Invalid);
}

TEST(PiezasTest, GameStateXConditions)
{
	Piezas p;
	p.dropPiece(1);
	p.dropPiece(0);
	p.dropPiece(2);
	p.dropPiece(1);
	p.dropPiece(3);
	p.dropPiece(0);
	p.dropPiece(2);
	p.dropPiece(0);
	p.dropPiece(3);
	ASSERT_EQ(p.gameState(), Invalid);
}

TEST(PiezasTest, GameStateXsMiddleofRow)
{
	Piezas p;
	p.dropPiece(1);
	p.dropPiece(0);
	p.dropPiece(2);
	ASSERT_EQ(p.gameState(), Invalid);
}

