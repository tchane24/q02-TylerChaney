#include "Piezas.h"
#include <vector>
/** CLASS Piezas
 * Class for representing a Piezas vertical board, which is roughly based
 * on the game "Connect Four" where pieces are placed in a column and 
 * fall to the bottom of the column, or on top of other pieces already in
 * that column. For an illustration of the board, see:
 *  https://en.wikipedia.org/wiki/Connect_Four
 *
 * Board coordinates [row,col] should match with:
 * [2,0][2,1][2,2][2,3]
 * [1,0][1,1][1,2][1,3]
 * [0,0][0,1][0,2][0,3]
 * So that a piece dropped in column 2 should take [0,2] and the next one
 * dropped in column 2 should take [1,2].
**/


/**
 * Constructor sets an empty board (default 3 rows, 4 columns) and 
 * specifies it is X's turn first
**/
Piezas::Piezas()
{
	board.resize(BOARD_ROWS, std::vector<Piece>(BOARD_COLS, Blank));
	turn = O; // Setting turn to 0 because toggleTurn is called on each drop
		// Therefore, when the first piece is dropped turn will be X
};

/**
 * Resets each board location to the Blank Piece value, with a board of the
 * same size as previously specified
**/
void Piezas::reset()
{
	for(int i=0; i<BOARD_ROWS; i++)
	{
		for(int j=0; j<BOARD_COLS; j++)
		{
			board[i][j] = Blank;
		}
	}
};

/**
 * Places a piece of the current turn on the board, returns what
 * piece is placed, and toggles which Piece's turn it is. dropPiece does 
 * NOT allow to place a piece in a location where a column is full.
 * In that case, placePiece returns Piece Blank value 
 * Out of bounds coordinates return the Piece Invalid value
 * Trying to drop a piece where it cannot be placed loses the player's turn
**/ 
Piece Piezas::dropPiece(int column)
{
	if(turn == X)
		turn = O;
	else if(turn == O)
		turn = X;
	if(column > 3 || column < 0)
		return Invalid;
	if(board[0][column] == Blank)
	{
		board[0][column] = turn;
		return turn;
	}
	else if(board[1][column] == Blank)
	{
		board[1][column] = turn;
		return turn;
	}
	else if(board[2][column] == Blank)
	{
		board[2][column] = turn;
		return turn;
	}
	return Blank;
};

/**
 * Returns what piece is at the provided coordinates, or Blank if there
 * are no pieces there, or Invalid if the coordinates are out of bounds
**/
Piece Piezas::pieceAt(int row, int column)
{
	if(row >= 0 && row < 3 && column >= 0 && column < 4)
		return board[row][column];
	// Should already return Blank if there is no piece there
	return Invalid;
};

/**
 * Returns which Piece has won, if there is a winner, Invalid if the game
 * is not over, or Blank if the board is filled and no one has won ("tie").
 * For a game to be over, all locations on the board must be filled with X's 
 * and O's (i.e. no remaining Blank spaces). The winner is which player has
 * the most adjacent pieces in a single line. Lines can go either vertically
 * or horizontally. If both X's and O's have the same max number of pieces in a
 * line, it is a tie.
**/
Piece Piezas::gameState()
{
	for(int i=0; i<BOARD_ROWS; i++)
	{
		for(int j=0; j<BOARD_COLS; j++)
		{
			if(board[i][j] == Blank)
				return Invalid;
		}
	}
	int xHigh = 0;
	int xCur = 0;
	int oHigh = 0;
	int oCur = 0;
	for(int i=0; i<BOARD_COLS; i++)
	{
		if(board[1][i] == X)
		{
			if(board[2][i] == X && board[0][i] == X)
				xCur = 3;
			else if(board[2][i] == X || board[0][i] == X)
				xCur = 2;
		}
		else if(board[1][i] == O)
		{
			if(board[2][i] == O && board[0][i] == O)
				oCur = 3;
			else if(board[2][i] == O || board[0][i] == O)
				oCur = 2;
		}
		if(xCur > xHigh)
			xHigh = xCur;
		if(oCur > oHigh)
			oHigh = oCur;
	}
	for(int i=0; i<BOARD_ROWS; i++)
	{
		if(board[i][0] == X && board[i][1] == X)
		{
			if(board[i][2] == X)
			{
				if(board[i][3] == X)
					xCur = 4;
				else xCur = 3;
			}
			else xCur = 2;
		}
		else if(board[i][1] == X && board[i][2] == X)
		{
			if(board[i][3] == X)
				xCur = 3;
			else xCur = 2;
		}
		else if(board[i][2] == X && board[i][3] == X)
			xCur = 2;
		if(board[i][0] == O && board[i][1] == O)
		{
			if(board[i][2] == O)
			{
				if(board[i][3] == O)
					oCur = 4;
				else oCur = 3;
			}
			else oCur = 2;
		}
		else if(board[i][1] == O && board[i][2] == O)
		{
			if(board[i][3] == O)
				oCur = 3;
			else oCur = 2;
		}
		else if(board[i][2] == O && board[i][3] == O)
			oCur = 2;
		if(xCur > xHigh)
			xHigh = xCur;
		if(oCur > oHigh)
			oHigh = oCur;
	}
	if(xHigh == oHigh)
		return Blank;
	if(xHigh > oHigh)
		return X;
	return O;
};
