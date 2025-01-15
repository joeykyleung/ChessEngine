/* Pos.h - header file for the class Pos */

#ifndef POS_H
#define POS_H

#include <iostream>

/******************* Class Pos *******************/

class Pos {
	public:
		int row; //row value of position 
		int col; //column value of position

		/* Creates an instance of Pos with uninitialized members
		 */
		Pos();

		/* Creates an instance of Pos
		 *
		 * @param _row: row of the position to intialise to
		 * @param _col: column of the position to intialise to
		 */
		Pos(int _row, int _col);

		/* Creates an instance of Pos
		 *
		 * @param src: location of piece on the board in rank and file form
		 */
		Pos(const char* src);
		
		/* Overloads the == operator to compare if the other Pos is the same
		 *
		 * @param other: Pos to compare to
		 * @returns: whether the two Pos are the same
		 */
		bool operator == (const Pos& other) const;

		/* Overloads the != operator to compare if the other Pos is not the same
		 *
		 * @param other: Pos to compare to
		 * @returns: whether the two Pos are different
		 */
		bool operator != (const Pos& other) const; 

		/* Overloads the = operator to assign one Pos to another
		 *
		 * @param other: Pos to assign
		 * @returns: a Pos that is the same as other
		 */
		Pos& operator = (const Pos& other);

		/* Overloads the << operator to print Pos
		 *
		 * @param std::ostream&: output stream to write to
		 * @param Pos&: Pos to print
		 * @returns: the output stream
		 */
		friend std::ostream& operator << (std::ostream&, const Pos&); 

	private:
		/* Checks whether a rank and file location is valid and parses it into row and column
		 *
		 * @param src: rank and file location
		 * @param pos: Pos to assign parsed row and column
		 * @returns: Pos with parsed row and column
		 */
		Pos& parsePosition(const char* src, Pos& pos);
};

#endif

