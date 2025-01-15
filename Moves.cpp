#include <iostream>
#include "Moves.h"

using namespace std;

const ChessPiece* isDiagonal(Pos src, Pos dest, const ChessPiece* board[][8]) {
	//check destination is on a diagonal path
	if (abs(dest.row - src.row) != abs(dest.col - src.col)) { 
		return board[src.row][src.col];	
	}
	//determine the direction of the diagonal
	int rowStep = (dest.row > src.row) ? 1 : -1;
	int colStep = (dest.col > src.col) ? 1 : -1;

	//traverse the diagonal path from source to destination
	for (int row = src.row + rowStep, col = src.col + colStep;
			row != dest.row || col != dest.col;
			row += rowStep, col += colStep) {
		//check if the path is clear else return piece in path
		if (board[row][col]) {
			return board[row][col];
		}
	}
	return NULL;
}

const ChessPiece* isVertical(Pos src, Pos dest, const ChessPiece* board[][8]) {
	//check if destination is in same column as source
	if (src.col != dest.col) {
		return board[src.row][src.col];
	}
	//determine the direction of the vertical path
	int rowStep = (dest.row > src.row) ? 1 : -1;

	//traverse the vertical path from source to destination
	for (int row = src.row + rowStep; row != dest.row; row += rowStep) {
		//check if the path is clear else return piece in path
		if (board[row][src.col]) {
			return board[row][src.col];
		}
	}
	return NULL;
}

const ChessPiece* isHorizontal(Pos src, Pos dest, const ChessPiece* board[][8]) {
	//check if destination is in same row as source
	if (src.row != dest.row) {
		return board[src.row][src.col];
	}
	//determine the direction of the horizontal path
	int colStep = (dest.col > src.col) ? 1 : -1;

	//traverse the horizontal path from source to destination
	for (int col = src.col + colStep; col != dest.col; col += colStep) {
		//check if the path is clear else return piece in path
		if (board[src.row][col]) {
			return board[src.row][col];
		}
	}
	return NULL;
}

bool isL(Pos src, Pos dest) {
	if (!(abs(src.row - dest.row) == 2 && abs(src.col - dest.col) == 1)
			&& !(abs(src.row - dest.row) == 1 && abs(src.col - dest.col) == 2)) {
		return false;
	}
	return true;
}

const ChessPiece* isDiagonalCheck(Pos src, Pos dest, const ChessPiece* board[][8], 
		ChessBoard::COLOUR sideToMove, char except) {
	//if source equals destination, it is not a valid move
	if (src == dest) {
		return NULL;
	}
	//get any piece that is between source and destination
	const ChessPiece* takingPiece = isDiagonal(src, dest, board);
	//check if that piece can take the piece at the source location
	return canCheck(takingPiece, src, dest, board, sideToMove, except);
}

const ChessPiece* isVerticalCheck(Pos src, Pos dest, const ChessPiece* board[][8], 
		ChessBoard::COLOUR sideToMove, char except) {
	//if source equals destination, it is not a valid move
	if (src == dest) {
		return NULL;
	}
	//get any piece that is between source and destination
	const ChessPiece* takingPiece = isVertical(src, dest, board);
	//check if that piece can take the piece at the source location
	return canCheck(takingPiece, src, dest, board, sideToMove, except);
}

const ChessPiece* isHorizontalCheck(Pos src, Pos dest, const ChessPiece* board[][8], 
		ChessBoard::COLOUR sideToMove, char except) {
	//if source equals destination, it is not a valid move
	if (src == dest) {
		return NULL;
	}
	//get any piece that is between source and destination
	const ChessPiece* takingPiece = isHorizontal(src, dest, board);
	//check if that piece can take the piece at the source location
	return canCheck(takingPiece, src, dest, board, sideToMove, except);
}

const ChessPiece* isLCheck(Pos pos, const ChessPiece* board[][8], 
						   ChessBoard::COLOUR sideToMove) {
	//setup an array of possible locations relative to pos
	const int LMoves[][2] = {
		{-2, -1}, {-2, 1},
		{-1, -2}, {-1, 2},
		{1, -2}, {1, 2},
		{2, -1}, {2, 1}
	};
	//for each possible L position
	for (int i = 0; i < 8; i++) {
		int row = pos.row + LMoves[i][0];
		int col = pos.col + LMoves[i][1];
		//if it is on the board
		if ((0 <= row && row < 8) && (0 <= col && col < 8)) {
			const ChessPiece* takingPiece = board[row][col];
			//ensure that takingPiece is a knight and can take the piece at pos 
			if (takingPiece && (takingPiece->getSymbol() == 'n' 
						 	||  takingPiece->getSymbol() == 'N')) {
				if (canCheck(takingPiece, pos, Pos(-1, -1), board, sideToMove)) {
					return takingPiece;
				}
			}
		}
	}
	//if there are no knights in L positions around pos, return NULL
	return NULL;
}

const ChessPiece* canCheck(const ChessPiece* takingPiece, Pos src, Pos dest, 
		const ChessPiece* board[][8], ChessBoard::COLOUR sideToMove, char except) {
	//if takingPiece is a piece that should not be moved, return NULL
	if (takingPiece && (takingPiece->getSymbol() == except 
					||  takingPiece->getSymbol() == except + 32)) {
		return NULL;
	}
	//if there are no pieces up to the edge and no pieces at the edge, return NULL
	if (!takingPiece && !board[dest.row][dest.col]) {
		return NULL;
	} 
	//else assume that the piece at the edge is the takingPiece
	else if (!takingPiece) {
		takingPiece = board[dest.row][dest.col]; 
	}
	//if the piece at src is taken by the opponent takingPiece or if takingPiece is just 
	//moving to src location
	if ((board[src.row][src.col] 
			&& takingPiece->getColour() != board[src.row][src.col]->getColour())
			|| (board[src.row][src.col] == NULL && takingPiece->getColour() == sideToMove)) {
		//if the move is valid
		if (((ChessPiece*)takingPiece)->isValidMove(takingPiece->getPos(), src, board)) { 
			//takingPiece can take the piece at src, return the taking Piece
			return takingPiece;
		}
	}
	//if takingPiece cannot move to src location, return NULL
	return NULL;
}

