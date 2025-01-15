#include <iostream>
#include "ChessPiece.h"

using namespace std;

/************ Superclass ChessPiece Implementation ************/

ChessPiece::ChessPiece(Pos _pos, ChessBoard::COLOUR _colour) 
	: pos(_pos), pieceColour(_colour), symbol('-') {};

ChessBoard::COLOUR ChessPiece::getColour() const {
	return pieceColour;
}

char ChessPiece::getSymbol() const {
	return symbol;
}

Pos ChessPiece::getPos() const {
	return pos;
}

void ChessPiece::setPos(Pos newPos) {
	pos = newPos;
}

const ChessPiece* ChessPiece::canBeTaken(Pos pos, const ChessPiece* board[][8], 
										 ChessBoard::COLOUR sideToMove, char except) {
	const ChessPiece* checkingPiece = NULL;
	//check whether piece at pos can be taken horizontally
	checkingPiece = checkHorizontal(pos, board, sideToMove, except);
	if (checkingPiece) {
		return checkingPiece;
	}
	//check whether piece at pos can be taken vertically
	checkingPiece = checkVertical(pos, board, sideToMove, except);
	if (checkingPiece) {
		return checkingPiece;
	}
	//check whether piece at pos can be taken diagonally
	checkingPiece = checkDiagonal(pos, board, sideToMove, except);
	if (checkingPiece) {
		return checkingPiece;
	}
	//check whether piece at pos can be taken by a knight
	checkingPiece = isLCheck(pos, board, sideToMove);
	if (checkingPiece) {
		return checkingPiece;
	}
	//if piece at pos cannot be taken, return NULL
	return checkingPiece;
}

const ChessPiece* ChessPiece::checkHorizontal(Pos pos, const ChessPiece* board[][8],
											ChessBoard::COLOUR sideToMove, char except) {
	const ChessPiece* checkingPiece = NULL;
	//check up to left most square for an attacking piece 
	Pos dest(pos.row, 0);
	checkingPiece = isHorizontalCheck(pos, dest, board, sideToMove, except);
	if (checkingPiece) {
		return checkingPiece;
	}
	//check up to right most square for an attacking piece 
	dest = Pos(pos.row, 7);
	checkingPiece = isHorizontalCheck(pos, dest, board, sideToMove, except);
	if (checkingPiece) {
		return checkingPiece;
	}
	//if there is no piece that can attack horizontally, return NULL
	return checkingPiece;
}

const ChessPiece* ChessPiece::checkVertical(Pos pos, const ChessPiece* board[][8],
											ChessBoard::COLOUR sideToMove, char except) {
	const ChessPiece* checkingPiece = NULL;
	//check up to top most square for an attacking piece 
	Pos dest(0, pos.col);
	checkingPiece = isVerticalCheck(pos, dest, board, sideToMove, except);
	if (checkingPiece) {
		return checkingPiece;
	}
	//check up to bottom most square for an attacking piece 
	dest = Pos(7, pos.col);
	checkingPiece = isVerticalCheck(pos, dest, board, sideToMove, except);
	if (checkingPiece) {
		return checkingPiece;
	}
	//if there is no piece that can attack vertically, return NULL
	return checkingPiece;
}

const ChessPiece* ChessPiece::checkDiagonal(Pos pos, const ChessPiece* board[][8],
											ChessBoard::COLOUR sideToMove, char except) {
	const ChessPiece* checkingPiece = NULL;
	//check up to top left most square for an attacking piece 
	int offset = (pos.col - 0 < pos.row - 0) ? pos.col - 0 : pos.row - 0;
	Pos dest(pos.row - offset, pos.col - offset);
	checkingPiece = isDiagonalCheck(pos, dest, board, sideToMove, except);
	if (checkingPiece) {
		return checkingPiece;
	}
	//check up to top right most square for an attacking piece 
	offset = (7 - pos.col < pos.row - 0) ? 7 - pos.col : pos.row - 0;
	dest = Pos(pos.row - offset, pos.col + offset);
	checkingPiece = isDiagonalCheck(pos, dest, board, sideToMove, except);
	if (checkingPiece) {
		return checkingPiece;
	}
	//check up to bottom right most square for an attacking piece 
	offset = (7 - pos.col < 7 - pos.row) ? 7 - pos.col : 7 - pos.row;
	dest = Pos(pos.row + offset, pos.col + offset);
	checkingPiece = isDiagonalCheck(pos, dest, board, sideToMove, except);
	if (checkingPiece) {
		return checkingPiece;
	}
	//check up to bottom left most square for an attacking piece 
	offset = (pos.col - 0 < 7 - pos.row) ? pos.col - 0 : 7 - pos.row;
	dest = Pos(pos.row + offset, pos.col - offset);
	checkingPiece = isDiagonalCheck(pos, dest, board, sideToMove, except);
	if (checkingPiece) {
		return checkingPiece;
	}
	//if there is no piece that can attack diagonally, return NULL
	return checkingPiece;
}

