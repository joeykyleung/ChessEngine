#include <iostream>
#include "ChessBoard.h"
#include "ChessPiece.h"

using namespace std;

ChessBoard::ChessBoard() {
	for (int row = 0; row < 8; row++) {
		for (int col = 0; col < 8; col++) {
			//set all squares on the board to NULL
			board[row][col] = NULL;
		}
	}
	//default white player to move
	sideToMove = ChessBoard::WHITE;
};

void ChessBoard::loadState(const char* FENstring) {
	//clear board of any previous pieces
	destruct();

	int row = 0, col = 0;
	//load board with ChessPieces
	FENstring = loadBoard(row, col, FENstring);
	//get active colour
	FENstring = getSideToMove(FENstring);
	//get castling availability (should correspond to the state of the board loaded)
	castlingState = FENstring;

	cout << "A new board state is loaded!" << endl;
}

ChessPiece* ChessBoard::makePiece (Pos pos, char FENchar) {
	//store colour and convert FENchar to lowercase
	COLOUR colour; 
	if ('a' <= FENchar && FENchar <= 'z') {
		colour = ChessBoard::BLACK;
	} else {
		colour = ChessBoard::WHITE;
		FENchar += 32;
	}
	//make pieces based on FENchar
	switch (FENchar) {
		case 'r':
			return new Rook(pos, colour);
		case 'n':
			return new Knight(pos, colour);
		case 'b':
			return new Bishop(pos, colour);
		case 'q':
			return new Queen(pos, colour);
		case 'k':
			//update position of kings
			kingPos[colour] = pos;
			return new King(pos, colour);
		case 'p':
			return new Pawn(pos, colour);
	}
	return NULL;
}

const char* ChessBoard::loadBoard(int& row, int& col, const char* FENstring) {
	//continue until first field of FENstring is read
	while (*FENstring != ' ') {
		//if char is '/' move to next row
		if (*FENstring == '/') {
			col = 0;
			row++;
			FENstring++;
			continue;
		}
		//if char is a number then skip that number of squares
		if ('1' <= *FENstring && *FENstring <= '8') {
			col += *FENstring - '1' + 1;
		} 
		// else create the piece
		else {
			board[row][col] = makePiece(Pos(row,col), *FENstring);
			col++;
		}
		FENstring++;
	}
	FENstring++;
	return FENstring;
}

const char* ChessBoard::getSideToMove(const char* FENstring) {
	//continune until the second field of FENstring is read
	while (*FENstring != ' ') {
		//set sideToMove with active colour
		if (*FENstring == 'w') {
			sideToMove = ChessBoard::WHITE;
		} else if (*FENstring == 'b') {
			sideToMove = ChessBoard::BLACK;
		}
		FENstring++;
	}
	FENstring++;
	return FENstring;
}

void ChessBoard::submitMove(const char* src, const char* dest) {
	//get positions of the arguments in row and column form
	Pos srcPos(src);
	Pos destPos(dest);
	//if any position is invalid, return
	if (srcPos.row == -1 || destPos.row == -1) {
		cout << "Invalid position inputted" << endl;
		return;
	}
	//get source piece
	ChessPiece* srcPiece = board[srcPos.row][srcPos.col];
	//if piece doesn't exist, return
	if (!srcPiece) {
		cout << "There is no piece at position " << src << "!" << endl;
		return;
	}
	//check if piece is the colour which has the move
	if (srcPiece->getColour() != sideToMove) {
		cout << "It is not " << srcPiece->getColour() << "'s turn to move!" << endl;
		return;
	}
	//check if move is valid
	if (!tryValidMove(srcPiece, srcPos, destPos)) {
		cout << srcPiece << " cannot move to " << dest << "!" << endl;
		return;
	}
	//update castlingState based on piece and its position
	updateCastlingState(srcPiece);
	//make the move
	makeMove(src, srcPos, dest, destPos);
	//reset isCastling after the move
	resetIsCastling(srcPiece);
	//check for check or checkmate or stalemate
	checkGameState();
	cout << *this << endl;
}

