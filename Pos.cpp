#include <iostream>
#include "Pos.h"

Pos::Pos() {};

Pos::Pos(int _row, int _col) : row(_row), col(_col) {};

Pos::Pos(const char* src) {
	*this = parsePosition(src, *this);
};

Pos& Pos::parsePosition(const char* src, Pos& pos) {
	//validate src coordinates are on board
	if (!src[0] || !src[1] || src[2] != '\0'
			|| src[0] < 'A' || src[0] > 'H'
			|| src[1] < '1' || src[1] > '8') {
		//if not valid, return an invalid Pos
		pos.row = -1;
		pos.col = -1;
		return pos;
	}
	//get row and column from src coordinates
	pos.row = 7 - (src[1] - '1');
	pos.col = src[0] - 'A';
	return pos;
}

bool Pos::operator == (const Pos& other) const {
	//check if row and column are equal
	return (row == other.row) && (col == other.col);
}

bool Pos::operator != (const Pos& other) const {
	//check if row and column are not equal
	return !((row == other.row) && (col == other.col));
}

Pos& Pos::operator = (const Pos& other) {
	//assignment of member variables
	if (this != &other) {
		row = other.row;
		col = other.col;
	}
	return *this;
}

std::ostream& operator << (std::ostream& output, const Pos& pos) {
	return output << pos.row << pos.col;
}

