/* ChessBoard.h - header file for the class ChessBoard */

#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <iostream>
#include "Pos.h"

/******************* Class ChessBoard *******************/

class ChessPiece;

class ChessBoard {
	public:
		/* Represents the colour of the players and pieces
		 *
		 * @value BLACK: black player or black piece
		 * @value WHITE: white player or white piece
		 */
		enum COLOUR {BLACK, WHITE};
		
		/* Creates an instance of an empty ChessBoard
		 */
		ChessBoard();
		
		/* Populates the ChessBoard and its state based on a FEN string
		 * 
		 * @param FENstring: ChessBoard state in Forsyth-Edwards Notation 
		 */
		void loadState(const char* FENstring);
		
		/* Initiates checks to see whether a move is valid, makes the move,
		 * and checks if the move results in a check, checkmate or stalemate
		 *
		 * @param src: location of piece to move represented by rank and file
		 * @param dest: location to move to represented by rank and file
		 */
		void submitMove(const char* src, const char* dest);

		/* Overloads the << operator to print a COLOUR
		 *
		 * @param std::ostream&: the output stream to write to
		 * @param ChessBoard&: COLOUR to be printed
		 * @returns: the output stream
		 */
		friend std::ostream& operator << (std::ostream&, const COLOUR&);

		/* Overloads the << operator to display the ChessBoard
		 *
		 * @param std::ostream&: the output stream to write to
		 * @param ChessBoard&: ChessBoard to be printed
		 * @returns: the output stream
		 */
		friend std::ostream& operator << (std::ostream&, const ChessBoard&);

		/* Destructor for ChessBoard empties the board
		 */
		virtual ~ChessBoard();

	private:
		ChessPiece* board[8][8]; //2D array representing the ChessBoard and its pieces
		COLOUR sideToMove; //Player who has the move
		const char* castlingState; //State of castling availability
		Pos kingPos[2]; //Position of kings (black at index 0, white at index 1)

		/* Dynamically creates a specific ChessPiece type based on a FEN char
		 *
		 * @param pos: position of ChessPiece on the ChessBoard
		 * @param FENchar: ChessPiece in Forsyth-Edwards Notation
		 * @returns: a pointer to the created ChessPiece
		 */
		ChessPiece* makePiece(Pos pos, char FENchar);

		/* Populates a ChessBoard with ChessPieces by incrementing FENstring pointer
		 * 
		 * @param row: row on the ChessBoard
		 * @param col: column on the ChessBoard 
		 * @param FENstring: ChessBoard state in Forsyth-Edwards Notation
		 * @returns: the updated FENstring pointer
		 */
		const char* loadBoard(int& row, int& col, const char* FENstring);
		
		/* Sets sideToMove with the active colour from FENstring
		 *
		 * @param FENstring: active colour and castling availability of the ChessBoard 
		 *					 state in Forsyth-Edwards Notation
		 * @returns: the updated FENstring pointer
		 */
		const char* getSideToMove(const char* FENstring);

		/* Moves a piece from source to destination
		 *
		 * @param src: position of the source
		 * @param dest: position of the destination
		 * @returns: ChessPiece or NULL at the destination
		 */
		ChessPiece* movePiece(Pos src, Pos dest);
		
		/* Reverts a move from the original destination to the original source
		 *
		 * @param dest_o: original destination a piece moved to
		 * @param src_o: original source a piece moved from
		 * @param takenPiece: piece that was at the original destination
		 */
		void undoMove(Pos dest_o, Pos src_o, ChessPiece* takenPiece);

		/* Evaluates whether a move is valid
		 * 
		 * @param piece: piece to move
		 * @param src: source position to move from
		 * @param dest: destination position to move to
		 * @returns: whether move is valid
		 */
		bool tryValidMove(ChessPiece* piece, Pos src, Pos dest);

		/* Changes the player/colour that has the move
		 */
		void changeSides();

		/* Moves a piece based on input from submitMove and prints the move
		 * 
		 * @param src: source position in rank and file form
		 * @param srcPos: source position in row and column form
		 * @param dest: destination position in rank and file form
		 * @param destPos: destination position in row and column form
		 */
		void makeMove(const char* src, Pos srcPos, const char* dest, Pos destPos);

		/* Checks whether player is in check, checkmate or stalemate
		 */
		void checkGameState();

		/* Checks whether a king is in check
		 *
		 * @param kingPos: position of the king
		 * @returns: piece that can take the king
		 */
		const ChessPiece* isCheck(Pos kingPos);
		
		/* Checks whether a player is in checkmate
		 *
		 * @param kingPos: position of the player's king
		 * @param checkingPiece: piece that can take the player's king
		 * @returns: whether player is in checkmate
		 */
		bool isCheckmate(Pos kingPos, const ChessPiece* checkingPiece);

		/* Checks whether a player's king can move
		 *
		 * @param kingPos: position of the player's king
		 * @returns: whether the king has a valid move
		 */
		bool kingCanMove(Pos);

		/* Checks whether a piece's attacker can be taken
		 *
		 * @param checkingPiece: the attacking piece
		 * @returns: whether the attacking piece can be taken
		 */
		bool canTakeAttacker(const ChessPiece* checkingPiece);

		/* Checks whether the path from a king and its attacker can be blocked
		 *
		 * @param kingPos: position of the king
		 * @param checkingPiece: the piece that is attacking the king
		 * @returns: whether the path between checkingPiece and king can be blocked
		 */
		bool canBlockAttacker(Pos kingPos, const ChessPiece* checkingPiece);

		/* Update the castling availability based on which piece is moving
		 *
		 * @param piece: the piece that is moving
		 */
		void updateCastlingState(ChessPiece* piece);

		/* Reset the isCastling member of a king after a move
		 *
		 * @param piece: the piece hat has moved
		 */
		void resetIsCastling(ChessPiece* piece);

		/* Checks whether there are any valid moves for a player on the board
		 *
		 * @param sideToMove: which player to check for
		 * @returns: whether the player's pieces have any valid moves
		 */
		bool boardHasValidMove(COLOUR sideToMove);

		/* Checks whether a piece has any valid moves
		 *
		 * @param piece: the piece to check
		 * @returns: whether the piece has any square to move to
		 */
		bool pieceHasValidMove(ChessPiece* piece);

		/* Empties the ChessBoard
		 */
		void destruct();
};

#endif

