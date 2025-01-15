/* ChessPiece.h - header file for class ChessPiece*/

#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include "ChessBoard.h"
#include "Moves.h"
#include "Pos.h"

/***************** Superclass ChessPiece *****************/ 

class ChessPiece {
	public:
		/* Creates an instance of ChessPiece
		 *
		 * @param _pos: position of the piece
		 * @param _colour: colour of the player
		 */
		ChessPiece(Pos _pos, ChessBoard::COLOUR _colour);

		/* Getter for a piece's colour
		 *
		 * @returns: the piece's colour
		 */
		ChessBoard::COLOUR getColour() const;

		/* Getter for a piece's FEN symbol
		 *
		 * @returns: the piece's FEN symbol
		 */
		char getSymbol() const;
		
		/* Getter for a piece's position
		 *
		 * @returns: the piece's position
		 */
		Pos getPos() const;
		
		/* Setter for a piece's position
		 *
		 * @param newPos: the position to set the piece's position to
		 */
		void setPos(Pos newPos);

		/* Checks whether a piece can be taken by the opponent
		 *
		 * @param pos: position of piece to check
		 * @param board: the ChessBoard
		 * @param sideToMove: which player has the move
		 * @param except: FEN representation of piece that is not allowed to move
		 *				  (takes in capital letters only)
		 * @returns: opponent's piece that can take the piece, otherwise NULL
		 */
		static const ChessPiece* canBeTaken(Pos pos, const ChessPiece* board[][8], 
											ChessBoard::COLOUR sideToMove, char except='-');
		
		/* Checks whether the path from source to destination is valid for a piece
		 */
		virtual bool isValidMove(Pos src, Pos dest, const ChessPiece* board[][8]) = 0;

		/* Overloads the << operator to display a piece's icon
		 *
		 * @param std::ostream&: the output stream to write to
		 * @param ChessPiece&: the ChessPiece to print
		 * @returns: the output stream
		 */
		friend std::ostream& operator << (std::ostream&, const ChessPiece&);
		
		/* Overloads the << operator to display a piece's colour and name
		 *
		 * @param std::ostream&: the output stream to write to
		 * @param ChessPiece*: the ChessPiece to print
		 * @returns: the output stream
		 */
		friend std::ostream& operator << (std::ostream&, const ChessPiece*);

		/* Destructor for ChessPiece
		 */
		virtual ~ChessPiece();

	protected:
		Pos pos; //position of the ChessPiece on the ChessBoard
		ChessBoard::COLOUR pieceColour; //colour of the ChessPiece
		const char* icon; //icon of the ChessPiece
		const char* name; //name of the ChessPiece
		char symbol; //FEN representation of the ChessPiece

	private:
		/* Checks whether a piece at pos can be taken horizontally
		 *
		 * @param pos: position of the piece to check
		 * @param board: the ChessBoard
		 * @param sideToMove: which player has the move
		 * @param except: FEN representation of piece that is not allowed to move
		 *				  (takes in capital letters only)
		 * @returns: opponent's piece that can take the piece, otherwise NULL
		 */
		static const ChessPiece* checkHorizontal(Pos pos, const ChessPiece* board[][8],
											ChessBoard::COLOUR sideToMove, char except);

		/* Checks whether a piece at pos can be taken vertically 
		 *
		 * @param pos: position of the piece to check
		 * @param board: the ChessBoard
		 * @param sideToMove: which player has the move
		 * @param except: FEN representation of piece that is not allowed to move
		 *				  (takes in capital letters only)
		 * @returns: opponent's piece that can take the piece, otherwise NULL
		 */
		static const ChessPiece* checkVertical(Pos pos, const ChessPiece* board[][8],
											ChessBoard::COLOUR sideToMove, char except);

		/* Checks whether a piece at pos can be taken diagonally 
		 *
		 * @param pos: position of the piece to check
		 * @param board: the ChessBoard
		 * @param sideToMove: which player has the move
		 * @param except: FEN representation of piece that is not allowed to move
		 *				  (takes in capital letters only)
		 * @returns: opponent's piece that can take the piece, otherwise NULL
		 */
		static const ChessPiece* checkDiagonal(Pos pos, const ChessPiece* board[][8],
											ChessBoard::COLOUR sideToMove, char except);
};

/******************** Subclass Rook **********************/

class Rook: public ChessPiece {
	public:
		/* Creates an instance of Rook
		 *
		 * @param _pos: position of the piece
		 * @param _colour: colour of the piece
		 */
		Rook(Pos _pos, ChessBoard::COLOUR _colour);

		/* Checks whether the path from source to destination is valid
		 *
		 * @param src: source position
		 * @param dest: destination position
		 * @param board: the ChessBoard
		 * @returns: whether the path is valid
		 */
		bool isValidMove(Pos src, Pos dest, const ChessPiece* board[][8]) override;
};