ChessPiece* ChessBoard::movePiece(Pos src, Pos dest) {
	//get source and destnation pieces
	ChessPiece* srcPiece = board[src.row][src.col];
	ChessPiece* destPiece = board[dest.row][dest.col];
	//insert source piece at destnation and update piece's position
	board[dest.row][dest.col] = srcPiece;
	board[dest.row][dest.col]->setPos(dest);
	//if the piece to move is a king
	if (srcPiece->getSymbol() == 'k' || srcPiece->getSymbol() == 'K') {
		//update position of the king
		kingPos[srcPiece->getColour()] = dest;
		//if isCastling, move the corresponding Rook
		if (((King*)srcPiece)->isCastling) {
			if (dest.col == 6) {
				movePiece(Pos(dest.row, dest.col + 1), Pos(dest.row, dest.col - 1));
				//undo changeSides done by movePiece
				changeSides();
			} else if (dest.col == 1) {
				movePiece(Pos(dest.row, dest.col - 1), Pos(dest.row, dest.col + 1));
				changeSides();
			}
		}
	}
	//set source location to NULL
	board[src.row][src.col] = NULL;
	//switch which player has the move
	changeSides();
	//return NULL or the piece at the destination
	return destPiece;
}

void ChessBoard::undoMove(Pos dest_o, Pos src_o, ChessPiece* takenPiece) {
	//get original destination piece
	ChessPiece* destPiece_o = board[dest_o.row][dest_o.col];
	//put original destination piece back into original source position
	board[src_o.row][src_o.col] = destPiece_o;
	//update position if not NULL
	if (board[src_o.row][src_o.col]) {
		board[src_o.row][src_o.col]->setPos(src_o);
	}
	//if the original destination piece was a king
	if (destPiece_o->getSymbol() == 'k' || destPiece_o->getSymbol() == 'K') {
		//update position of the king
		kingPos[destPiece_o->getColour()] = src_o;
		//if isCastling, revert the corresponding Rook's move
		if (((King*)destPiece_o)->isCastling) {
			if (dest_o.col == 6) {
				undoMove(Pos(dest_o.row, dest_o.col - 1), 
						Pos(dest_o.row, dest_o.col + 1), NULL);
				//undo changeSides done by undoMove
				changeSides();
			} else if (dest_o.col == 1) {
				undoMove(Pos(dest_o.row, dest_o.col + 1),
						Pos(dest_o.row, dest_o.col - 1), NULL);
				changeSides();
			}
		}
	}
	//put piece that was taken back into the original destination position
	board[dest_o.row][dest_o.col] = takenPiece;
	//update position if not NULL
	if (board[dest_o.row][dest_o.col]) {
		board[dest_o.row][dest_o.col]->setPos(dest_o);
	}
	//switch which player has the move
	changeSides();
}

bool ChessBoard::tryValidMove(ChessPiece* piece, Pos src, Pos dest) {
	//if positions are the same, move is not valid
	if (src == dest) {
		return false;
	}
	//get piece at destination
	ChessPiece* destPiece = board[dest.row][dest.col];
	//if piece is the same colour as the destination piece or player is trying to move
	//to an empty square but it is not their move, return false
	if ((destPiece && piece->getColour() == destPiece->getColour())
			|| (destPiece == NULL && piece->getColour() != sideToMove)) {
		return false;
	}
	//if piece is a king
	if (piece->getSymbol() == 'k' || piece->getSymbol() == 'K') {
		//check if it is not a castling move or a valid move
		if (!((King*)piece)->isCastlingMove(src, dest, (const ChessPiece* (*)[8])board, 
											castlingState)
				&& !piece->isValidMove(src, dest, (const ChessPiece* (*)[8])board)) {
			return false;
		}
	//else check if it is a valid move
	} else if (!piece->isValidMove(src, dest, (const ChessPiece* (*)[8])board)) {
		return false;
	}
	//try the move
	ChessPiece* capturedPiece = movePiece(src, dest);
	//if move results in check, return false
	if (isCheck(kingPos[piece->getColour()])) {
		undoMove(dest, src, capturedPiece);
		return false;
	}
	//undo the move
	else {
		undoMove(dest, src, capturedPiece);
	}
	//if all checks pass, return true
	return true;
}

void ChessBoard::changeSides() {
	//toggle colour enum value using XOR to change turns
	sideToMove = static_cast<COLOUR>(sideToMove ^ WHITE ^ BLACK);
}

void ChessBoard::makeMove(const char* src, Pos srcPos, const char* dest, Pos destPos) {
	cout << board[srcPos.row][srcPos.col] << " moves from " << src << " to " << dest;
	//get destination piece if it was taken
	ChessPiece* takenPiece = movePiece(srcPos, destPos);
	if (takenPiece) {
		cout << " taking " << takenPiece;
		//free the taken piece's pointer
		delete takenPiece;
		takenPiece = NULL;
	}
}

