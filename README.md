# sudoku-algorithms
Sudoku Solver and Puzzle Generator built in C++

## Sudoku Solver
Uses Backtracking and Recursive algorithms to find empty squares and fill them with valid numbers.

## Sudoku Puzzle Generator
Uses a full puzzle generated using purely non-deterministic randomness by time-seeding the Mersenne Twister engine, according to the modern C++ standards.

The full puzzle is then subjected to a "hole-digging" algorithm, thant removes a number randomly and checks the solvability of the puzzle at every iteration.

The number of "holes" can be controlled by changing the difficulty factor variable value. 