std::ostream& operator << (std::ostream& output, const ChessPiece& piece) {
	return output << piece.icon;
}

std::ostream& operator << (std::ostream& output, const ChessPiece* piece) {
	//print piece's colour and name if there is a piece, otherwise print NULL
	return piece ? output << piece->pieceColour << "'s " << piece->name 
				: output << "NULL";
}

ChessPiece::~ChessPiece(){};

/**************** Subclass Rook Implementation ****************/

Rook::Rook(Pos _pos, ChessBoard::COLOUR _colour) : ChessPiece(_pos, _colour) {
	name = "Rook";
	symbol = (pieceColour == ChessBoard::WHITE) ? 'R' : 'r';
	icon = (pieceColour == ChessBoard::WHITE) ? "\u2656" : "\u265C";
};

bool Rook::isValidMove(Pos src, Pos dest, const ChessPiece* board[][8]) {
	//check if move is vertical or horizontal
	return isVertical(src, dest, board) == NULL 
			|| isHorizontal(src, dest, board) == NULL;
}

/*************** Subclass Knight Implementation ***************/

Knight::Knight(Pos _pos, ChessBoard::COLOUR _colour) : ChessPiece(_pos, _colour) {
	name = "Knight";
	symbol = (pieceColour == ChessBoard::WHITE) ? 'N' : 'n';
	icon = (pieceColour == ChessBoard::WHITE) ? "\u2658" : "\u265E";
};

bool Knight::isValidMove(Pos src, Pos dest, const ChessPiece* board[][8]) {
	//check if move is L shape
	return isL(src, dest);
}

/*************** Subclass Bishop implementation ***************/

Bishop::Bishop(Pos _pos, ChessBoard::COLOUR _colour) : ChessPiece(_pos, _colour) {
	name = "Bishop";
	symbol = (pieceColour == ChessBoard::WHITE) ? 'B' : 'b';
	icon = (pieceColour == ChessBoard::WHITE) ? "\u2657" : "\u265D";
};

bool Bishop::isValidMove(Pos src, Pos dest, const ChessPiece* board[][8]) {
	//check if move is diagonal
	return isDiagonal(src, dest, board) == NULL;
}

/**************** Subclass Queen implementation ***************/

Queen::Queen(Pos _pos, ChessBoard::COLOUR _colour) : ChessPiece(_pos, _colour) {
	name = "Queen";
	symbol =(pieceColour == ChessBoard::WHITE) ? 'Q' : 'q';
	icon = (pieceColour == ChessBoard::WHITE) ? "\u2655" : "\u265B";
};

bool Queen::isValidMove(Pos src, Pos dest, const ChessPiece* board[][8]) {
	//check if move is diagonal, vertical or horizontal
	return isDiagonal(src, dest, board) == NULL
			|| isVertical(src, dest, board) == NULL 
			|| isHorizontal(src, dest, board) == NULL;
}

/**************** Subclass King implementation ****************/

King::King(Pos _pos, ChessBoard::COLOUR _colour) : ChessPiece(_pos, _colour) {
	name = "King";
	symbol = (pieceColour == ChessBoard::WHITE) ? 'K' : 'k';
	icon = (pieceColour == ChessBoard::WHITE) ? "\u2654" : "\u265A";
	isCastling = false;
};

bool King::isValidMove(Pos src, Pos dest, const ChessPiece* board[][8]) {
	//check if distance is greater than 1
	if (abs(src.row - dest.row) > 1 || abs(src.col - dest.col) > 1) {
		return false;
	}
	//check if move is diagonal, vertical or horizontal
	return  isDiagonal(src, dest, board) == NULL
			|| isVertical(src, dest, board) == NULL 
			|| isHorizontal(src, dest, board) == NULL;
}