void ChessBoard::checkGameState() {
	//check if there is a piece that can take the king
	const ChessPiece* checkingPiece = isCheck(kingPos[sideToMove]);
	if (checkingPiece) {
		cout << '\n' << sideToMove  << " is in ";
		//check for checkmate
		if (isCheckmate(kingPos[sideToMove], checkingPiece)) {
			cout << "checkmate";
		} else {
			cout << "check";
		}
	} else {
		//check for stalemate
		if (!boardHasValidMove(sideToMove)) {
			cout << "stalemate";
		}
	}
	cout << '\n';
}

const ChessPiece* ChessBoard::isCheck(Pos kingPos) {
	//check if king can be taken
	return ChessPiece::canBeTaken(kingPos, (const ChessPiece* (*)[8]) board, sideToMove);
}

bool ChessBoard::isCheckmate(Pos kingPos, const ChessPiece* checkingPiece) {
	//check if king can move 
	if (kingCanMove(kingPos)) {
		return false;
	}
	//check if attacking piece can be taken
	if (canTakeAttacker(checkingPiece)) {
		return false;
	}
	//check if attacking piece can be blocked if it is not a knight
	if (checkingPiece->getSymbol() != 'N' && checkingPiece->getSymbol() != 'n'
			&& canBlockAttacker(kingPos, checkingPiece)) {
			return false;
	}
	//if all checks pass, return true
	return true;
}

bool ChessBoard::kingCanMove(Pos kingPos) {
	//check each square around the king
	for (int rowStep = -1; rowStep <= 1; rowStep++) {
		for (int colStep = -1; colStep <= 1; colStep++) {
			//don't check the square that the king is in
			if (rowStep == 0 && colStep == 0) {
				continue;
			}
			int row = kingPos.row + rowStep;
			int col = kingPos.col + colStep;
			Pos dest = Pos(row, col);
			//check if the proposed square is on the board
			if (row < 0 || row > 7 || col < 0 || col > 7) {
				continue;
			}
			//check if the king can move to the proposed square
			if (tryValidMove(board[kingPos.row][kingPos.col], kingPos, dest)) {
				return true;	
			}
		}
	}
	//if the king cannot move to any of the proposed squares, return false
	return false;
}

bool ChessBoard::canTakeAttacker(const ChessPiece* checkingPiece) {
	//check if checkingPiece can be captured
	const ChessPiece* takingPiece = ChessPiece::canBeTaken(checkingPiece->getPos(), 
									(const ChessPiece* (*)[8])board, sideToMove, 'K');
	//if there is a piece that can take the checkingPiece
	if (takingPiece) {
		Pos src = takingPiece->getPos();
		Pos dest = checkingPiece->getPos();
		//check if taking the checkingPiece is a valid move
		if (tryValidMove((ChessPiece*)takingPiece, src, dest)) {
			return true;
		}
	}
	//if checkingPiece cannot be taken, return false
	return false;
}

bool ChessBoard::canBlockAttacker(Pos kingPos, const ChessPiece* checkingPiece) {
	int rowStep = 0, colStep = 0;
	//if the path is horizontal, only set colStep
	if (checkingPiece->getPos().row == kingPos.row) {
		colStep = (checkingPiece->getPos().col > kingPos.col) ? 1 : -1;
	}
	//if the path is vertical, only set rowStep
	if (checkingPiece->getPos().col == kingPos.col) {
		rowStep = (checkingPiece->getPos().row > kingPos.row) ? 1 : -1;
	}
	//if the path is diagonal, set rowStep and colStep
	if (abs(checkingPiece->getPos().row - kingPos.row) 
			== abs(checkingPiece->getPos().col - kingPos.col)) {
		rowStep = (checkingPiece->getPos().row > kingPos.row) ? 1 : -1;
		colStep = (checkingPiece->getPos().col > kingPos.col) ? 1 : -1;
	}
	//for each square in the path
	for (int row = kingPos.row + rowStep, col = kingPos.col + colStep; 
			 row != checkingPiece->getPos().row || col != checkingPiece->getPos().col; 
			 row += rowStep, col += colStep) {
		//check if there is a piece that can move to the square
		const ChessPiece* takingPiece = ChessPiece::canBeTaken(Pos(row, col), 
										(const ChessPiece* (*)[8])board, sideToMove, 'K');
		//if there is a piece that can block the path
		if (takingPiece) {
			Pos src(takingPiece->getPos().row, takingPiece->getPos().col);
			Pos dest(row, col);
			//check if blocking the path is a valid move
			if (tryValidMove((ChessPiece*)takingPiece, src, dest)) {
				return true;
			}	
		}
	}
	//if path cannot be blocked by a piece, return false
	return false;
}

