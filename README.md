# ChessEngine
A sophisticated C++ chess engine implementation that provides a robust platform for playing and analyzing chess games.

![Screenshot 2025-03-12 at 2 36 33 PM](https://github.com/user-attachments/assets/da4684ca-7b93-4cf1-9f45-5bcdae95a7e3)


## Features
- Complete chess rule implementation including special moves (castling, en passant)
- FEN (Forsyth–Edwards Notation) string support for board state loading
- Advanced move validation system
- Check, checkmate, and stalemate detection
- Object-oriented design with clear separation of concerns

## System Requirements
- C++11 or higher
- GCC/Clang compiler
- Make build system
- Unix-like environment (Linux/macOS)

## Technical Implementation
The engine is built with several key components:

### Core Classes
- `ChessBoard`: Main game controller managing the board state and game flow
- `ChessPiece`: Abstract base class for chess pieces with derived piece-specific classes
- `Pos`: Handles position calculations and board coordinate translations
- `Moves`: Implements move generation and validation logic

### Technical Challenges & Solutions
1. **Move Validation**
   - Implemented a sophisticated move validation system that checks piece-specific rules
   - Uses a two-phase validation: first checks basic piece movement, then validates if the move would result in check
   - Efficient implementation using bitboards for move generation

2. **Check Detection**
   - Maintains king positions for quick check detection
   - Implements ray-tracing algorithm to detect attacks along ranks, files, and diagonals
   - Optimized to avoid unnecessary board scanning

3. **State Management**
   - Uses FEN notation for compact board state representation
   - Implements efficient state rollback for move validation
   - Maintains castling rights and en passant possibilities

## Building and Running
1. Clone the repository
2. Build using make:
```bash
make clean  # Clean any previous builds
make        # Compile the project
```

3. Set executable permissions:
```bash
chmod +x chess
chmod +x test
```

4. Run the chess engine:
```bash
./chess
```

## Usage Examples
```cpp
ChessBoard cb;
// Load initial position
cb.loadState("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq");

// Make moves using algebraic notation
cb.submitMove("E2", "E4");  // Move white pawn from E2 to E4
cb.submitMove("E7", "E5");  // Move black pawn from E7 to E5
```

## Testing
The engine includes a comprehensive test suite in `test.cpp`. Run the tests using:
```bash
make test    # Compile the test suite
chmod +x test  # Ensure test is executable
./test       # Run the tests
```

## Troubleshooting
If you encounter permission denied errors:
1. Make sure the executables have proper permissions:
   ```bash
   chmod +x chess test
   ```
2. If compilation fails, ensure you have the required compiler and dependencies:
   ```bash
   g++ --version  # Check compiler version
   make --version # Check make version
   ```
