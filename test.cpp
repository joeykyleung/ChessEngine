#include <iostream>
#include "ChessBoard.h"
#include<cstring>
using namespace std;

int main () {
	cout << "========================\n";
	cout << "Testing the Chess Engine\n";
	cout << "========================\n";
	
	ChessBoard cb;
	cb.loadState("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq");
	//--checkmate
	//cb.loadState("rnbq1bnr/pppppppp/2pkp3/p1Ppp3/8/1N7/PPPPPPPP/RNBQKBNR w KQkq");
	//cb.loadState("rnbq1bnr/pppppppp/2bkp3/111pp3/1B6/1N7/PPPPPPPP/RNBQKBNR w KQkq");
	//--horizontal checkmate block
	//cb.loadState("rnbq1bnr/ppppp1bp/2ppb3/2pk2R1/2ppp3/8/PPPPPPPP/RNBQKBNR w KQkq");
	//--vertical checkmate block
	//cb.loadState("rnbq1bnr/pppppppp/2ppp3/2pkp3/2p1p3/6r1/PPP1PPPP/RNBQKBNR w KQkq");
	//--diagonal checkmate blcok
	//cb.loadState("rnbq1bnr/pppppppp/2pkbb2/2pp13/5B2/8/PPPPPPPP/RNBQKBNR w KQkq");
	//--isL check
	//cb.loadState("rnbq1bnr/pppppppp/2pkrb2/2pp1N3/8/4R3/PPPPPPPP/RNBQKBNR w KQkq");
	//cb.loadState("rnbq1bnr/pppppppp/2ppn3/2pkp3/2p1p3/1n7/PPP1PPPP/RNBQKBNR w KQkq");
	//cb.loadState("8/3p4/8/2R1R3/3k4/2R1R3/P6K/8 w KQkq"); //not stalemate
	//cb.loadState("K7/8/8/8/8/8/P4Q2/7k w KQkq"); //stalemate
	/*cb.loadState("kbQ5/8/2K5/8/8/8/8/8 w "); // stalemate
	cb.submitMove("C6", "B6");
	*/
	/*cb.loadState("rnbq1bnr/ppppp1bp/2ppn3/2pk1p1R/2ppp3/8/PPPPPPPP/RNBQKBNR w KQkq");
    cb.submitMove("A2", "A4");
	cb.submitMove("F5", "F4"); //check if can move that results in check
	*/
	/*cb.loadState("r3k2r/8/8/8/8/8/8/R1K4R w Kkq"); //check castling
	cb.submitMove("C1", "B1");
	*/
	/*cb.loadState("r3k2r/8/8/8/8/8/8/R3K2R w KQkq"); //check castling
	cb.submitMove("A1", "C1");
	cb.submitMove("H8", "G8");
	cb.submitMove("C1", "A1");
	cb.submitMove("E8", "B8");
	cb.submitMove("A1", "C1");
	cb.submitMove("G8", "D8");
	cb.submitMove("E1", "G1");
	*/
	/*cb.loadState("r3k2r/8/8/8/8/8/8/R3K2R w KQkq"); //check castling
	cb.submitMove("A1", "C1");
	cb.submitMove("E8", "G8");
	cb.submitMove("C1", "A1");
	cb.submitMove("F8", "C8");
	cb.submitMove("E1", "B1");
	cb.submitMove("E1", "G1");
	*/
	/*cb.loadState("r3k2r/8/8/8/8/8/6q1/R3K2R w KQkq"); //check cannot castle (q)
	cb.submitMove("E1", "B1");
	*/
	cout << cb << endl;
	char c[3];
	while (true) {
		cout << "Move: ";
		cin >> c;
		if (strcmp(c, "q") == 0) break;
		char pos1[3]; 
		strncpy(pos1, c, 3);
		cin >> c;
		char pos2[3];
		strncpy(pos2, c, 3);
		cb.submitMove(pos1, pos2);
		cout << '\n';
	}

	//cb.submitMove("A2", "A4");
	cout << '\n';
	/*cb.submitMove("B1", "C3");
	cout << '\n';
	cb.submitMove("A8", "A6");
	cout << '\n';
	cb.submitMove("D2", "D3");
	cout << '\n';
	cb.submitMove("A6", "D6");
	cout << '\n';
	cb.submitMove("C1", "G5");
	cout << '\n';
	*/

	return 0;
}