void ChessBoard::updateCastlingState(ChessPiece* piece) {
	const char* remove = NULL;
	//based on the FEN symbol of the piece, select castling availability to remove
	switch(piece->getSymbol()) {
		case 'K':
			remove = "KQ";
			break;
		case 'k':
			remove = "kq";
			break;
		case 'R':
			if (piece->getPos().col == 7) {
				remove = "K";
			} else if (piece->getPos().col == 0) {
				remove = "Q";
			}
			break;
		case 'r':
			if (piece->getPos().col == 7) {
				remove = "k";
			} else if (piece->getPos().col == 0) {
				remove = "q";
			}
			break;
	}
	//if there is castling availability to remove
	if (remove) {
		//set up a new char array
		char* newState = new char[4];
		int index = 0;
		bool match = false;
		for (const char* c = castlingState; *c != '\0'; c++) {
			for (const char* r = remove; *r != '\0'; r++) {
				//check if castling availability is in the remove char array
				if (*c == *r) {
					match = true;
					break;
				}
			}
			//if not in remove char array, add to the new char array
			if (!match) {
				newState[index] = *c;
				index++;
			}
			match = false;
		}
		//add the null terminator
		newState[index] = '\0';
		//if all castling availability has been removed, set it to '-'
		if (newState[0] == '\0') {
			newState = (char*)"-";
		}
		//set castlingState to the new char array
		castlingState = newState;
	}
}

void ChessBoard::resetIsCastling(ChessPiece* piece) {
	//if the piece is a king, reset isCastling to false
	switch(piece->getSymbol()) {
		case 'K':
			((King*)piece)->isCastling = false;
			break;
		case 'k':
			((King*)piece)->isCastling = false;
			break;
	}
}

bool ChessBoard::boardHasValidMove(COLOUR sideToMove) {
	//for each square of the board
	for (int row = 0; row < 8; row++) {
		for (int col = 0; col < 8; col++) {
			ChessPiece* piece = board[row][col];
			//check if there is a player's piece there and whether it has any valid moves
			if (piece && piece->getColour() == sideToMove && pieceHasValidMove(piece)) {
				return true;
			}
		}
	}
	//if there are no valid moves for any of the player's pieces, return false
	return false;
}

bool ChessBoard::pieceHasValidMove(ChessPiece* piece) {
	//for each square of the board
	for (int row = 0; row < 8; row++) {
		for (int col = 0; col < 8; col++) {
			//check if the piece can move to the square
			if (tryValidMove(piece, piece->getPos(), Pos(row, col))) {
				return true;
			}
		}
	}
	//if the piece cannot move to any square, return false
	return false;
}

std::ostream& operator << (std::ostream& output, const ChessBoard::COLOUR& colour) {	
	//setup an array of strings corresponding to the COLOURS enum
	const char* colours[] = {"Black", "White"};
	//print enum using COLOUR as index
	return output << colours[colour];
}

std::ostream& operator << (std::ostream& output, const ChessBoard& board) {
	for (int rank = 0; rank < 8; rank++) {
		//print ranks
		output << 8 - rank << " ";
		for (int file = 0; file < 8; file++) {
			//print piece on board or '.' if there is no piece
			if (board.board[rank][file] == NULL) {
				output << ". ";
				continue;
			}
			output << *board.board[rank][file] << " ";
		} 
		output << endl;
	}
	output << "  ";
	//print files
	for (char file = 'A'; file <= 'H'; file++) {
		output << file << " ";
	}
	output << '\n';
	return output;
}

void ChessBoard::destruct () {
	//for each square of the board
	for (int rank = 0; rank < 8; rank++) {
		for (int file = 0; file < 8; file++) {
			//free the pointer in the square
			delete board[rank][file];
			board[rank][file] = NULL;
		}
	}
}

ChessBoard::~ChessBoard() {
	destruct();
}