bool King::isCastlingMove(Pos src, Pos dest, const ChessPiece* board[][8], 
			const char* castlingState) {
	//check if squares the king moves through can be taken by opponent 
	if (isPathBlocked(src, dest, board)) {
		return false;
	}
	bool canCastle = checkCastlingState(src, dest, board, castlingState);
	//if king can castle and has a direct path, it can make the move
	if (canCastle && (board[dest.row][dest.col] == NULL 
				&& isHorizontal(src, dest, board) == NULL)) {
		isCastling = true;
		return true;
	}
	return false;
}

bool King::isPathBlocked(Pos src, Pos dest, const ChessPiece* board[][8]) {
	//get direction of path
	int colStep = (dest.col > src.col) ? 1 : -1;
	//get opposite colour to pass into canBeTaken function
	ChessBoard::COLOUR colour = board[src.row][src.col]->getColour();
	colour = static_cast<ChessBoard::COLOUR>(colour ^ ChessBoard::WHITE ^ ChessBoard::BLACK);
	//for each square in the path
	for (int col = src.col; col != dest.col; col+=colStep) {
		//check if the square can be taken by opponent
		if (canBeTaken(Pos(src.row, col), board, colour)) {
			return true;
		}
	}
	//if all squares cannot be taken, return false
	return false;
}

bool King::checkCastlingState(Pos src, Pos dest, const ChessPiece* board[][8], 
							  const char* castlingState) {
	bool canCastle = false;
	if (board[src.row][src.col]->getColour() == ChessBoard::WHITE) {
		//if White tries to castle kingside or queenside check with castlingState
		if ((dest.col == 6 && contains('K', castlingState))
				|| (dest.col == 1 && contains('Q', castlingState))) {
			canCastle = true;
		} 
	} else if (board[src.row][src.col]->getColour() == ChessBoard::BLACK) {
		//if Black tries to castle kingside or queenside check with castlingState
		if ((dest.col == 6 && contains('k', castlingState))
				|| (dest.col == 1 && contains('q', castlingState))) {
			canCastle = true;
		} 
	}
	return canCastle;
}

bool King::contains(char c, const char* castlingState) {
	//for each character in castlingState
	for (const char* s = castlingState; *s != '\0'; s++) {
		//if there is a match, return true
		if (c == *s) {
			return true;
		}
	}
	//if there is no match, return false
	return false;
}

/**************** Subclass Pawn implementation ****************/

Pawn::Pawn(Pos _pos, ChessBoard::COLOUR _colour) : ChessPiece(_pos, _colour) {
	name = "Pawn";
	symbol = (pieceColour == ChessBoard::WHITE) ? 'P' : 'p';
	icon = (pieceColour == ChessBoard::WHITE) ? "\u2659" : "\u265F";
};

bool Pawn::isValidMove(Pos src, Pos dest, const ChessPiece* board[][8]) {
	//check if white, then can only move up
	if (pieceColour == ChessBoard::WHITE && dest.row >= src.row) {
		return false;
	}
	//check if black, then can only move down
	if (pieceColour == ChessBoard::BLACK && dest.row <= src.row) {
		return false;
	}
	//determine direction of the diagonal with a distance of 1
	int rowStep = (dest.row > src.row) ? 1 : -1;
	int colStep = (dest.col > src.col) ? 1 : -1;
	//check start moves or if there is a piece in front	
	if (!isValidDistance(rowStep, colStep, src, dest, board)) {
		return false;
	}
	//if destination is diagonal must return true
	if (Pos(src.row + rowStep, src.col + colStep) == dest) {
		// if there is a piece, move is valid
		if (board[dest.row][dest.col]) {
			return true;
		}
	} 
	//check vertical
	if (isVertical(src, dest, board) != NULL) {
		return false;
	}
	//if all checks pass, return true
	return true;
}

bool Pawn::isValidDistance(int rowStep, int colStep, Pos src, Pos dest,
						   const ChessPiece* board[][8]) {
	//if moving from the start, can move two spaces
	if (src.row == 6 || src.row == 1) {
		if (abs(dest.row - src.row) > 2) {
			return false;
		}
		//make sure cannot take piece 2 steps away from start if there is a piece there
		if (Pos(src.row + rowStep * 2, src.col) == dest && board[dest.row][dest.col]) {
			return false;
		}
	} 
	//else can only move one space
	else {
		if (abs(dest.row - src.row) > 1) {
			return false;
		}
	}
	//make sure cannot take piece in front
	if (Pos(src.row + rowStep, src.col) == dest && board[dest.row][dest.col]) {
		return false;
	}
	//if all checks pass, return true
	return true;
}

