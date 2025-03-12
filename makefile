CXX = g++
CXXFLAGS = -Wall -g -std=c++11 -arch $(shell uname -m)

chess: ChessMain.o Pos.o Moves.o ChessBoard.o ChessPiece.o
	$(CXX) $(CXXFLAGS) ChessMain.o Pos.o Moves.o ChessBoard.o ChessPiece.o -o chess

ChessMain.o: ChessMain.cpp
	$(CXX) $(CXXFLAGS) -c ChessMain.cpp

ChessBoard.o: ChessBoard.cpp ChessBoard.h
	$(CXX) $(CXXFLAGS) -c ChessBoard.cpp

ChessPiece.o: ChessPiece.cpp ChessPiece.h
	$(CXX) $(CXXFLAGS) -c ChessPiece.cpp

Moves.o: Moves.cpp Moves.h
	$(CXX) $(CXXFLAGS) -c Moves.cpp

Pos.o: Pos.cpp Pos.h
	$(CXX) $(CXXFLAGS) -c Pos.cpp

test: test.o Pos.o Moves.o ChessBoard.o ChessPiece.o
	$(CXX) $(CXXFLAGS) test.o Pos.o Moves.o ChessBoard.o ChessPiece.o -o test

test.o: test.cpp
	$(CXX) $(CXXFLAGS) -c test.cpp

clean:
	rm -f *.o chess test

.PHONY: clean
