chess: ChessMain.o Pos.o Moves.o ChessBoard.o ChessPiece.o
	g++ -g ChessMain.o Pos.o Moves.o ChessBoard.o ChessPiece.o -o chess

ChessMain.o: ChessMain.cpp
	g++ -Wall -g -c ChessMain.cpp

ChessBoard.o: ChessBoard.cpp ChessBoard.h
	g++ -Wall -g -c ChessBoard.cpp

ChessPiece.o: ChessPiece.cpp ChessPiece.h
	g++ -Wall -g -c ChessPiece.cpp

Moves.o: Moves.cpp Moves.h
	g++ -Wall -g -c Moves.cpp

Pos.o: Pos.cpp Pos.h
	g++ -Wall -g -c Pos.cpp

test: test.o Pos.o Moves.o ChessBoard.o ChessPiece.o
	g++ -g test.o Pos.o Moves.o ChessBoard.o ChessPiece.o -o test

test.o: test.cpp
	g++ -Wall -g -c test.cpp

clean:
	rm -f *.o chess test
