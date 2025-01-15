/* Moves.h - header file for the class Moves */

#ifndef MOVES_H
#define MOVES_H

#include "ChessBoard.h"
#include "ChessPiece.h"
#include "Pos.h"

/***************** Move functions *****************/ 

/* Checks whether there is a ChessPiece on the diagonal path between source and destination
 * (checks up to, but not including, the destination)
 *
 * @param src: source location
 * @param dest: destination location
 * @param board: the ChessBoard
 * @returns: the ChessPiece in the path or NULL
 */
const ChessPiece* isDiagonal(Pos src, Pos dest, const ChessPiece* board[][8]);

/* Checks whether there is a ChessPiece on the vertical path between source and destination
 * (checks up to, but not including, the destination)
 *
 * @param src: source location
 * @param dest: destination location
 * @param board: the ChessBoard
 * @returns: the ChessPiece in the path or NULL
 */
const ChessPiece* isVertical(Pos src, Pos dest, const ChessPiece* board[][8]);

/* Checks whether there is a ChessPiece on the horizontal path between source and destination
 * (checks up to, but not including, the destination)
 *
 * @param src: source location
 * @param dest: destination location
 * @param board: the ChessBoard
 * @returns: the ChessPiece in the path or NULL
 */
const ChessPiece* isHorizontal(Pos src, Pos dest, const ChessPiece* board[][8]);

/* Checks whether the path between source and destination is an L shape (for knight moves)
 *
 * @param src: source location
 * @param dest: destination location
 * @returns: whether the path is in an L shape
 */
bool isL(Pos src, Pos dest);

/* Checks if there is a piece on the diagonal path between source and destination, and 
 * whether that piece can capture the piece at the source
 *
 * @param src: source location
 * @param dest: destination location
 * @param board: the ChessBoard
 * @param sideToMove: which player has the move
 * @param except: FEN representation of the piece that is not allowed to move
 * @returns: ChessPiece that can take the piece at src diagonally, otherwise NULL
 */
const ChessPiece* isDiagonalCheck(Pos src, Pos dest, const ChessPiece* board[][8], 
								  ChessBoard::COLOUR sideToMove, char except);

/* Checks if there is a piece on the vertical path between source and destination, and 
 * whether that piece can capture the piece at the source
 *
 * @param src: source location
 * @param dest: destination location
 * @param board: the ChessBoard
 * @param sideToMove: which player has the move
 * @param except: FEN representation of the piece that is not allowed to move
 * @returns: ChessPiece that can take the piece at src vertically, otherwise NULL
 */
const ChessPiece* isVerticalCheck(Pos src, Pos dest, const ChessPiece* board[][8], 
								  ChessBoard::COLOUR sideToMove, char except);

/* Checks if there is a piece on the horizontal path between source and destination, and
 * whether that piece can capture the piece at the source
 *
 * @param src: source location
 * @param dest: destination location
 * @param board: the ChessBoard
 * @param sideToMove: which player has the move
 * @param except: FEN representation of the piece that is not allowed to move
 * @returns: ChessPiece that can take the piece at src horizontally, otherwise NULL
 */
const ChessPiece* isHorizontalCheck(Pos src, Pos dest, const ChessPiece* board[][8], 
								    ChessBoard::COLOUR sideToMove, char except);

/* Checks whether there are opponent knights around pos that can capture the piece at pos
 *
 * @param pos: source location
 * @param board: the ChessBoard
 * @param sideToMove: which player has the move
 * @returns: ChessPiece that can take the piece at pos, otherwise NULL
 */
const ChessPiece* isLCheck(Pos pos, const ChessPiece* board[][8], 
						   ChessBoard::COLOUR sideToMove);

/* Checks whether piece at the source can be taken by takingPiece or destination piece at
 * the edge of the board
 *
 * @param takingPiece: piece that has a direct path to the source piece
 * @param src: source location
 * @param dest: destination location
 * @param board: the ChessBoard
 * @param sideToMove: which player has the move
 * @param except: FEN representation of the piece that is not allowed to move
 * @returns: ChessPiece that can take the piece at src, otherwise NULL
 */
const ChessPiece* canCheck(const ChessPiece* takingPiece, Pos src, Pos dest,
		const ChessPiece* board[][8], ChessBoard::COLOUR sideToMove, char except = '-');

#endif