/******************* Subclass Knight *********************/

class Knight: public ChessPiece {
	public:
		/* Creates an instance of Knight
		 *
		 * @param _pos: position of the piece
		 * @param _colour: colour of the piece
		 */
		Knight(Pos, ChessBoard::COLOUR);

		/* Checks whether the path from source to destination is valid
		 *
		 * @param src: source position
		 * @param dest: destination position
		 * @param board: the ChessBoard
		 * @returns: whether the path is valid
		 */
		bool isValidMove(Pos src, Pos dest, const ChessPiece* board[][8]) override;
};

/******************* Subclass Bishop *********************/

class Bishop: public ChessPiece {
	public:
		/* Creates an instance of Bishop
		 *
		 * @param _pos: position of the piece
		 * @param _colour: colour of the piece
		 */
		Bishop(Pos, ChessBoard::COLOUR);

		/* Checks whether the path from source to destination is valid
		 *
		 * @param src: source position
		 * @param dest: destination position
		 * @param board: the ChessBoard
		 * @returns: whether the path is valid
		 */
		bool isValidMove(Pos src, Pos dest, const ChessPiece* board[][8]) override;
};

/******************** Subclass Queen *********************/

class Queen: public ChessPiece {
	public:
		/* Creates an instance of Queen
		 *
		 * @param _pos: position of the piece
		 * @param _colour: colour of the piece
		 */
		Queen(Pos, ChessBoard::COLOUR);

		/* Checks whether the path from source to destination is valid
		 *
		 * @param src: source position
		 * @param dest: destination position
		 * @param board: the ChessBoard
		 * @returns: whether the path is valid
		 */
		bool isValidMove(Pos src, Pos dest, const ChessPiece* board[][8]) override;
};

/******************** Subclass King **********************/

class King: public ChessPiece {
	public:
		/* Creates an instance of King
		 *
		 * @param _pos: position of the piece
		 * @param _colour: colour of the piece
		 */
		King(Pos, ChessBoard::COLOUR);

		/* Checks whether the path from source to destination is valid
		 *
		 * @param src: source position
		 * @param dest: destination position
		 * @param board: the ChessBoard
		 * @returns: whether the path is valid
		 */
		bool isValidMove(Pos src, Pos dest, const ChessPiece* board[][8]) override;

		/* Checks whether the path from source to destination is a valid castling move
		 *
		 * @param src: source position
		 * @param dest: destination position
		 * @param board: the ChessBoard
		 * @param castlingState: the castling availability of ChessBoard
		 * @returns: whether the path is a castling move
		 */
		bool isCastlingMove(Pos src, Pos dest, const ChessPiece* board[][8], 
				const char* castlingState);

		bool isCastling; //whether the king is making a castling move

	private:
		/* Checks whether the squares between the source and destination can be taken 
		 * by opponent
		 *
		 * @param src: source position
		 * @param dest: destination position
		 * @param board: the ChessBoard
		 * @returns: whether the path for castling is clear
		 */
		bool isPathBlocked(Pos src, Pos dest, const ChessPiece* board[][8]);

		/* Checks whether the castling move is in the board's castling availability 
		 *
		 * @param src: source position
		 * @param dest: destination position
		 * @param board: the ChessBoard
		 * @param castlingState: the castling availability of ChessBoard
		 * @returns: whether castling is available
		 */
		bool checkCastlingState(Pos src, Pos dest, const ChessPiece* board[][8],
								const char* castlingState);

		/* Checks whether char c is in the char array castlingState
		 *
		 * @param c: char to be match
		 * @param castlingState: the castling availability of ChessBoard
		 * @returns: whether castlingState contains c
		 */
		bool contains(char c, const char* castlingState);
};

/******************** Subclass Pawn **********************/

class Pawn: public ChessPiece {
	public:
		/* Creates an instance of Pawn
		 *
		 * @param _pos: position of the piece
		 * @param _colour: colour of the piece
		 */
		Pawn(Pos, ChessBoard::COLOUR);

		/* Checks whether the path from source to destination is valid
		 *
		 * @param src: source position
		 * @param dest: destination position
		 * @param board: the ChessBoard
		 * @returns: whether the path is valid
		 */
		bool isValidMove(Pos src, Pos dest, const ChessPiece* board[][8]) override;

	private:
		/* Checks whether the distance the pawn moves is valid
		 *
		 * @param rowStep: direction and magnitude to move along row
		 * @param colStep: direction and magnitued to move along column
		 * @param src: source position
		 * @param dest: destination position
		 * @param board: the ChessBoard
		 * @returns: whether the distance the pawn moves is valid
		 */
		bool isValidDistance(int rowStep, int colStep, Pos src, Pos dest, 
							 const ChessPiece* board[][8]);
};

#endif

